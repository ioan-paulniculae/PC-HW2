#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <ncurses.h>

#define NO_STOP 1
#define HEAD 0
#define UNITY 1000
#define Y 21
#define X 22

typedef struct {
  
    unsigned x;
    unsigned y;
} PUNCT;

typedef struct {

    PUNCT *p;

    unsigned last_x;
    unsigned last_y;

    unsigned dim;
    unsigned size;

    unsigned speed;

    unsigned level; // 1 - easy 5 - insane
    char input;
    char lastinput;
} SNAKE;

void init_window (PUNCT *gboard) {

    //initializare
    raw ();
    getmaxyx (stdscr, gboard->y, gboard->x);

    //mesaj initial
    attron (A_UNDERLINE | A_BOLD);
       
        mvprintw (gboard->y / 3, gboard->x / 2 - 5, "SNAKE");
        mvprintw (gboard->y / 3 + 1, gboard->x / 2 - 5, "W - inainte");
        mvprintw (gboard->y / 3 + 2, gboard->x / 2 - 5, "A - stanga");
        mvprintw (gboard->y / 3 + 3, gboard->x / 2 - 5, "S - jos");
        mvprintw (gboard->y / 3 + 4, gboard->x / 2 - 5, "D - dreapta");
    
    attroff (A_UNDERLINE | A_BOLD);

  //ascundere cursor
    curs_set (0);

  //ascundem inputul
    noecho ();



    mvprintw (gboard->y / 3 + 6, gboard->x / 2 - 5, "Apasa orice tasta");
    
    getch ();
    clear ();
}

unsigned main_menu (PUNCT *gboard) {

    PUNCT p;

    p.x = gboard->x / 2 - 5;
    p.y = gboard->y / 3;

    clear ();
    
    attron (A_UNDERLINE | A_BOLD);
        mvaddstr (gboard->y / 3, p.x, "NEW GAME");
    attroff (A_UNDERLINE | A_BOLD);

    mvaddstr (gboard->y / 3 + 1, p.x, "OPTIONS");
    mvaddstr (gboard->y / 3 + 2, p.x, "EXIT");

    char c;

    while (NO_STOP) {

        c = getch ();
        c = tolower (c);

        switch (c) {
            case 'w':
        
                if (p.y > gboard->y / 3) {
               
                    p.y--;
                }

            break;

            case 's':

                if (p.y < gboard->y / 3 + 2) {
                
                    p.y++;
                }

            break;

            case '\n':
           
                clear ();
                if (p.y == gboard->y / 3){
                    
                    return 2;
                }

                if (p.y ==gboard ->y / 3 + 1){
                    
                    return 1;
                }

                return 0;
            break;

            default:
            break;
        }

        if (p.y == gboard->y / 3){
               
            clear ();
            
            attron (A_UNDERLINE | A_BOLD);
            
                mvaddstr (gboard->y / 3, p.x, "NEW GAME");
            
            attroff (A_UNDERLINE | A_BOLD);

            mvaddstr (gboard->y / 3 + 1, p.x, "OPTIONS");
            mvaddstr (gboard->y / 3 + 2, p.x, "EXIT");

        }

        if (p.y == gboard->y / 3 + 1){
                
            clear ();
            
            mvaddstr (gboard->y / 3, p.x, "NEW GAME");

            attron (A_UNDERLINE | A_BOLD);
            
                mvaddstr (gboard->y / 3 + 1, p.x, "OPTIONS");
            
            attroff (A_UNDERLINE | A_BOLD);

            mvaddstr (gboard->y / 3 + 2, p.x, "EXIT");

        }

        if(p.y == gboard->y / 3 + 2){

            clear ();

            mvaddstr (gboard->y / 3, p.x, "NEW GAME");
            mvaddstr (gboard->y / 3 + 1, p.x, "OPTIONS");

            attron (A_UNDERLINE | A_BOLD);

                mvaddstr (gboard->y / 3 + 2, p.x, "EXIT");
            
            attroff (A_UNDERLINE | A_BOLD);
        }

        refresh ();
    }

    clear ();

    return 1;
}

//functie care permite utilizatorului sa aleaga nivelul de 
//dificultate si dimensiunea initiala
void customise (SNAKE *snake) {

    char input;
    PUNCT coord;

    coord.x = X;
    coord.y = Y;

    clear ();

    attron(A_UNDERLINE);
    
        mvprintw (Y - 1, X - 2, "DIFFICULTY: %d", snake->level);
    attroff(A_UNDERLINE);

    mvaddch (Y, X, '1');
    mvaddch (Y, X + 2, '2');
    mvaddch (Y, X + 4, '3');
    mvaddch (Y, X + 6, '4');
    mvaddch (Y, X + 8, '5');
    
    attron(A_UNDERLINE);
        
        mvprintw (Y + 1, X - 2, "INITIAL SIZE: %d", snake->size);
    attroff(A_UNDERLINE);

    mvaddch (Y + 2, X, '1');
    mvaddch (Y + 2, X + 2, '2');
    mvaddch (Y + 2, X + 4, '3');
    mvaddch (Y + 2, X + 6, '5');
    mvaddch (Y + 2, X + 8, '7');

    attron(A_UNDERLINE);
        
        mvprintw(Y + 3, X - 2, "RETURN TO MAIN MENU");
    attroff(A_UNDERLINE);

    while (NO_STOP) {

        input = getch();
        input = tolower (input);
        
        switch (input){

            case 'w':

                switch(coord.y){

                    case Y:
                    break;

                    case Y + 2:

                        coord.y -= 2;
                    break;

                    case X + 2:

                        coord.y -= 1;

                    break;
                }
            break;

            case 'a':

                if (coord.x != X){
                    coord.x -= 2;
                }
            break;

            case 's':

                switch(coord.y){

                    case Y:

                        coord.y += 2;
                    break;

                    case Y + 2:

                        coord.y += 1;
                    break;

                    case X + 2:
                    break;
                }
            break;

            case 'd':

                if (coord.x != X + 8){
                    coord.x += 2;
                }
            break;

            case '\n':
            break;   
        }

        switch (coord. y){

            case Y:

                switch (coord.x){

                    case X:

                        attron(A_UNDERLINE);
    
                            mvprintw (Y - 1, X - 2, "DIFFICULTY: %d", snake->level);
                        attroff(A_UNDERLINE);

                        attron(A_STANDOUT);
                            mvaddch (Y, X, '1');
                        attroff(A_STANDOUT);
                        mvaddch (Y, X + 2, '2');
                        mvaddch (Y, X + 4, '3');
                        mvaddch (Y, X + 6, '4');
                        mvaddch (Y, X + 8, '5');
    
                        attron(A_UNDERLINE);
        
                            mvprintw (X, X - 2, "INITIAL SIZE: %d", snake->size);
                        attroff(A_UNDERLINE);

                        mvaddch (Y + 2, X, '1');
                        mvaddch (Y + 2, X + 2, '2');
                        mvaddch (Y + 2, X + 4, '3');
                        mvaddch (Y + 2, X + 6, '5');
                        mvaddch (Y + 2, X + 8, '7');

                        attron(A_UNDERLINE);
        
                            mvprintw(Y + 3, X - 2, "RETURN TO MAIN MENU");
                        attroff(A_UNDERLINE);

                        if (input == '\n'){
                            snake->level = 1;
                        }

                        refresh();
                    break;

                    case X + 2:

                        attron(A_UNDERLINE);
    
                            mvprintw (Y - 1, X - 2, "DIFFICULTY: %d", snake->level);
                        attroff(A_UNDERLINE);

                        mvaddch (Y, X, '1');
                        attron(A_STANDOUT);
                            mvaddch (Y, X + 2, '2');
                        attroff(A_STANDOUT);
                        mvaddch (Y, X + 4, '3');
                        mvaddch (Y, X + 6, '4');
                        mvaddch (Y, X + 8, '5');
    
                        attron(A_UNDERLINE);
        
                            mvprintw (X, X - 2, "INITIAL SIZE: %d", snake->size);
                        attroff(A_UNDERLINE);

                        mvaddch (Y + 2, X, '1');
                        mvaddch (Y + 2, X + 2, '2');
                        mvaddch (Y + 2, X + 4, '3');
                        mvaddch (Y + 2, X + 6, '5');
                        mvaddch (Y + 2, X + 8, '7');

                        attron(A_UNDERLINE);
        
                            mvprintw(Y + 3, X - 2, "RETURN TO MAIN MENU");
                        attroff(A_UNDERLINE);

                        if (input == '\n'){
                            snake->level = 2;
                        }

                        refresh();
                    break;

                    case X + 4:

                        attron(A_UNDERLINE);
    
                            mvprintw (Y - 1, X - 2, "DIFFICULTY: %d", snake->level);
                        attroff(A_UNDERLINE);

                        mvaddch (Y, X, '1');
                        mvaddch (Y, X + 2, '2');
                        attron(A_STANDOUT);
                            mvaddch (Y, X + 4, '3');
                        attroff(A_STANDOUT);
                        mvaddch (Y, X + 6, '4');
                        mvaddch (Y, X + 8, '5');
    
                        attron(A_UNDERLINE);
        
                            mvprintw (X, X - 2, "INITIAL SIZE: %d", snake->size);
                        attroff(A_UNDERLINE);

                        mvaddch (Y + 2, X, '1');
                        mvaddch (Y + 2, X + 2, '2');
                        mvaddch (Y + 2, X + 4, '3');
                        mvaddch (Y + 2, X + 6, '5');
                        mvaddch (Y + 2, X + 8, '7');

                        attron(A_UNDERLINE);
        
                            mvprintw(Y + 3, X - 2, "RETURN TO MAIN MENU");
                        attroff(A_UNDERLINE);

                        if (input == '\n'){
                            snake->level = 3;
                        }

                        refresh();               
                    break;

                    case X + 6:

                        attron(A_UNDERLINE);
    
                            mvprintw (Y - 1, X - 2, "DIFFICULTY: %d", snake->level);
                        attroff(A_UNDERLINE);

                        mvaddch (Y, X, '1');
                        mvaddch (Y, X + 2, '2');
                        mvaddch (Y, X + 4, '3');
                        attron(A_STANDOUT);
                            mvaddch (Y, X + 6, '4');
                        attroff(A_STANDOUT);
                        mvaddch (Y, X + 8, '5');
    
                        attron(A_UNDERLINE);
        
                            mvprintw (X, X - 2, "INITIAL SIZE: %d", snake->size);
                        attroff(A_UNDERLINE);

                        mvaddch (Y + 2, X, '1');
                        mvaddch (Y + 2, X + 2, '2');
                        mvaddch (Y + 2, X + 4, '3');
                        mvaddch (Y + 2, X + 6, '5');
                        mvaddch (Y + 2, X + 8, '7');

                        attron(A_UNDERLINE);
        
                            mvprintw(Y + 3, X - 2, "RETURN TO MAIN MENU");
                        attroff(A_UNDERLINE); 

                        if (input == '\n'){
                            snake->level = 4;
                        }

                        refresh();                   
                    break;

                    case X + 8:

                        attron(A_UNDERLINE);
    
                            mvprintw (Y - 1, X - 2, "DIFFICULTY: %d", snake->level);
                        attroff(A_UNDERLINE);

                        mvaddch (Y, X, '1');
                        mvaddch (Y, X + 2, '2');
                        mvaddch (Y, X + 4, '3');
                        mvaddch (Y, X + 6, '4');
                        attron(A_STANDOUT);
                            mvaddch (Y, X + 8, '5');
                        attroff(A_STANDOUT);
    
                        attron(A_UNDERLINE);
        
                            mvprintw (X, X - 2, "INITIAL SIZE: %d", snake->size);
                        attroff(A_UNDERLINE);

                        mvaddch (Y + 2, X, '1');
                        mvaddch (Y + 2, X + 2, '2');
                        mvaddch (Y + 2, X + 4, '3');
                        mvaddch (Y + 2, X + 6, '5');
                        mvaddch (Y + 2, X + 8, '7');

                        attron(A_UNDERLINE);
        
                            mvprintw(Y + 3, X - 2, "RETURN TO MAIN MENU");
                        attroff(A_UNDERLINE);

                        if (input == '\n'){
                            snake->level = 5;
                        }

                        refresh();
                    break;
                }
            break;

            case Y + 2:

                switch (coord.x){

                    case X:

                        attron(A_UNDERLINE);
    
                            mvprintw (Y - 1, X - 2, "DIFFICULTY: %d", snake->level);
                        attroff(A_UNDERLINE);

                        mvaddch (Y, X, '1');
                        mvaddch (Y, X + 2, '2');
                        mvaddch (Y, X + 4, '3');
                        mvaddch (Y, X + 6, '4');
                        mvaddch (Y, X + 8, '5');
    
                        attron(A_UNDERLINE);
        
                            mvprintw (X, X - 2, "INITIAL SIZE: %d", snake->size);
                        attroff(A_UNDERLINE);

                        attron(A_STANDOUT);
                            mvaddch (Y + 2, X, '1');
                        attroff(A_STANDOUT);
                        mvaddch (Y + 2, X + 2, '2');
                        mvaddch (Y + 2, X + 4, '3');
                        mvaddch (Y + 2, X + 6, '5');
                        mvaddch (Y + 2, X + 8, '7');

                        attron(A_UNDERLINE);
        
                            mvprintw(Y + 3, X - 2, "RETURN TO MAIN MENU");
                        attroff(A_UNDERLINE);

                        if (input == '\n'){

                            snake->size = 1;
                        }

                        refresh();
                    break;

                    case X + 2:

                        attron(A_UNDERLINE);
    
                            mvprintw (Y - 1, X - 2, "DIFFICULTY: %d", snake->level);
                        attroff(A_UNDERLINE);

                        mvaddch (Y, X, '1');
                        mvaddch (Y, X + 2, '2');
                        mvaddch (Y, X + 4, '3');
                        mvaddch (Y, X + 6, '4');
                        mvaddch (Y, X + 8, '5');
    
                        attron(A_UNDERLINE);
        
                            mvprintw (X, X - 2, "INITIAL SIZE: %d", snake->size);
                        attroff(A_UNDERLINE);

                        mvaddch (Y + 2, X, '1');
                        attron(A_STANDOUT);
                            mvaddch (Y + 2, X + 2, '2');
                        attroff(A_STANDOUT);
                        mvaddch (Y + 2, X + 4, '3');
                        mvaddch (Y + 2, X + 6, '5');
                        mvaddch (Y + 2, X + 8, '7');

                        attron(A_UNDERLINE);
        
                            mvprintw(Y + 3, X - 2, "RETURN TO MAIN MENU");
                        attroff(A_UNDERLINE);

                        if (input == '\n'){

                            snake->size = 2;
                        }

                        refresh();
                    break;

                    case X + 4:

                        attron(A_UNDERLINE);
    
                            mvprintw (Y - 1, X - 2, "DIFFICULTY: %d", snake->level);
                        attroff(A_UNDERLINE);

                        mvaddch (Y, X, '1');
                        mvaddch (Y, X + 2, '2');
                        mvaddch (Y, X + 4, '3');
                        mvaddch (Y, X + 6, '4');
                        mvaddch (Y, X + 8, '5');
    
                        attron(A_UNDERLINE);
        
                            mvprintw (X, X - 2, "INITIAL SIZE: %d", snake->size);
                        attroff(A_UNDERLINE);

                        mvaddch (Y + 2, X, '1');
                        mvaddch (Y + 2, X + 2, '2');
                        attron(A_STANDOUT);
                            mvaddch (Y + 2, X + 4, '3');
                        attroff(A_STANDOUT);
                        mvaddch (Y + 2, X + 6, '5');
                        mvaddch (Y + 2, X + 8, '7');

                        attron(A_UNDERLINE);
        
                            mvprintw(Y + 3, X - 2, "RETURN TO MAIN MENU");
                        attroff(A_UNDERLINE);

                        if (input == '\n'){

                            snake->size = 3;
                        }

                        refresh();
                    break;

                    case X + 6:

                        attron(A_UNDERLINE);
    
                            mvprintw (Y - 1, X - 2, "DIFFICULTY: %d", snake->level);
                        attroff(A_UNDERLINE);

                        mvaddch (Y, X, '1');
                        mvaddch (Y, X + 2, '2');
                        mvaddch (Y, X + 4, '3');
                        mvaddch (Y, X + 6, '4');
                        mvaddch (Y, X + 8, '5');
    
                        attron(A_UNDERLINE);
        
                            mvprintw (X, X - 2, "INITIAL SIZE: %d", snake->size);
                        attroff(A_UNDERLINE);

                        mvaddch (Y + 2, X, '1');
                        mvaddch (Y + 2, X + 2, '2');
                        mvaddch (Y + 2, X + 4, '3');
                        attron(A_STANDOUT);
                            mvaddch (Y + 2, X + 6, '5');
                        attroff(A_STANDOUT);
                        mvaddch (Y + 2, X + 8, '7');

                        attron(A_UNDERLINE);
        
                            mvprintw(Y + 3, X - 2, "RETURN TO MAIN MENU");
                        attroff(A_UNDERLINE);

                        if (input == '\n'){

                            snake->size = 5;
                        }

                        refresh();
                    break;

                    case X + 8:

                        attron(A_UNDERLINE);
    
                            mvprintw (Y - 1, X - 2, "DIFFICULTY: %d", snake->level);
                        attroff(A_UNDERLINE);

                        mvaddch (Y, X, '1');
                        mvaddch (Y, X + 2, '2');
                        mvaddch (Y, X + 4, '3');
                        mvaddch (Y, X + 6, '4');
                        mvaddch (Y, X + 8, '5');
    
                        attron(A_UNDERLINE);
        
                            mvprintw (X, X - 2, "INITIAL SIZE: %d", snake->size);
                        attroff(A_UNDERLINE);

                        mvaddch (Y + 2, X, '1');
                        mvaddch (Y + 2, X + 2, '2');
                        mvaddch (Y + 2, X + 4, '3');
                        mvaddch (Y + 2, X + 6, '5');
                        attron(A_STANDOUT);
                            mvaddch (Y + 2, X + 8, '7');
                        attroff(A_STANDOUT);

                        attron(A_UNDERLINE);
        
                            mvprintw(Y + 3, X - 2, "RETURN TO MAIN MENU");
                        attroff(A_UNDERLINE);

                        if (input == '\n'){

                            snake->size = 7;
                        }

                        refresh();
                    break;
                }
            break;

            case X + 2:

                        attron(A_UNDERLINE);
    
                            mvprintw (Y - 1, X - 2, "DIFFICULTY: %d", snake->level);
                        attroff(A_UNDERLINE);

                        mvaddch (Y, X, '1');
                        mvaddch (Y, X + 2, '2');
                        mvaddch (Y, X + 4, '3');
                        mvaddch (Y, X + 6, '4');
                        mvaddch (Y, X + 8, '5');
    
                        attron(A_UNDERLINE);
        
                            mvprintw (X, X - 2, "INITIAL SIZE: %d", snake->size);
                        attroff(A_UNDERLINE);

                        mvaddch (Y + 2, X, '1');
                        mvaddch (Y + 2, X + 2, '2');
                        mvaddch (Y + 2, X + 4, '3');
                        mvaddch (Y + 2, X + 6, '5');
                        mvaddch (Y + 2, X + 8, '7');

                        attron(A_UNDERLINE | A_STANDOUT);
        
                            mvprintw(Y + 3, X - 2, "RETURN TO MAIN MENU");
                        attroff(A_UNDERLINE | A_STANDOUT);

                        if (input == '\n'){

                            return;
                        }
            break;
        }

        refresh();

    }
}

//functie care creaza un chenar de dim_x * dim_y
void create_gameboard (unsigned dim_x, unsigned dim_y) {

    int i;

    //sus
    for (i = 1; i < dim_x + 1; i++) {
      
        if (i % 2) {
         
            mvaddch (0, i, '#');
        }
        else {
         
            mvaddch (0, i, ' ');
        }
    }
    
    //dreapta
    for (i = 0; i < dim_y; i++) {
        
        mvaddch (i, dim_x, '#');
    }

    //jos
    for (i = 1; i < dim_x + 1; i++) {
        
        if (i % 2) {
        
            mvaddch (dim_y, i, '#');
        }
        else {

            mvaddch (dim_y, i, ' ');
        }
    }

    //stanga
    for (i = 0; i < dim_y; i++){

        mvaddch (i, 1, '#');
    }
}

void init_game (SNAKE *snake, PUNCT *gboard){

    getmaxyx (stdscr, gboard->y, gboard->x); //aflam dimensiunile maxime ale tablei de joc

    gboard->x--;      //din motive de aspect, folosim un chenar un pic mai mic
    gboard->y--;

    //delimitam un chenar de x * y, in care se va desfasura jocul
    create_gameboard (gboard->x, gboard->y);

                
    gboard->x -= 2;   //dimensiunile efective ale tablei de joc, dupa chenar
    gboard->y -= 2;

    //in conditii ideale sarpele poate ajunge sa ocupe toata tabla
    snake->p = (PUNCT *) malloc (gboard->x * gboard->y * sizeof (PUNCT));
     
    snake->p[HEAD].x = gboard->x / 3;  //intializam coordonatele capului sarpelui
    snake->p[HEAD].y = gboard->y / 3;
     
    mvaddch (snake->p[HEAD].y, snake->p[HEAD].x, 'O');    //adaugam pe tabla sarpele
}

void init_snake(SNAKE *snake, unsigned *hungry){

    *hungry = 1;
    snake->lastinput = 'd';
    snake->dim = snake->size;

    //setari in functie de nivel
    switch(snake->level){

        case 1:

            snake->speed = 600;
        break;

        case 2:

            snake->speed = 630;
        break;

        case 3:

            snake->speed = 630;
        break;

        case 4:

            snake->speed = 640;
        break;

        case 5:

            snake->speed = 650;
        break;
    }
}

void updatesnake (SNAKE *snake){
    
    unsigned i;

    for (i = snake->dim; i > 0; i--){

         snake->p[i] = snake->p[i - 1];
     }

    snake->last_x = snake->p[snake->dim].x;
    snake->last_y = snake->p[snake->dim].y;
}

//generatorul de mancare
void foodGen (unsigned *hungry, PUNCT *gboard, SNAKE *snake, PUNCT *food, PUNCT *obst){

    unsigned fooderr;
    unsigned i;

    if (*hungry) {
        
        *hungry = FALSE;
        srand (time (NULL));

        do {

            fooderr = FALSE;

            food->x = rand () % gboard->x;
            food->y = rand () % gboard->y;

            if (food->x <= 1){

                fooderr = TRUE;
                continue;
            }

            if (food->y <= 1){

                fooderr = TRUE;
                continue;
            }

            for (i = 0; i < snake->dim; i++) {

                //daca s-a generat mancare peste sarpe
                if (food->x == snake->p[i].x) { 
                    
                    if (food->y == snake->p[i].y) {

                        fooderr = TRUE;
                        break;
                    }
                }
           }

           for (i = 0; i < 5 * snake->level; i++){

                if (food->x == obst[i].x){

                    if (food->y == obst[i].y){

                        fooderr = TRUE;
                        break;
                    }
                }
           }

       }while (fooderr);

       mvaddch (food->y, food->x, '*');
   }
}

//genereaza obstacole in functie de nivel;
//pentru level 1 - 5 obs, lvl 2 - 10; 3 - 15...
void obstacleGen(PUNCT *obst, SNAKE *snake, PUNCT *gboard){

    unsigned i, j;
    unsigned obsterr;
    srand(time(NULL));

    for (i = 0; i < 5 * snake->level; i++){


        do{
            obsterr = FALSE;

            obst[i].x = rand() % gboard->x;
            obst[i].y = rand() % gboard->y;

            //verificam daca a pus mancarea fix pe bordura

            if (obst[i].x <= 2){

                obsterr = TRUE;
                continue;
                
            }

            if (obst[i].y <= 2){

                obsterr = TRUE;
                continue;
                
            }

            //verificam daca nu s-a generat peste pozitia initiala a sarpelui
            //si daca nu s-a generat mult prea aproape de el, impactul fiind iminent
            if (obst[i].y == snake->p[HEAD].y){

                if (obst[i].x == snake->p[HEAD].x
                    || (obst[i].x > snake->p[HEAD].x 
                        && obst[i].x - snake->p[HEAD].x <= 10 - snake->level)){

                    obsterr = TRUE;
                    continue;
                }
            }

            //verificam daca obstacolul s-a generat peste alt obstacol
            for (j = 0; j < i; j++){
                
                if (obst[i].x == obst[j].x){
                    
                    if (obst[i].y == obst[j].y){
                        obsterr = TRUE;
                        break;
                    }
                }
            }

            

        }while(obsterr);

        mvaddch(obst[i].y, obst[i].x, ACS_DIAMOND);


    }
}

void readInput(SNAKE *snake){

    snake->input = getch();
    snake->input = tolower (snake->input);
}

void correctInput(SNAKE *snake){

    unsigned mverr = FALSE;

    if (snake->input == 'w' 
        && ( snake->lastinput == 's' || snake->lastinput == 'w')) {

        mverr = TRUE;
    }

    if (snake->input == 'a' 
        && ( snake->lastinput == 'd' || snake->lastinput == 'a')) {
        
        mverr = TRUE;
    }

    if (snake->input == 's' 
        && ( snake->lastinput == 'w' || snake->lastinput == 's')) {

        mverr = TRUE;
    }

    if (snake->input == 'd' 
        && ( snake->lastinput == 'a'|| snake->lastinput == 'd')) {

        mverr = TRUE;
    }


      //daca s-a introdus ceva corect

    if (snake->input != ERR && !mverr) {

        snake->lastinput = snake->input;
    }

    //daca apar erori de miscare
    if (mverr) {
        
        //sa se miste in aceeasi directie
        snake->input = ERR;
    }
}

unsigned isTimeToEnd(SNAKE *snake){

    if (snake->input == 'q'){

        return 1;
    }

    return 0;
}

void positionSnake(SNAKE *snake){

    switch (snake->input) {
        
        case 'a':
               
            snake->p[HEAD].x--;
        break;

        case 's':

            snake->p[HEAD].y++;
        break;

        case 'd':

            snake->p[HEAD].x++;
        break;

        case 'w':
        
            snake->p[HEAD].y--;
        break;

        default:

            switch (snake->lastinput) {

                case 'a':
                    
                    snake->p[HEAD].x--;
                break;

                case 's':

                    snake->p[HEAD].y++;
                break;

                case 'd':

                    snake->p[HEAD].x++;
                break;

                case 'w':

                    snake->p[HEAD].y--;
                break;
            }
        break;
    }
}

unsigned gameIsLost(SNAKE *snake, PUNCT *gboard, PUNCT *obst) {

    unsigned i;

    //daca a atins vreo margine
    if (snake->p[HEAD].x <= 1) {

        return 1;
    }

    if (snake->p[HEAD].x > gboard->x + 1) {

        return 1;
    }

    if (snake->p[HEAD].y <= 1) {

        return 1;
    }

    if (snake->p[HEAD].y > gboard->y + 1){
        return 1;
    }

    //daca s-a lovit de el insusi
    for (i = 1; i < snake->dim; i++) {
        if (snake->p[HEAD].x == snake->p[i].x) {
            if (snake->p[HEAD].y == snake->p[i].y) {
                return 1;
            }
        }
    }

    //daca s-a lovit de obstacol

    for (i = 1; i < 5 * snake->level; i++){

        if (snake->p[HEAD].x == obst[i].x){

            if (snake->p[HEAD].y == obst[i].y){

                return 1;
            }
        }
    }

    return 0;
}

unsigned hasEaten (SNAKE *snake, PUNCT *food) {

    if (snake->p[HEAD].x == food->x){
        if (snake->p[HEAD].y == food->y){
    
            return 1;
        }
    }

    return 0;
}

void snakeAccelerate (SNAKE * snake){

    switch (snake->level){

        case 1:

            if (snake->dim <= 4) {
                
                snake->speed += 10;
            }
            else{

                if (snake->dim <= 26){

                    snake->speed += 5;
                }
            }
        break;

        case 2:

            if (snake->dim <= 15){

                snake->speed += 2;
            }
            else{

                if (snake->dim <= 20){

                    snake->speed += 8;
                }
                else{

                    if (snake->dim <= 25){

                        snake->speed += 20;
                    }
                }
            }

        break;

        case 3:

            if (snake->dim <= 25){

                snake->speed += 9;
            }
        break;

        case 4:

            if (snake->dim <= 5){

                snake->speed += 12;
            }
            else{

                if(snake->dim <= 10){

                    snake->speed += 20;
                }
                else{

                    if (snake->dim <= 24){

                        snake->speed += 3;
                    }
                    else{

                        if (snake->dim == 25){

                            snake->speed += 8;
                        }
                    }
                }
            }
        break;

        case 5:

            if (snake->dim <= 10){

                snake->speed += 15;
            }
            else{

                if (snake->dim <= 15){

                    snake->speed += 20;
                }
                else{

                    if (snake->dim <= 17){

                        snake->speed += 25;
                    }
                }
            }
        break;
    }
}

void makeSnakeFatAndFurious(SNAKE *snake, unsigned * hungry){

    *hungry = 1;
    snakeAccelerate(snake);
    snake->dim++;
}

void refreshSnake(SNAKE *snake){
    
    snake->p[snake->dim].x = snake->last_x;
    snake->p[snake->dim].y = snake->last_y;
}

void paintSnake(SNAKE *snake, unsigned hungry){

    if (!hungry) {
 
        mvaddch (snake->last_y, snake->last_x, ' ');
    }
    else
    {
    
        mvaddch (snake->last_y, snake->last_x, 'O');
    }

    mvaddch (snake->p[HEAD].y, snake->p[HEAD].x, 'O');
}

//folosind aceeasi viteza, pe y sarpele se misca mult mai repede decat pe x.
//corectare prin functie care in momentul schimbarii axelor creste sau scade viteza pentru a da impresia ca e constanta.
void adjustSpeed(SNAKE *snake, PUNCT *gboard){

    if (snake->input == 'w' || snake->input == 's'){

        if (snake->lastinput == 'a' || snake->lastinput == 'd'){

            snake->speed -= 17 * gboard->y / 24;
        
        }
    }

    if (snake->input == 'a' || snake->input == 'd'){
        if (snake->lastinput =='w' || snake->lastinput =='s'){

            snake->speed += 17 * gboard->y / 24; 

        }
    }
}

void printLoosersMSG(PUNCT *gboard){

    clear();
    mvaddstr (10, gboard->x / 3, "GAME OVER");
    timeout (-1);
    getch ();
}

int main () {
    
    //nobuffering
    cbreak ();
    PUNCT *gboard;
    PUNCT *food;
    PUNCT *obstacle;

    SNAKE *snake;

    unsigned hungry;        //1 = daca nu e mancare pe tabla
    unsigned op;                 //2 - game, 1- options 0 - quit    

    gboard = (PUNCT *) malloc (sizeof(PUNCT));
    food = (PUNCT *) malloc (sizeof(PUNCT));
    obstacle = (PUNCT *) malloc (sizeof(PUNCT));
    snake = (SNAKE *) malloc (sizeof(SNAKE));

    snake->size = 1;
    snake->level = 1;
    initscr();
    init_window (gboard);

    while (NO_STOP){

        op = main_menu (gboard);          // din main menu, utilizatorul alege optiunea

        switch (op){

            case 0:                 //utilizatorul a ales sa iasa din joc

                endwin();
                exit(1);
            break;

            case 1:                 //utilizatorul doreste sa vada optiunile

                customise(snake);
            break;

            case 2:                 //utilizatorul doreste sa joace

                //initializam tabla
                init_game (snake, gboard);
                
                /*
                initializam sarpele:
                    initial nu a mancat nimic
                    se deplaseaza spre dreapta
                    setam viteza initiala in functie de nivel
                */
                init_snake (snake, &hungry);

                //realocam memorie in caz ca s-a modificat nivelul, deci si numarul de obstacole
                obstacle = (PUNCT *) realloc(obstacle, 5 * snake->level * sizeof(PUNCT));

                //generam obstacolele
                obstacleGen(obstacle, snake, gboard);

                while (NO_STOP) {   //incepe jocul

                    updatesnake(snake);                //actualizarea coordonatelor

                    timeout (UNITY - snake->speed);  //viteza de miscare

                    foodGen (&hungry, gboard, snake, food, obstacle); //generam mancarea

                    readInput (snake);             //citim urmatoarea miscare

                    adjustSpeed (snake, gboard);    //cand se trece dupa o axa pe alta

                    correctInput (snake);          //verificam de erori

                    if (isTimeToEnd (snake)){         //inchidem daca trebuie
                        
                        break;
                    }

                    positionSnake (snake);            //in urma inputului, repozitionam sarpele   

                    if (gameIsLost(snake, gboard, obstacle)){     //daca s-a terminat jocul
                        
                        printLoosersMSG (gboard);
                        break;
                    }

                    if (hasEaten(snake, food)){

                        //creste in dimensiune si devine mai rapid
                        makeSnakeFatAndFurious(snake, &hungry);
                    }

                    refreshSnake(snake);    //actualizeaza finalul sarpelui(daca a mancat, s-a marit)    

                    paintSnake(snake, hungry);  //inainteaza capul o pozitie, si se sterge coada

                    refresh ();

                }
            break;
        }

    }

    //inchidere
    endwin ();
    exit(1);
}
