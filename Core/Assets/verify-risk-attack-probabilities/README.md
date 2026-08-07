# Verifica Probabilità di Conquista - Risiko

Applicazione web per verificare le probabilità di attacco nel gioco Risiko.

## Prerequisiti

- [Node.js](https://nodejs.org/) (versione 18 o superiore)
- [npm](https://www.npmjs.com/) (incluso con Node.js)

## Installazione

Aprire il terminale nella cartella del progetto e installare le dipendenze:

```bash
npm install
```

## Sviluppo

Per avviare il server di sviluppo:

```bash
npm run dev
```

L'applicazione sarà disponibile su: [http://localhost:5173](http://localhost:5173)

Premere `Ctrl + C` per fermare il server.

## Build per Produzione

Per generare la versione di produzione:

```bash
npm run build
```

I file verranno generati nella cartella `dist/`.

## Tecnologie

- **React 19** - Interfaccia utente
- **Vite** - Build tool e server di sviluppo
- **TypeScript** - Tipizzazione
- **Tailwind CSS** - Styling

## Struttura del Progetto

```
src/
├── App.tsx          # Componente principale
├── main.tsx         # Entry point
├── index.css        # Stili globali
├── data/            # Dati di gioco
└── utils/           # Utility functions
```