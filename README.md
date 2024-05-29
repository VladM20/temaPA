# temaPA - lanParty
### Sistem de Gestionare a Turneelor

#### Prezentare Generală
Acest proiect implementează un sistem de gestionare a turneelor în C. Acesta oferă funcționalități pentru citirea echipelor și jucătorilor dintr-un fișier, gestionarea echipelor în diverse structuri de date, simularea meciurilor și organizarea turneului folosind cozi, stive, arbori binari de căutare (BST) și arbori AVL.

#### Fișiere și Structură

- **main.c**: Conține funcția principală și execută părți ale programului pe baza cerințelor de intrare.
- **teams.c**: Funcții pentru gestionarea echipelor și jucătorilor.
- **liste.c**: Funcții pentru gestionarea listelor de echipe.
- **cozi.c**: Funcții pentru gestionarea cozilor de meciuri.
- **stive.c**: Funcții pentru gestionarea stivelor de echipe.
- **tasks.c**: Funcții pentru gestionarea sarcinilor specifice ale simulării turneului.
- **bst.c**: Funcții pentru gestionarea arborilor binari de căutare.
- **avl.c**: Funcții pentru gestionarea arborilor AVL.
- **definitii.h**: Fișier header cu declarații de funcții și definiții de structuri.

#### Compilare și Execuție

1. **Compilarea Programului:**
   Pentru a compila programul, utilizați comanda:
   ```sh
   make
   ```
   sau următoarea comandă:
   ```sh
   gcc -o tournament main.c teams.c liste.c cozi.c stive.c tasks.c bst.c avl.c -Wall
   ```

2. **Rularea Programului:**
   Programul așteaptă trei argumente din linia de comandă:
   - Fișierul cu cerințe
   - Fișierul de intrare conținând informațiile despre echipe și jucători
   - Fișierul de ieșire pentru a scrie rezultatele

   Exemplu:
   ```sh
   ./tournament requirements.txt input.txt output.txt
   ```

#### Funcționalitate

1. **Gestionarea Echipei și Jucătorilor (teams.c):**
   - `readTeam(FILE *input)`: Citește o echipă dintr-un fișier.
   - `readPlayer(FILE *input)`: Citește un jucător dintr-un fișier.
   - `teamPoints(Team *team)`: Calculează punctele unei echipe.
   - Diverse funcții utilitare pentru alocarea memoriei și gestionarea șirurilor de caractere.

2. **Gestionarea Listelor (liste.c):**
   - `createList(FILE *input, int *numberOfTeams)`: Creează o listă de echipe dintr-un fișier.
   - `listAdd(Team *team, Node **list)`: Adaugă o echipă la o listă.
   - `deleteList(Node **list)`: Șterge întreaga listă de echipe.

3. **Gestionarea Cozilor (cozi.c):**
   - `createQueue()`: Creează o coadă goală.
   - `enQueue(Queue *q, Team *team1, Team *team2)`: Adaugă un meci în coadă.
   - `deQueue(Queue *q, Team **team1, Team **team2)`: Scoate un meci din coadă.

4. **Gestionarea Stivelor (stive.c):**
   - `push(Node **top, Team *team)`: Adaugă o echipă pe stivă.
   - `pop(Node **top)`: Scoate o echipă de pe stivă.
   - `deleteStack(Node **stack)`: Șterge stiva.

5. **Gestionarea Sarcinilor (tasks.c):**
   - `task2(int *numberOfTeams, Node **list)`: Ajustează numărul de echipe la cel mai apropiat număr de putere a lui 2.
   - `task3(FILE *output, int *numberOfTeams, Node **list, Node **last8Teams)`: Simulează meciurile și scrie rezultatele în fișierul de ieșire.
   - `task4(FILE *output, Node *last8Teams, Node **orderedTeams)`: Organizează primele 8 echipe într-un BST și scrie în fișierul de ieșire.
   - `task5(FILE *output, Node *orderedTeams)`: Organizează echipele într-un arbore AVL și scrie echipele de nivel 2 în fișierul de ieșire.

6. **Arbore Binari de Căutare (bst.c):**
   - `insert(TreeNode *node, Team *team)`: Inserează o echipă în BST.
   - `writeBST(FILE *output, TreeNode *root)`: Scrie BST în fișierul de ieșire.

7. **Arbore AVL (avl.c):**
   - `insertAVL(AVLNode *node, Team *team)`: Inserează o echipă în arborele AVL.
   - `writeAVL(FILE *output, AVLNode *root, int level)`: Scrie echipele de nivel 2 din arborele AVL în fișierul de ieșire.

#### Utilitare pentru Debugging
- `printTeams(Node *list)`: Printează echipele și jucătorii lor în consolă.
- `printQ(Queue *q)`: Printează meciurile din coadă în consolă.

#### Fișierul de Cerințe
Fișierul de cerințe (`requirements.txt`) trebuie să conțină 5 linii, fiecare cu un 0 sau 1, indicând dacă sarcina corespunzătoare trebuie executată:
- Sarcina 1: Printează echipele
- Sarcina 2: Șterge echipele cu punctajul cel mai mic până când numărul de echipe este o putere a lui 2
- Sarcina 3: Simulează meciurile și printează câștigătorii
- Sarcina 4: Organizează primele 8 echipe în BST
- Sarcina 5: Organizează echipele în arbore AVL și printează echipele de nivel 2

Exemplu `requirements.txt`:
```
1 1 1 1 1
```

#### Exemplu Format Fișier de Intrare
Fișierul de intrare (`input.txt`) trebuie să conțină numărul de echipe urmat de detalii despre fiecare echipă și jucătorii săi.

Exemplu `input.txt`:
```
4
3 TeamA
Firstname1 Secondname1A 10
Firstname2 Secondname2A 20
Firstname3 Secondname3A 30

3 TeamB
Firstname1 Secondname1B 15
Firstname2 Secondname2B 25
Firstname3 Secondname3B 35

3 TeamC
Firstname1 Secondname1C 20
Firstname1 Secondname2C 30
Firstname1 Secondname3C 40

3 TeamD
Firstname1 Secondname1D 25
Firstname1 Secondname2D 35
Firstname1 Secondname3D 45
```

#### Exemplu de Ieșire
Fișierul de ieșire (`output.txt`) va conține rezultatele sarcinilor pe baza cerințelor specificate.

#### Gestionarea Memoriei
Programul alocă dinamic memorie pentru echipe, jucători și structuri de date. Sunt furnizate funcții pentru a elibera memoria alocată pentru a evita situații de memory leak.

#### Gestionarea Erorilor
Programul include gestionarea de bază a erorilor pentru operațiunile cu fișiere și alocarea memoriei.
