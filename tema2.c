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
}PUNCT;

typedef struct {

    PUNCT *p;

    unsigned last_x;
    unsigned last_y;

    unsigned dim;
    unsigned speed;

    char input;
    char lastinput;

}SNAKE;

typedef struct {

    unsigned nr_x;  //numarul de coloane
    unsigned nr_y;  //numarul de linii

}BOARD;

void init_window(){

    //initializare
    raw();

    //mesaj initial
    attron(A_UNDERLINE | A_BOLD);
        mvprintw(0, 3, "SNAKE");
        mvprintw(1, 1, "W - inainte");
        mvprintw(2, 1, "A - stanga");
        mvprintw(3, 1, "S - jos");
        mvprintw(4, 1, "D - dreapta");
    attroff(A_UNDERLINE | A_BOLD);

    //ascundere cursor
    curs_set(0);

    //ascundem inputul
    noecho();



    mvprintw(10, 10, "Apasa pentru a incepe jocul");
    getch();
    clear();


}

//functie care creaza un
//chenar de dim_x * dim_y

void create_gameboard(int dim_x, int dim_y){
    int i;

    //sus, orizontal
    for (i = 1; i < dim_x + 1; i ++){
        if (i % 2){
            mvaddch(SPATIERE, i, '#');
        }else{
            mvaddch(SPATIERE, i, ' ');
        }
    }

    //dreapta
    for (i = SPATIERE; i < dim_y + SPATIERE; i++){
        mvaddch(i, dim_x, '#');
    }

    //jos
    for (i = 1; i < dim_x + 1; i++){
        if (i % 2){
            mvaddch(dim_y + SPATIERE, i, '#');
        }else{
            mvaddch(dim_y + SPATIERE, i, ' ');
        }
    }

    //stanga
    for (i = SPATIERE; i < dim_y + SPATIERE; i++){
        mvaddch(i, 1, '#');
    }
}

int main(){

    //nobuffering
    cbreak();

    WINDOW *wnd = initscr();
    BOARD gboard;
    SNAKE snake;
    PUNCT food;

    unsigned over = 0;      //daca ajunge 1, game over
    unsigned quit = 0;      //daca ajunge 1, trebuie iesit
    unsigned hungry = 1;    //1= daca nu e mancare pe tabla

    //erors
    unsigned mverr = 0;     //daca ajunge 1, eroare de miscare
    unsigned fooderr = 0;   //1 - daca eroare la generare mancare

    unsigned i;


    init_window();
    getmaxyx(wnd, gboard.nr_y, gboard.nr_x);

    /*
    folosim efectiv un chenar de dimenisuni mai mici
    pentru aspect
    */
    gboard.nr_x--;
    gboard.nr_y--;

    create_gameboard(gboard.nr_x, gboard.nr_y);

    //din cauza chenarului
    //dimensiunea efectiva s-a redus iar
    gboard.nr_x -= 2;
    gboard.nr_y -= 2;

    snake.p = (PUNCT *) malloc (gboard.nr_x * gboard.nr_y * sizeof (PUNCT));

    //pozitionare initiala
    snake.p[HEAD].x = gboard.nr_x  / 3;
    snake.p[HEAD].y = gboard.nr_y / 3 ;
    mvaddch(snake.p[HEAD].y, snake.p[HEAD].x, 'o');

    //dimensiune initiala
    snake.dim = 1;

    //viteza initiala
    snake.speed = 350;


    while (NO_STOP){

        mverr = 0;
        snake.last_x = snake.p[snake.dim - 1].x;
        snake.last_y = snake.p[snake.dim - 1].y;

        timeout(UNITY - snake.speed);


        //adaugare mancare
        if(hungry){

            hungry = 0;

            do{

                fooderr = 0;

                srand(time(NULL));

                food.x = rand() % gboard.nr_x;
                food.y = rand() % gboard.nr_y;

                for (i = 0; i < snake.dim; i++){

                    if (food.x == snake.p[i].x
                        && food.y == snake.p[i].y){

                            fooderr = 1;
                            break;

                    }
                }

            }while (fooderr == 1);

            mvaddch(food.y, food.x, '*');

        }


        snake.input = getch();

        /*
        Prindere eroare:
        daca sarpele merge spre stanga si utilizatorul
        apasa dreapta
        */
    {

        if (snake.input == 'w'
            && snake.lastinput == 's'){
                mverr = 1;
            }

        if (snake.input == 'a'
            && snake.lastinput == 'd'){
                mverr = 1;
            }

        if (snake.input == 's'
            && snake.lastinput == 'w'){
                mverr = 1;
            }

        if (snake.input == 'd'
            && snake.lastinput =='a'){
                mverr = 1;
            }
    }

        //daca s-a introdus ceva corect
        if (snake.input != ERR && !mverr){
            snake.lastinput = snake.input;
        }

        snake.input = tolower (snake.input);



        //daca apar erori de miscare
        if (mverr){

            //sa se miste in aceeasi directie
            snake.input = ERR;
        }


        if (snake.input == 'q'){
            quit = 1;
        }

        if (quit){
            break;
        }

        if (over){
            mvaddstr(10, 30, "GAME OVER");
            getch();
            break;
        }

        //input
        switch (snake.input){
            case 'a':
                if(snake.p[HEAD].x > 2){
                    snake.p[HEAD].x --;
                }else{
                    over = 1;

                }
                break;

            case 's':
                if (snake.p[HEAD].y < gboard.nr_y + 1){
                    snake.p[HEAD].y++;
                }else{
                    over = 1;
                }
                break;

            case 'd':
                if (snake.p[0].x < gboard.nr_x){
                    snake.p[0].x++;
                }else{
                    over = 1;
                }
                break;
            case 'w':
                if (snake.p[0].y > 1){
                    snake.p[0].y --;
                }else{
                    over = 1;

                }
                break;

            default:
                switch (snake.lastinput){
                case 'a':
                if(snake.p[HEAD].x > 2){
                    snake.p[HEAD].x --;
                }else{
                    over = 1;

                }
                break;

                case 's':
                if (snake.p[HEAD].y < gboard.nr_y + 1){
                    snake.p[HEAD].y++;
                }else{
                    over = 1;
                }
                break;

                case 'd':
                if (snake.p[0].x < gboard.nr_x){
                    snake.p[0].x++;
                }else{
                    over = 1;
                }
                break;
                case 'w':
                if (snake.p[0].y > 1){
                    snake.p[0].y --;
                }else{
                    over = 1;

                }
                break;

            }
                break;

        }


        if (snake.p[HEAD].x == food.x &&
            snake.p[HEAD].y == food.y){
                hungry = 1;
            
            }


        //sterge coada + inaintare cap

        mvaddch(snake.last_y, snake.last_x, ' ');
        mvaddch(snake.p[0].y, snake.p[0].x, 'o');




        refresh();

    }


    //inchidere
    getch();
    endwin();

    return 0;
}
