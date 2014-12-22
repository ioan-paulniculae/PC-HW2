#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>

#define SPATIERE 0
#define NO_STOP 1

typedef struct {
    unsigned x;
    unsigned y;
}PUNCT;

typedef struct {

    PUNCT *p;

    unsigned last_x;
    unsigned last_y;

    unsigned dim;
    char input;

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
    snake.p[0].x = gboard.nr_x  / 3;
    snake.p[0].y = gboard.nr_y / 3 ;

    snake.dim = 1;

    mvaddch(snake.p[0].y, snake.p[0].x, '0');


    while (NO_STOP){

        snake.last_x = snake.p[snake.dim - 1].x;
        snake.last_y = snake.p[snake.dim - 1].y;

        snake.input = getchar();
        snake.input = tolower (snake.input);

        if (snake.input == 'q'){
            break;
        }

        //input
        switch (snake.input){
            case 'a':
                if(snake.p[0].x > 2){
                    snake.p[0].x --;
                }
                break;

            case 's':
                if (snake.p[0].y < gboard.nr_y + 1){
                    snake.p[0].y++;
                }
                break;

            case 'd':
                if (snake.p[0].x < gboard.nr_x){
                    snake.p[0].x++;
                }
                break;
            case 'w':
                if (snake.p[0].y > 1){
                    snake.p[0].y --;
                }
                break;
        }


        //sterge coada + inaintare cap
        mvaddch(snake.last_y, snake.last_x, ' ');
        mvaddch(snake.p[0].y, snake.p[0].x, '0');

        refresh();

    }


    //inchidere
    getch();
    endwin();

    return 0;
}
