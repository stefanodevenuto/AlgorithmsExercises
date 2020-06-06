## Esercizio 2

### Libreria

La prima constatazione che salta subito all'occhio è che la funzione che implementa il calcolo della distanza di edit senza l'utilizzo della memoization non riesce nemmeno entro i 10 minuti a fornire un risultato.

Da ciò quindi si è convertito il metodo sopracitato all'utilizzo della programmazione dinamica, attraverso lo svolgimento dei seguenti punti:

1. Caratterizzazione della struttura di una soluzione

2. Individuazione di una soluzione ricorsiva

3. Eliminazione delle ripetazioni attraverso memoization

Il punto 1 è già svolto all'interno del file che riporta il mandato, mentre il punto 2 è stato completato per la risoluzione della variante non dinamica,

Il punto 3, invece, è stato implementato attraverso l'utilizzo di una matrice (della grandezza della prima stringa da esaminare per la seconda) inizialmente contenente in ogni posizione -1.

Ogni volta che un risultato intermedio viene restituito, esso viene salvato all'interno della matrice, nella posizione relativa all'indice della prima stringa e della seconda (i quali indicano rispettivamente a che punto dell' analisi delle stringhe si è arrivati).

Così facendo, prima di effettuare una nuova chiamata ricorsiva si controlla se il risultato è già stato computato, altrimenti si procede al calcolo e al succesivo salvataggio.

### Applicazione

L'applicazione restituisce un risultato (compreso di lettura, caricamento e di stampa) in **22.16 secondi**.

Questa soluzione, rispetto alla seconda che verrà proposta, calcola la distanza di edit per ogni parola da correggere con ogni altra parola nel dizionario (si interrompe prima solo se incontra una parola per cui l'edit distance è pari a 0) salvandola in una struttura ArrayList, calcola il minimo per ogni struttura così creata e restituisce la lista delle stringhe minime. La complessità quindi, definito $`m`$ come le parole nel file da correggere ed $`n`$ come le parole nel dizionario e supponendo che ogni parola abbia la stessa probabilità di essere selezionata (definendo quindi $`p`$ come $`n/m`$), è pari a  $`\Omicron(n \cdot m) + \Omicron(p \cdot m)`$.

La seconda soluzione, invece, calcola l'edit distance per ogni parola da correggere con ogni altra parola nel dizionario **ma**, nel momento in cui trova una parola con distanza minore, pulisce la lista e inserisce solo più parole con tale distanza (interrompendosi a edit distance pari a 0).
Rispetto quindi alla prima soluzione non servono funzioni per il calcolo del minimo nella lista e per il riperimento di tali parole.
D'altro canto, la funzione ``` clear() ```per svuotare l' ArrayList ha complessità pari a, definendo $`n`$ come il numero di elementi nella lista, $\Omicron(n)$.

Con la seconda soluzione, quindi, l'applicazione restituisce un risultato (compreso di lettura, caricamento e di stampa) in **20.32 secondi**.