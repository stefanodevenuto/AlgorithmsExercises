## Esercizio 1

Questa è la tabella che riporta i dati ottenuti attraverso l'esecuzione dei due algoritmi sul dataset fornito.

| x |  Primo campo  |  Secondo Campo  |  Terzo Campo  |
|---|---|---|---|---|
| **Quick-Sort**| Test Fallito | 20.85 secondi | 24.77 secondi |
| **Insertion Sort**| Test Fallito | Test Fallito | Test Fallito |

I dati relativi all' **Insertion-Sort** non fanno emergere perplessità: dal momento che la complessità di tale algoritmo nel caso peggiore è pari a $`\Omicron(n^2)`$, e sapendo che il file csv contiene 20.000.000 di record, il numero di operazioni risultanti è circa 400.000.000.000.000. E' quindi impensabile che esso possa finire prima di 10 minuti.

Per quanto riguarda il **Quick-Sort**, invece, solo i dati realtivi al secondo e al terzo campo sono coerenti con ciò che mi sarei aspettato, mentre il terzo, continuando ben oltre i 10 minuti, mi soprende.

Le supposizioni che ho fatto sono state inizialmente indirizzate verso il "metodo" con cui due stringhe vengono confrontate, la ``` strcmp() ```, più lenta rispetto al confronto tra due numeri, e succesivamente verso la funzione Partition così implementata.
La *prima versione*, infatti (quella riportata sulle slide di teoria), non riusciva a trattare in maniera efficiente quelli che sono valori ripetuti o prefissi comuni all'interno del dataset.

Per questo motivo la *seconda versione* della funzione Partition divide l'array dato in 3 zone differenti: gli elementi minori del pivot, quelli pari al pivot e quelli maggiori.

Con questa nuova implementazione (che non altera la complessità asintotica) i tempi risultanti sono:

| x |  Primo campo  |  Secondo Campo  |  Terzo Campo  |
|---|---|---|---|---|
| **Quick-Sort**| 20.83 secondi | 29.40 secondi | 32.94 secondi |