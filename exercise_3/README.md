## Esercizio 3

Dall'esecuzione avente come input il file hashes.csv risultano i seguenti tempi:

|                              |     Tempo    |
|:----------------------------:|:------------:|
| **Caricamento HashMap**      | 5.19 secondi |
| **Caricamento Array Statico**| 1.31 secondi |
| **Ordinamento Array**        | 1.07 secondi |
| **Reperimento HashMap**      | 1.95 secondi |
| **Reperimento Array**        | 6.11 secondi |
<br>
I risultati ottenuti rispecchiano le aspettative: 

1. i tempi di caricamento dell'array sono inferiori a quelli della struttura HashMap (sia per l'accesso diretto sicuro dato dall'array sia per la funzione ``` rehash() ```, atta al reperimento più veloce delle associazioni nelle future interrogazioni).

2. Il reperimento delle associazioni è più veloce nell' HashMap, dovuto ad un tempo di calcolo medio, per quanto riguarda la ricerca, pari a $`\Omicron(1)`$ (contro una complessità pari a $`\Omicron(\log n)`$ nella struttura sequenziale)