#include <stdio.h>
#include <ncurses.h>

typedef struct {

    int x;
    int y;
    unsigned dim;
    int viteza;

}snake;

typedef struct {

    int x;
    int y;
    int max_x;
    int max_y;
    unsigned nr_x;  //numarul de coloane
    unsigned nr_y;  //numarul de linii

}chenar;

void initializare_tabla(){

    //initializare
    initscr();
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


}

int main(){

    initializare_tabla();
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
