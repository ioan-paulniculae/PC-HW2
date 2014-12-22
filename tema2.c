#include <stdio.h>
#include <ncurses.h>

#define SPATIERE 0
typedef struct {

    int x;
    int y;
    unsigned dim;
    int viteza;

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

    WINDOW *wnd = initscr();
    BOARD gboard;
    SNAKE s;

    init_window();
    getmaxyx(wnd, gboard.nr_y, gboard.nr_x);

    /*
    folosim efectiv un chenar de dimenisuni mai mici
    pentru aspect
    */
    gboard.nr_x--;
    gboard.nr_y--;

    create_gameboard(gboard.nr_x, gboard.nr_y);
    /*
    //foreground background
    init_pair(1,COLOR_RED, COLOR_BLUE);

    attron( COLOR_PAIR(1));

    printw("TESTCOLORAT");

    attroff(COLOR_PAIR(1));

*/
    //inchidere
    getch();
    endwin();

    return 0;
}
