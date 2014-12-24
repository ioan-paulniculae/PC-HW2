#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <ncurses.h>

#define SPATIERE 0
#define NO_STOP 1
#define HEAD 0
#define UNITY 1000

typedef struct {
  
    unsigned x;
    unsigned y;
} PUNCT;

typedef struct {

    PUNCT *p;

    unsigned last_x;
    unsigned last_y;

    unsigned dim;
    unsigned speed;

    char input;
    char lastinput;
} SNAKE;

void init_window () {

  //initializare
    raw ();

  //mesaj initial
    attron (A_UNDERLINE | A_BOLD);
       
        mvprintw (0, 3, "SNAKE");
        mvprintw (1, 1, "W - inainte");
        mvprintw (2, 1, "A - stanga");
        mvprintw (3, 1, "S - jos");
        mvprintw (4, 1, "D - dreapta");
    
    attroff (A_UNDERLINE | A_BOLD);

  //ascundere cursor
    curs_set (0);

  //ascundem inputul
    noecho ();



    mvprintw (10, 10, "Apasa orice tasta");
    
    getch ();
    clear ();
}

unsigned main_menu () {

    PUNCT p;

    p.x = 30;
    p.y = 12;

    clear ();

    attron (A_UNDERLINE | A_BOLD);
        
        mvaddstr (p.y - 2, p.x, "NEW GAME");
    
    attroff (A_UNDERLINE | A_BOLD);

    mvaddstr (p.y - 1, p.x, "OPTIONS");
    mvaddstr (p.y, p.x, "EXIT");

    char c;

    while (NO_STOP) {

        c = getch ();
        c = tolower (c);

        if (c == 'q') {
            return 0;
        }

        switch (c) {
            case 'w':
        
                if (p.y < 12) {
               
                    p.y++;
                }

            break;

            case 's':

                if (p.y > 10) {
                
                    p.y--;
                }

            break;

            case '\n':
           
                clear ();
                return p.y - 10;
        
            break;

            default:
            break;
        }

        switch (p.y) {

            case 12:
               
                clear ();
                
                attron (A_UNDERLINE | A_BOLD);
                
                    mvaddstr (p.y - 2, p.x, "NEW GAME");
                
                attroff (A_UNDERLINE | A_BOLD);

                mvaddstr (p.y - 1, p.x, "OPTIONS");
                mvaddstr (p.y, p.x, "EXIT");

            break;

            case 11:
                
                clear ();
                
                mvaddstr (p.y - 1, p.x, "NEW GAME");

                attron (A_UNDERLINE | A_BOLD);
                
                    mvaddstr (p.y, p.x, "OPTIONS");
                
                attroff (A_UNDERLINE | A_BOLD);

                mvaddstr (p.y + 1, p.x, "EXIT");

            break;

            case 10:

                clear ();

                mvaddstr (p.y, p.x, "NEW GAME");
                mvaddstr (p.y + 1, p.x, "OPTIONS");

                attron (A_UNDERLINE | A_BOLD);

                    mvaddstr (p.y + 2, p.x, "EXIT");
                
                attroff (A_UNDERLINE | A_BOLD);
   
            break;

            default:
            break;
        }

        refresh ();
    }

    clear ();

    return 1;
}

void options () {

    clear ();

    mvaddstr (10, 10, "DIFFICULTY:");
    mvaddstr (11, 10, "INITIAL SIZE:");

    getch ();
}

//functie care creaza un chenar de dim_x * dim_y
void create_gameboard (unsigned dim_x, unsigned dim_y) {

    int i;

    //sus
    for (i = 1; i < dim_x + 1; i++) {
      
        if (i % 2) {
         
            mvaddch (SPATIERE, i, '#');
        }
        else {
         
            mvaddch (SPATIERE, i, ' ');
        }
    }
    
    //dreapta
    for (i = SPATIERE; i < dim_y; i++) {
        
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
    for (i = SPATIERE; i < dim_y; i++){

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

void updatesnake (SNAKE *snake){
    
    unsigned i;

    for (i = snake->dim; i > 0; i--){

         snake->p[i].x = snake->p[i - 1].x;
         snake->p[i].y = snake->p[i - 1].y;
     }

    snake->last_x = snake->p[snake->dim].x;
    snake->last_y = snake->p[snake->dim].y;
}

//generatorul de mancare
void foodGen (unsigned *hungry, PUNCT *gboard, SNAKE *snake, PUNCT *food){

    unsigned fooderr;
    unsigned i;

    if (*hungry) {
        
        *hungry = 0;
        srand (time (NULL));

        food->x = rand () % gboard->x;
        food->y = rand () % gboard->y;

        //fix: daca e pe margine, sa o puna langa.
        //nu sa genereze iar
        if (food->x <= 2) {
        
            food->x = 3;
        }

        if (food->y <= 2) {
        
            food->y = 3;
        }

        do {

            fooderr = 0;
            for (i = 0; i < snake->dim; i++) {

                //daca s-a generat mancare peste sarpe
                if (food->x == snake->p[i].x) { 
                    if (food->y == snake->p[i].y) {

                            srand (time (NULL));

                            food->x = rand () % gboard->x;
                            food->y = rand () % gboard->y;

                            fooderr = 1;
                            
                            break;
                    }
                }
           }
       }while (fooderr);

       mvaddch (food->y, food->x, '*');
   }
}

void readInput(SNAKE *snake){

    snake->input = getch();
    snake->input = tolower (snake->input);
}

void correctInput(SNAKE *snake){

    unsigned mverr = FALSE;

    if (snake->input == 'w' && snake->lastinput == 's') {

        mverr = TRUE;
    }

    if (snake->input == 'a' && snake->lastinput == 'd') {
        
        mverr = TRUE;
    }

    if (snake->input == 's' && snake->lastinput == 'w') {

        mverr = TRUE;
    }

    if (snake->input == 'd' && snake->lastinput == 'a') {

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

unsigned gameIsLost(SNAKE *snake, PUNCT *gboard){

    unsigned i;

    if (snake->p[HEAD].x <= 2) {

        return 1;
    }

    if (snake->p[HEAD].x >= gboard->x) {

        return 1;
    }

    if (snake->p[HEAD].y <= 1) {

        return 1;
    }

    if (snake->p[HEAD].y >= gboard->y + 1){
        return 1;
    }

    for (i = 1; i < snake->dim; i++) {
        if (snake->p[HEAD].x == snake->p[i].x) {
            if (snake->p[HEAD].y == snake->p[i].y) {
                return 1;
            }
        }
    }

    return 0;
}

unsigned hasEaten (SNAKE *snake, PUNCT *food){

    if (snake->p[HEAD].x == food->x){
        if (snake->p[HEAD].y == food->y){
    
            return 1;
        }
    }

    return 0;
}

void makeSnakeFatAndFurious(SNAKE *snake, unsigned * hungry, unsigned * speed_augment){

    *hungry = 1;

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

int main () {
    
    //nobuffering
    cbreak ();

    
    PUNCT *gboard;
    PUNCT *food;

    gboard = (PUNCT *) malloc (sizeof(PUNCT));
    food = (PUNCT *) malloc (sizeof(PUNCT));
    
    SNAKE *snake;
    snake = (SNAKE *) malloc (sizeof(SNAKE));

    unsigned hungry = 1;		//1= daca nu e mancare pe tabla

    unsigned speed_augment = 0;    //coeficient care influenteaza viteza

    unsigned op;                 //2 - game, 1- options 0 - quit

    initscr();
    init_window ();



    while (NO_STOP){

        op = main_menu ();          // din main menu, utilizatorul alege optiunea

        switch (op){

            case 0:                 //utilizatorul a ales sa iasa din joc

                endwin();
                exit(1);
            break;

            case 1:                 //utilizatorul doreste sa vada optiunile

                options();
            break;

            case 2:                 //utilizatorul doreste sa joace

                init_game (snake, gboard);
                
                snake->dim = 10; //dimensiunea initiala a sarpelui. TO DO: select from options

                //TO DO: SNAKE SPEED FROM OPTIONS
                snake->speed = 550;

                snake->lastinput = 'd'; //sarpele se va misca initial spre dreapta

                while (NO_STOP) {   //incepe jocul

                    updatesnake(snake);                //actualizarea coordonatelor

                    timeout (UNITY - snake->speed);  //viteza de miscare

                    foodGen(&hungry, gboard, snake, food); //generam mancarea

                    readInput(snake);             //citim urmatoarea miscare

                    correctInput(snake);          //verificam de erori

                    if (isTimeToEnd(snake)){         //inchidem daca trebuie
                        
                        break;
                    }

                    positionSnake(snake);            //in urma inputului, repozitionam sarpele

                    if (gameIsLost(snake, gboard)){     //daca s-a terminat jocul
                        
                        clear();
                        mvaddstr (10, gboard->x / 3, "GAME OVER");
                        timeout (-1);
                        getch ();
                        
                        break;
                    }

                    if (hasEaten(snake, food)){

                        makeSnakeFatAndFurious(snake, &hungry, &speed_augment);
                    }

                    refreshSnake(snake);

                    paintSnake(snake, hungry);

                    refresh ();

                }
            break;
        }

    }

    //inchidere
    endwin ();
    return 0;
}
