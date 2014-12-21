ssh enabled


UNIVERSITATEA POLITEHNICA  - FACULTATEA DE AUTOMATICA  SI CALCULATOARE

Tema 2 - Snake

Programarea Calculatoarelor - seria CC, an universitar 2014-2015

Publicarea enuntului: 11 decembrie 2014

Ultima modificare a enuntului: 11 decembrie 2014, ora 18:00

Termen de predare: 11 ianuarie 2015, ora 23:55
Nu se accepta temele trimise dupa termen.

1 DESCRIEREA PROBLEMEI
Tema presupune realizarea unui joc de tip Snake. Implementarea se va face pe Linux si veti
utiliza biblioteca grafica ncurses. Miscarea sarpelui va fi controlata de la tastatura, folosind
tastele W A S D (pentru sus, stânga, jos si, respectiv, dreapta). Pentru iesirea din aplicatie, se
va folosi tasta Q.

2 CERINTE
Tinând cont ca nu va este impus un aspect anume pentru joc, ci doar anumite functionalitati
necesare pentru obtinerea punctajului mentionat, veti primi puncte bonus pentru aspec-
tul "artistic" al aplicatiei si pentru diverse îmbunatatiri sau idei originale pe care le aduceti.
Precizati-le în README.
Exemple de functionalitati suplimentare: afisarea scorului sau o lista de "high-scores" afisata
la finalul jocului - se poate cere numele jucatorului pentru a fi introdus în lista de scoruri.

2.1 CERINTA 1 [30 DE PUNCTE ]
Creati un joc de Snake care permite mutarea sarpelui la apasarea unei taste. Trebuie sa aveti
un chenar (a carui dimensiune o alegeti voi, dar sa fie suficient de mare) ale carui margini nu
pot fi depasite. Sarpele va avea o lungime intiala (de exemplu, cinci patratele) si va putea fi
mutat numai în interiorul chenarului desenat.
Jocul se opreste la apasarea unei taste prestabilite (de iesire din joc) sau atunci când sarpele
face o mutare invalida (se loveste de chenar sau de el însusi).

2.2 CERINTA 2 [20 DE PUNCTE ]
Adaugati aplicatiei generarea aleatoare a câte unui patratel cu "hrana" pentru sarpe. De
fiecare data când aceasta este consumata (capul sarpelui ajunge în aceeasi pozitie cu hrana
si aceasta dispare), va fi generat un alt patrat cu hrana. Prin consumarea unui patratel de
hrana, sarpele creste cu o unitate.

2.3 CERINTA 3 [20 DE PUNCTE ]
Adaugati aplicatiei posibilitatea de a generara obstacole (tot aleator) înainte de începutul
jocului. Sarpele nu are voie sa se loveasca de ele - daca sarpele atinge un obstacol, jocul
se termina.
La lansarea aplicatiei, se va afisa un meniu care va permite alegerea unuia dintre modurile:
cu obstacole sau fara obstacole.

2.4 CERINTA 4 [20 DE PUNCTE ]
Implementati miscarea automata a sarpelui: acesta se misca continuu, cu o anumita viteza,
iar la apasarea unei taste i se schimba directia.

2.5 CERINTA 5 [10 PUNCTE ]
Se doreste accelerarea miscarii în functie de lungimea sarpelui. Se porneste cu o viteza initiala
si, pe masura ce lungimea sarpelui creste, se mareste si viteza (de exemplu, la fiecare doua
patratele de lungime câstigate).
 ̆
3 PRECIZARI
• Punctaj: 150 de puncte = 100p (cerintele 1-5) + 30p (Bonus) + 20p (README si "coding
style") - punctajul pentru obtinerea punctajului legat de scrierea codului, cititi sectiunea
dedicata de pe site-ul de laboratoare.
• Pentru obtinerea bibliotecii ncurses (pe o distributie de Linux bazata pe Debian):
apt-get install libncurses5-dev
• Rezolvarea va porni de la arhiva temei - aflata pe site-ul de cursuri.
• Pentru cerintele 4 si 5 se va utiliza functia select - studiati codul sursa din arhiva.
• Va recomandam sa utilizati structuri pentru a clarifica cât mai mult solutia voastra (de
exemplu, pentru sarpe sau pentru chenar).
• Pentru mai multe detalii despre ncurses, aveti la dispozitie documentatia oficiala si o
serie de exemple.
• Tema va fi rezolvata obligatoriu în limbajul C. Nu folositi elemente ale limbajului C++.
2• Veti urca pe site-ul de cursuri o arhiva zip cu denumirea <grupa>_<nume>_<prenume>.zip
(de exemplu, 313CC_Popescu_Maria) care va contine fisierele sursa, Makefile si README.
Fisierele trebuie sa se regaseasca direct în radacina arhivei.
• Precizati în README cerintele rezolvate si modul în care se interactioneaza cu aplicatia
voastra. De asemenea, explicati, pe scurt, cum ati realizat implementarea cerintelor.
• Temele care nu compileaza la comanda make si care nu ruleaza la comanda make run
nu vor fi punctate.
• Temele sunt individuale. Copierea va fi sanctionata - anularea punctajului temei pen-
tru toti studentii implicati.
3
