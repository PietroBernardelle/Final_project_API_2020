# Final project: Algorithm and Principles of Computer Science Course.
One of the three final projects, with the one of Digital Logic Design and the Software Engineering one, that concur to the final bachelor mark in "Engineering of Computing Systems" held by **Politecnico di Milano**.

**Teacher** : Alessandro Barenghi 

**Final Score** : 30/30 cum laude

## Requirements

Il progetto consiste nell’implementare un semplice editor di testi. L’editor considera un documento come una sequenza di righe, di dimensione arbitraria, numerate a partire da uno.

L’interfaccia dell’editor è costituita da comandi testuali, terminati da un carattere di “a capo”. I comandi possono essere seguiti da una porzione di testo, costituita da una o più righe, terminata da un carattere . (punto) che compare come unico carattere sulla riga successiva. I comandi sono costituiti da un’unica lettera, preceduta opzionalmente da uno o due numeri interi. L’interfaccia dell’editor è liberamente ispirata a quella del tradizionale editor ed.
In alcuni comandi, gli interi che compaiono in essi rappresentano degli speci- ficatori di indirizzo. Più precisamente, uno specificatore di indirizzo è un numero n, espresso in decimale, che indica l’indirizzo della n-esima riga; la prima riga del testo ha indirizzo 1.
I comandi supportati sono i seguenti, con la convenzione che ind1,ind2 indicano due specificatori di indirizzo tali che ind1  ind2 e le parentesi tonde sono introdotte per semplicità di lettura di questo testo, ma non incluse nel comando:

• (ind1,ind2)c

    Cambia il testo presente alle righe comprese tra ind1 ed ind2 (estremi
    inclusi). Il testo che segue il comando deve essere fatto di un numero di
    righe pari a ind2-ind1+1. ind1 deve essere o un indirizzo effettivamente
    presente nel testo, oppure il primo indirizzo dopo l’ultima riga presente
    nel testo (o 1 se il testo è ancora vuoto).
• (ind1,ind2)d

    Cancella le righe comprese tra ind1 ed ind2 (estremi inclusi), spostando
    verso l’alto le righe successive a quella di indirizzo ind2 (se ce ne sono).
    La cancellazione di una riga che non esiste nel testo non ha alcun effetto.
• (ind1,ind2)p

    Stampa le righe tra ind1 ed ind2, inclusi. Laddove non sia presente
    una riga nel testo nella posizione da stampare, viene stampata una riga
    contenente il solo carattere ’.’ seguito da un “a capo”.
• (numero)u

    Effettua l’annullamento (undo) di un numero di comandi (c o d) pari a quello specificato
    tra parentesi tonde (laddove numero è un intero strettamente maggiore di zero). Una sequenza 
    di comandi di undo consecutivi annulla un numero di passi pari alla somma dei passi specificati 
    in ognuno di essi. Se il numero di comandi di cui effettuare l’annullamento è superiore a quello 
    dei comandi eseguiti, vengono annullati tutti i passi. L’esecuzione di un comando di modifica 
    del testo (c, d) dopo un undo cancella gli effetti dei comandi annullati definitivamente.
    Si noti che nel numero dei comandi da annullare si contano anche i comandi che non hanno effetto
    (per esempio la cancellazione di un blocco di righe che non esistono).

 
• (numero)r

Annulla l’effetto di undo per un numero di comandi pari a numero a partire
dalla versione corrente (funzione di redo). Si noti che numero deve essere
un intero strettamente maggiore di zero. 
Una riga di testo fornita in ingresso all’editor può contenere al massimo 1024
caratteri.

 

## Test cases

| Task            | Commands   | Time Limit | Memory limit | Status |
| --------------- | ---------- | :--------: | :----------: | :--------------------------------------------------------: |
| WriteOnly       | c          | 7.4 s      | 3.00 GiB     |[![GREEN](https://placehold.it/15/44bb44/44bb44)](#)        |
| BulkReads       | c          | 1.250 s    | 240 MiB      |[![GREEN](https://placehold.it/15/44bb44/44bb44)](#)        |
| TimeForAChange  | c, d       | 2.100 s    | 540 MiB      |[![GREEN](https://placehold.it/15/44bb44/44bb44)](#)        |
| AlteringHistory | c, d, u    | 2.100 s    | 400 MiB      |[![GREEN](https://placehold.it/15/44bb44/44bb44)](#)        |
| RollingBack     | c, d, u, r | 2.400 s    | 550 MiB      |[![GREEN](https://placehold.it/15/44bb44/44bb44)](#)        |
| RollerCoaster   | c, d, u, r | 2.700 s    | 1.03 GiB     |[![GREEN](https://placehold.it/15/44bb44/44bb44)](#)        |
| Laude           | c, d, u, r | 2.000 s    | 340 MiB      |[![GREEN](https://placehold.it/15/44bb44/44bb44)](#)        |

#### Legend
[![RED](https://placehold.it/15/f03c15/f03c15)]() Task not implementes or implemented and not working &nbsp;&nbsp;&nbsp; [![GREEN](https://placehold.it/15/44bb44/44bb44)]() Task correctly implemented

## Tools Used:
- shell 
- gcc
- sublime text
