// ---------------------------------------------------------------------------
// Risk battle probability engine + game data
// ---------------------------------------------------------------------------

// Territory ownership / army counts read from the provided file.
export interface Territory {
  name: string;
  owner: "Red" | "Blue" | "Yellow" | "Green";
  armies: number;
}

export const TERRITORIES: Territory[] = [
  { name: "Alaska", owner: "Red", armies: 5 },
  { name: "Northwest Territory", owner: "Blue", armies: 4 },
  { name: "Greenland", owner: "Blue", armies: 3 },
  { name: "Alberta", owner: "Red", armies: 4 },
  { name: "Ontario", owner: "Blue", armies: 5 },
  { name: "Quebec", owner: "Blue", armies: 4 },
  { name: "Western US", owner: "Red", armies: 4 },
  { name: "Eastern US", owner: "Yellow", armies: 5 },
  { name: "Central America", owner: "Yellow", armies: 3 },
  { name: "Venezuela", owner: "Yellow", armies: 3 },
  { name: "Brazil", owner: "Green", armies: 6 },
  { name: "Peru", owner: "Green", armies: 4 },
  { name: "Argentina", owner: "Green", armies: 3 },
  { name: "Iceland", owner: "Red", armies: 3 },
  { name: "Great Britain", owner: "Red", armies: 4 },
  { name: "Scandinavia", owner: "Red", armies: 4 },
  { name: "Northern Europe", owner: "Blue", armies: 4 },
  { name: "Western Europe", owner: "Yellow", armies: 5 },
  { name: "Southern Europe", owner: "Yellow", armies: 4 },
  { name: "Ukraine", owner: "Blue", armies: 5 },
  { name: "North Africa", owner: "Green", armies: 5 },
  { name: "Egypt", owner: "Yellow", armies: 4 },
  { name: "East Africa", owner: "Green", armies: 4 },
  { name: "Congo", owner: "Green", armies: 3 },
  { name: "South Africa", owner: "Green", armies: 3 },
  { name: "Madagascar", owner: "Green", armies: 2 },
  { name: "Ural", owner: "Red", armies: 4 },
  { name: "Siberia", owner: "Blue", armies: 6 },
  { name: "Yakutsk", owner: "Blue", armies: 4 },
  { name: "Kamchatka", owner: "Red", armies: 5 },
  { name: "Irkutsk", owner: "Blue", armies: 4 },
  { name: "Mongolia", owner: "Blue", armies: 5 },
  { name: "Japan", owner: "Red", armies: 4 },
  { name: "Afghanistan", owner: "Red", armies: 4 },
  { name: "Middle East", owner: "Yellow", armies: 5 },
  { name: "India", owner: "Yellow", armies: 5 },
  { name: "China", owner: "Red", armies: 8 },
  { name: "Siam", owner: "Green", armies: 4 },
  { name: "Indonesia", owner: "Green", armies: 4 },
  { name: "New Guinea", owner: "Green", armies: 3 },
  { name: "Western Australia", owner: "Green", armies: 3 },
  { name: "Eastern Australia", owner: "Green", armies: 3 },
];

export const territoryMap: Record<string, Territory> = Object.fromEntries(
  TERRITORIES.map((t) => [t.name, t]),
);

// ---------------------------------------------------------------------------
// Single-round outcome probabilities (exact fractions).
// These are the standard Risk combat probabilities: attacker rolls up to
// 3 dice, defender up to 2, ties go to the defender.
// ---------------------------------------------------------------------------

// 3 attacker dice vs 2 defender dice  (out of 7776 permutations)
const A3D2_DEF_LOSES2 = 2890 / 7776; // 0.371656
const A3D2_ATT_LOSES2 = 2275 / 7776; // 0.292567
const A3D2_SPLIT = 2611 / 7776; // 0.335777

// 2 attacker dice vs 2 defender dice  (out of 1296)
const A2D2_DEF_LOSES2 = 295 / 1296; // 0.227623
const A2D2_ATT_LOSES2 = 581 / 1296; // 0.448302
const A2D2_SPLIT = 420 / 1296; // 0.324074

// 1 attacker die vs 2 defender dice  (out of 216)
const A1D2_DEF_LOSES1 = 55 / 216; // 0.254630
const A1D2_ATT_LOSES1 = 161 / 216; // 0.745370

// 3 attacker dice vs 1 defender die (out of 216)
const A3D1_DEF_LOSES1 = 0.6597222222;
// 2 attacker dice vs 1 defender die
const A2D1_DEF_LOSES1 = 0.5787037037;
// 1 attacker die vs 1 defender die
const A1D1_DEF_LOSES1 = 0.4166666667;

/**
 * Exact probability that the attacker conquers the territory,
 * given `a` attacking armies (armies actually committed = armies_on_tile - 1)
 * and `d` defending armies. Computed with a memoised recursion over the
 * full battle (attacker keeps attacking until one side is wiped out).
 */
const memo = new Map<string, number>();
export function conquerProbability(a: number, d: number): number {
  if (d <= 0) return 1;
  if (a <= 0) return 0;
  const key = `${a}:${d}`;
  const cached = memo.get(key);
  if (cached !== undefined) return cached;

  let p = 0;
  if (a >= 3 && d >= 2) {
    p =
      A3D2_DEF_LOSES2 * conquerProbability(a, d - 2) +
      A3D2_ATT_LOSES2 * conquerProbability(a - 2, d) +
      A3D2_SPLIT * conquerProbability(a - 1, d - 1);
  } else if (a === 2 && d >= 2) {
    p =
      A2D2_DEF_LOSES2 * conquerProbability(a, d - 2) +
      A2D2_ATT_LOSES2 * conquerProbability(a - 2, d) +
      A2D2_SPLIT * conquerProbability(a - 1, d - 1);
  } else if (a === 1 && d >= 2) {
    p =
      A1D2_DEF_LOSES1 * conquerProbability(a, d - 1) +
      A1D2_ATT_LOSES1 * conquerProbability(a - 1, d);
  } else if (a >= 3 && d === 1) {
    p =
      A3D1_DEF_LOSES1 * 1 + (1 - A3D1_DEF_LOSES1) * conquerProbability(a - 1, d);
  } else if (a === 2 && d === 1) {
    p =
      A2D1_DEF_LOSES1 * 1 + (1 - A2D1_DEF_LOSES1) * conquerProbability(a - 1, d);
  } else {
    // a === 1 && d === 1
    p = A1D1_DEF_LOSES1;
  }

  memo.set(key, p);
  return p;
}

// ---------------------------------------------------------------------------
// Reference table from the Risk Fandom Wiki ("Probabilities of attacker
// winning a whole battle"). Rows = defending armies, cols = attacking armies.
// Used only for display / cross-checking. Values are the wiki's rounded %.
// ---------------------------------------------------------------------------
export const WIKI_TABLE: (number | null)[][] = [
  //  att:  1     2     3     4     5     6     7     8     9     10
  /* d1 */ [42, 75, 92, 97, 99, 100, 100, 100, 100, 100],
  /* d2 */ [11, 36, 66, 79, 89, 93, 97, 98, 99, 99],
  /* d3 */ [3, 21, 47, 64, 77, 86, 91, 95, 97, 98],
  /* d4 */ [1, 9, 31, 48, 64, 74, 83, 89, 93, 95],
  /* d5 */ [0, 5, 21, 36, 51, 64, 74, 82, 87, 92],
  /* d6 */ [0, 2, 13, 25, 40, 52, 64, 73, 81, 86],
  /* d7 */ [0, 1, 8, 18, 30, 42, 54, 64, 73, 80],
  /* d8 */ [0, 0, 5, 12, 22, 33, 45, 55, 65, 72],
  /* d9 */ [0, 0, 3, 9, 16, 26, 36, 46, 56, 65],
  /* d10 */ [0, 0, 3, 6, 12, 19, 29, 38, 48, 57],
];

// ---------------------------------------------------------------------------
// The attacks claimed in the prompt, with the player's stated win %.
// ---------------------------------------------------------------------------
export interface Attack {
  from: string;
  to: string;
  claimed: number; // percentage stated by the user
}

export const ATTACKS: Attack[] = [
  { from: "China", to: "Siam", claimed: 83.6 },
  { from: "China", to: "Mongolia", claimed: 73.9 },
  { from: "China", to: "India", claimed: 72.3 },
  { from: "China", to: "Siberia", claimed: 62.9 },
  { from: "Western US", to: "Central America", claimed: 49.3 },
  { from: "Alaska", to: "Northwest Territory", claimed: 49.1 },
  { from: "Kamchatka", to: "Yakutsk", claimed: 49.1 },
  { from: "Kamchatka", to: "Irkutsk", claimed: 49.0 },
  { from: "Kamchatka", to: "Mongolia", claimed: 34.9 },
  { from: "Great Britain", to: "Northern Europe", claimed: 33.6 },
  { from: "Alberta", to: "Northwest Territory", claimed: 31.3 },
  { from: "Scandinavia", to: "Northern Europe", claimed: 27.8 },
  { from: "Western US", to: "Ontario", claimed: 22.3 },
  { from: "Afghanistan", to: "Middle East", claimed: 21.1 },
  { from: "Japan", to: "Mongolia", claimed: 21.0 },
  { from: "Afghanistan", to: "Ukraine", claimed: 20.9 },
  { from: "Great Britain", to: "Western Europe", claimed: 20.7 },
  { from: "Ural", to: "Ukraine", claimed: 20.4 },
  { from: "Afghanistan", to: "India", claimed: 20.3 },
  { from: "Scandinavia", to: "Ukraine", claimed: 20.3 },
  { from: "Western US", to: "Eastern US", claimed: 20.2 },
  { from: "Alberta", to: "Ontario", claimed: 19.2 },
  { from: "Iceland", to: "Greenland", claimed: 18.8 },
  { from: "Ural", to: "Siberia", claimed: 14.6 },
];

export interface AnalyzedAttack extends Attack {
  attackerArmies: number;
  defenderArmies: number;
  a: number; // committed attacking armies (armies - 1)
  d: number; // defending armies
  actual: number; // exact conquer probability, %
  diff: number; // claimed - actual
}

export function analyzeAttacks(): AnalyzedAttack[] {
  return ATTACKS.map((atk) => {
    const attacker = territoryMap[atk.from];
    const defender = territoryMap[atk.to];
    const a = attacker.armies - 1;
    const d = defender.armies;
    const actual = conquerProbability(a, d) * 100;
    return {
      ...atk,
      attackerArmies: attacker.armies,
      defenderArmies: defender.armies,
      a,
      d,
      actual,
      diff: atk.claimed - actual,
    };
  });
}
