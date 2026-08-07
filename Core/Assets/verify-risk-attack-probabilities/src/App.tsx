import { useMemo, useState } from "react";
import {
  analyzeAttacks,
  conquerProbability,
  TERRITORIES,
  WIKI_TABLE,
  type AnalyzedAttack,
} from "./data/risk";

const OWNER_COLORS: Record<string, string> = {
  Red: "bg-rose-500",
  Blue: "bg-sky-500",
  Yellow: "bg-amber-400",
  Green: "bg-emerald-500",
};

const OWNER_TEXT: Record<string, string> = {
  Red: "text-rose-300",
  Blue: "text-sky-300",
  Yellow: "text-amber-300",
  Green: "text-emerald-300",
};

function accuracyBadge(absDiff: number) {
  if (absDiff <= 0.5)
    return { label: "Corretto", cls: "bg-emerald-500/15 text-emerald-300 ring-emerald-500/30" };
  if (absDiff <= 1.5)
    return { label: "Quasi", cls: "bg-lime-500/15 text-lime-300 ring-lime-500/30" };
  if (absDiff <= 3)
    return { label: "Impreciso", cls: "bg-amber-500/15 text-amber-300 ring-amber-500/30" };
  return { label: "Sbagliato", cls: "bg-rose-500/15 text-rose-300 ring-rose-500/30" };
}

function StatCard({ label, value, sub }: { label: string; value: string; sub?: string }) {
  return (
    <div className="rounded-xl border border-white/10 bg-white/[0.03] p-4">
      <div className="text-2xl font-bold text-white sm:text-3xl">{value}</div>
      <div className="mt-1 text-xs font-medium uppercase tracking-wide text-slate-400">
        {label}
      </div>
      {sub && <div className="mt-0.5 text-xs text-slate-500">{sub}</div>}
    </div>
  );
}

export default function App() {
  const attacks = useMemo(() => analyzeAttacks(), []);
  const [sortByError, setSortByError] = useState(false);

  const sorted = useMemo(() => {
    const copy = [...attacks];
    if (sortByError) copy.sort((x, y) => Math.abs(y.diff) - Math.abs(x.diff));
    else copy.sort((x, y) => y.claimed - x.claimed);
    return copy;
  }, [attacks, sortByError]);

  const avgAbsError =
    attacks.reduce((s, a) => s + Math.abs(a.diff), 0) / attacks.length;
  const maxError = attacks.reduce(
    (m, a) => (Math.abs(a.diff) > Math.abs(m.diff) ? a : m),
    attacks[0],
  );
  const correctCount = attacks.filter((a) => Math.abs(a.diff) <= 0.5).length;

  // Detect inconsistencies: same (a,d) matchup but different claimed values.
  const groups = useMemo(() => {
    const map = new Map<string, AnalyzedAttack[]>();
    attacks.forEach((a) => {
      const k = `${a.a}v${a.d}`;
      if (!map.has(k)) map.set(k, []);
      map.get(k)!.push(a);
    });
    return [...map.entries()]
      .map(([k, list]) => {
        const claims = list.map((l) => l.claimed);
        const spread = Math.max(...claims) - Math.min(...claims);
        return { key: k, list, spread, actual: list[0].actual };
      })
      .filter((g) => g.list.length > 1 && g.spread > 1)
      .sort((x, y) => y.spread - x.spread);
  }, [attacks]);

  return (
    <div className="min-h-screen bg-slate-950 text-slate-200">
      {/* header */}
      <header className="border-b border-white/10 bg-gradient-to-br from-slate-900 via-slate-950 to-slate-900">
        <div className="mx-auto max-w-6xl px-5 py-10 sm:py-14">
          <div className="inline-flex items-center gap-2 rounded-full border border-white/10 bg-white/5 px-3 py-1 text-xs font-medium text-slate-300">
            🎲 Analisi probabilità · Risiko
          </div>
          <h1 className="mt-4 text-3xl font-bold tracking-tight text-white sm:text-5xl">
            Verifica dei tuoi valori di conquista
          </h1>
          <p className="mt-4 max-w-2xl text-sm leading-relaxed text-slate-400 sm:text-base">
            Ho confrontato le percentuali che hai indicato con le probabilità{" "}
            <span className="text-white">esatte</span>, calcolate risolvendo la
            catena di Markov del combattimento (attaccante fino a 3 dadi,
            difensore fino a 2, pareggi al difensore). L'attaccante impegna sempre{" "}
            <span className="text-white">carri − 1</span> unità. Riferimento
            incrociato: tabella statistica del{" "}
            <a
              href="https://risk.fandom.com/wiki/Risk_Board_Game"
              target="_blank"
              rel="noreferrer"
              className="text-sky-400 underline decoration-dotted underline-offset-2"
            >
              Risk Fandom Wiki
            </a>
            .
          </p>

          <div className="mt-8 grid grid-cols-2 gap-3 sm:grid-cols-4">
            <StatCard label="Attacchi analizzati" value={String(attacks.length)} />
            <StatCard
              label="Errore medio"
              value={`${avgAbsError.toFixed(1)} pt`}
              sub="scarto assoluto medio"
            />
            <StatCard
              label="Errore massimo"
              value={`${Math.abs(maxError.diff).toFixed(1)} pt`}
              sub={`${maxError.from} → ${maxError.to}`}
            />
            <StatCard
              label="Valori corretti"
              value={`${correctCount}/${attacks.length}`}
              sub="entro ±0,5 pt"
            />
          </div>
        </div>
      </header>

      <main className="mx-auto max-w-6xl space-y-12 px-5 py-12">
        {/* verdict */}
        <section className="rounded-2xl border border-white/10 bg-white/[0.03] p-6">
          <h2 className="text-lg font-semibold text-white">In sintesi</h2>
          <p className="mt-2 text-sm leading-relaxed text-slate-400">
            I tuoi valori sono <span className="text-emerald-300">nel complesso
            buoni</span>: lo scarto medio è di solo{" "}
            <span className="text-white">{avgAbsError.toFixed(1)} punti
            percentuali</span>. La maggior parte rientra entro 1–2 punti dal
            valore reale. I problemi principali non sono grandi errori numerici,
            ma <span className="text-white">incoerenze</span>: matchup
            identici (stessi carri attaccante/difensore) a cui hai assegnato
            percentuali diverse. Statisticamente devono dare lo stesso risultato.
          </p>
        </section>

        {/* main comparison table */}
        <section>
          <div className="mb-4 flex flex-wrap items-center justify-between gap-3">
            <h2 className="text-xl font-semibold text-white">
              Confronto attacco per attacco
            </h2>
            <button
              onClick={() => setSortByError((v) => !v)}
              className="rounded-lg border border-white/10 bg-white/5 px-3 py-1.5 text-xs font-medium text-slate-300 transition hover:bg-white/10"
            >
              Ordina per: {sortByError ? "errore" : "probabilità"}
            </button>
          </div>

          <div className="overflow-x-auto rounded-2xl border border-white/10">
            <table className="w-full min-w-[720px] text-sm">
              <thead>
                <tr className="border-b border-white/10 bg-white/[0.04] text-left text-xs uppercase tracking-wide text-slate-400">
                  <th className="px-4 py-3 font-medium">Attacco</th>
                  <th className="px-4 py-3 text-center font-medium">Dadi (A vs D)</th>
                  <th className="px-4 py-3 text-right font-medium">Tuo valore</th>
                  <th className="px-4 py-3 text-right font-medium">Reale</th>
                  <th className="px-4 py-3 text-right font-medium">Scarto</th>
                  <th className="px-4 py-3 text-center font-medium">Giudizio</th>
                </tr>
              </thead>
              <tbody>
                {sorted.map((a, i) => {
                  const badge = accuracyBadge(Math.abs(a.diff));
                  const fromT = TERRITORIES.find((t) => t.name === a.from)!;
                  const toT = TERRITORIES.find((t) => t.name === a.to)!;
                  return (
                    <tr
                      key={i}
                      className="border-b border-white/5 last:border-0 hover:bg-white/[0.02]"
                    >
                      <td className="px-4 py-3">
                        <div className="flex items-center gap-1.5 font-medium text-white">
                          <span className={OWNER_TEXT[fromT.owner]}>{a.from}</span>
                          <span className="text-slate-600">→</span>
                          <span className={OWNER_TEXT[toT.owner]}>{a.to}</span>
                        </div>
                        <div className="mt-0.5 text-xs text-slate-500">
                          {a.attackerArmies} carri vs {a.defenderArmies} carri
                        </div>
                      </td>
                      <td className="px-4 py-3 text-center font-mono text-xs text-slate-400">
                        {a.a} vs {a.d}
                      </td>
                      <td className="px-4 py-3 text-right font-mono text-slate-300">
                        {a.claimed.toFixed(1)}%
                      </td>
                      <td className="px-4 py-3 text-right font-mono font-semibold text-white">
                        {a.actual.toFixed(1)}%
                      </td>
                      <td
                        className={`px-4 py-3 text-right font-mono font-semibold ${
                          a.diff > 0 ? "text-rose-300" : a.diff < 0 ? "text-sky-300" : "text-slate-400"
                        }`}
                      >
                        {a.diff > 0 ? "+" : ""}
                        {a.diff.toFixed(1)}
                      </td>
                      <td className="px-4 py-3 text-center">
                        <span
                          className={`inline-block rounded-full px-2.5 py-0.5 text-xs font-medium ring-1 ${badge.cls}`}
                        >
                          {badge.label}
                        </span>
                      </td>
                    </tr>
                  );
                })}
              </tbody>
            </table>
          </div>
          <p className="mt-3 text-xs text-slate-500">
            Scarto = tuo valore − valore reale. In{" "}
            <span className="text-rose-300">rosso</span> hai sovrastimato le tue
            chance, in <span className="text-sky-300">azzurro</span> le hai
            sottostimate.
          </p>
        </section>

        {/* inconsistencies */}
        <section>
          <h2 className="text-xl font-semibold text-white">
            Incoerenze rilevate
          </h2>
          <p className="mt-2 text-sm text-slate-400">
            Questi gruppi hanno lo{" "}
            <span className="text-white">stesso matchup di dadi</span> (stessi
            carri d'attacco impegnati contro stessi carri in difesa), quindi la
            probabilità reale è identica. I valori che hai dato però variano — il
            che non è statisticamente possibile.
          </p>
          <div className="mt-5 grid gap-4 md:grid-cols-2">
            {groups.map((g) => (
              <div
                key={g.key}
                className="rounded-2xl border border-amber-500/20 bg-amber-500/[0.04] p-5"
              >
                <div className="flex items-center justify-between">
                  <span className="font-mono text-sm text-amber-300">
                    {g.key} dadi
                  </span>
                  <span className="rounded-full bg-white/10 px-2.5 py-0.5 text-xs text-white">
                    reale {g.actual.toFixed(1)}%
                  </span>
                </div>
                <div className="mt-1 text-xs text-slate-400">
                  Divario tra i tuoi valori:{" "}
                  <span className="font-semibold text-amber-300">
                    {g.spread.toFixed(1)} pt
                  </span>
                </div>
                <ul className="mt-3 space-y-1.5">
                  {g.list
                    .slice()
                    .sort((x, y) => y.claimed - x.claimed)
                    .map((a, i) => (
                      <li
                        key={i}
                        className="flex items-center justify-between text-sm"
                      >
                        <span className="text-slate-300">
                          {a.from} → {a.to}
                        </span>
                        <span className="font-mono text-slate-400">
                          {a.claimed.toFixed(1)}%
                          <span
                            className={`ml-2 ${
                              a.diff > 0 ? "text-rose-300" : "text-sky-300"
                            }`}
                          >
                            ({a.diff > 0 ? "+" : ""}
                            {a.diff.toFixed(1)})
                          </span>
                        </span>
                      </li>
                    ))}
                </ul>
              </div>
            ))}
          </div>
        </section>

        {/* reference table */}
        <section>
          <h2 className="text-xl font-semibold text-white">
            Tabella di riferimento
          </h2>
          <p className="mt-2 text-sm text-slate-400">
            Probabilità di conquista dell'attaccante (%). Colonne = carri
            d'attacco impegnati, righe = carri in difesa. Le celle{" "}
            <span className="text-emerald-300">evidenziate</span> mostrano il
            valore esatto per i matchup dei tuoi attacchi.
          </p>
          <div className="mt-5 overflow-x-auto rounded-2xl border border-white/10">
            <table className="w-full min-w-[640px] text-center text-sm">
              <thead>
                <tr className="border-b border-white/10 bg-white/[0.04] text-xs text-slate-400">
                  <th className="px-3 py-2 font-medium">D \ A</th>
                  {Array.from({ length: 10 }, (_, i) => (
                    <th key={i} className="px-3 py-2 font-medium">
                      {i + 1}
                    </th>
                  ))}
                </tr>
              </thead>
              <tbody>
                {WIKI_TABLE.map((row, di) => (
                  <tr key={di} className="border-b border-white/5 last:border-0">
                    <td className="bg-white/[0.03] px-3 py-2 font-medium text-slate-400">
                      {di + 1}
                    </td>
                    {row.map((val, ai) => {
                      const used = usedMatchups.has(`${ai + 1}v${di + 1}`);
                      const exact = conquerProbability(ai + 1, di + 1) * 100;
                      return (
                        <td
                          key={ai}
                          className={`px-3 py-2 font-mono ${
                            used
                              ? "bg-emerald-500/15 font-semibold text-emerald-200"
                              : "text-slate-400"
                          }`}
                          title={`esatto ${exact.toFixed(1)}%`}
                        >
                          {val}
                        </td>
                      );
                    })}
                  </tr>
                ))}
              </tbody>
            </table>
          </div>
        </section>

        {/* territory reference */}
        <section>
          <h2 className="text-xl font-semibold text-white">
            Situazione dei territori
          </h2>
          <p className="mt-2 text-sm text-slate-400">
            I dati letti dal file: proprietario e numero di carri.
          </p>
          <div className="mt-5 grid grid-cols-2 gap-2 sm:grid-cols-3 lg:grid-cols-4">
            {TERRITORIES.map((t) => (
              <div
                key={t.name}
                className="flex items-center justify-between gap-2 rounded-lg border border-white/10 bg-white/[0.03] px-3 py-2"
              >
                <div className="flex items-center gap-2 truncate">
                  <span
                    className={`h-2.5 w-2.5 flex-none rounded-full ${OWNER_COLORS[t.owner]}`}
                  />
                  <span className="truncate text-xs text-slate-300">{t.name}</span>
                </div>
                <span className="flex-none rounded bg-white/10 px-1.5 py-0.5 font-mono text-xs text-white">
                  {t.armies}
                </span>
              </div>
            ))}
          </div>
        </section>
      </main>

      <footer className="border-t border-white/10 py-6 text-center text-xs text-slate-500">
        Probabilità esatte via catena di Markov · riferimento incrociato Risk
        Fandom Wiki
      </footer>
    </div>
  );
}

const usedMatchups = new Set(
  analyzeAttacks().map((a) => `${a.a}v${a.d}`),
);
