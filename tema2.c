#include <stdio.h>
#include <ncurses.h>

int main(){

    //initializare
    initscr();
    raw();

    int y1 = 15;
    int y2 = 20;
    int x1 = 10;
    int x2 = 25;
    printw("Acesta e un text random, pentru test");
    addch('a');

    //atribuire de underline si standout
    attron(A_STANDOUT | A_UNDERLINE);

    move(12,13);
    mvprintw(y1, x1, "TEST");

    //oprire atribuire
    attroff(A_STANDOUT | A_UNDERLINE);

    start_color();
    //functioneaza ca attron


    //foreground background
    init_pair(1,COLOR_RED, COLOR_BLUE);
    attron( COLOR_PAIR(1));
    printw("TESTCOLORAT");
    attroff(COLOR_PAIR(1));
    //inchidere
    getch();
    endwin();

    return 0;
}
