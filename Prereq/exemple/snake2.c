/* Programarea Calculatoarelor, seria CC
 * Tema2 - Snake
 */
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <ctype.h>
#include <sys/select.h>

#define FOREVER 		1
#define INIT_ROW 		2
#define INIT_COL 		0
#define SELECT_EVENT		1
#define SELECT_NO_EVENT		0

/* Pentru explicarea codului specific ncurses
 * consultați snake1.c, iar pentru codul specific select
 * consultați select.c
 */

int main(void)
{
	int row = INIT_ROW, col = INIT_COL, nrows, ncols;
	char c;
	int nfds, sel;
	fd_set read_descriptors;
	struct timeval timeout;
	WINDOW *wnd = initscr();
	
	getmaxyx(wnd, nrows, ncols);
	clear();
	noecho();
	cbreak();
	curs_set(0);

	nfds = 1;
	FD_ZERO(&read_descriptors);
	FD_SET(0, &read_descriptors);
	timeout.tv_sec = 2;
	timeout.tv_usec = 0;
		
	mvaddstr(0, 0, "A fost apasata tasta:");
	move(1, 0);
	addch(' ');
	
	refresh();
	while (FOREVER) {
		sel = select(nfds, &read_descriptors, NULL, NULL, &timeout);

		if (sel == SELECT_EVENT) {
			c = getchar();
			
			if (tolower(c) == 'q') {
				break;
			}
			move(1, 0);
			addch(c);
		}

		if (row == nrows) {
			break;
		}
			
		if (col == ncols) {
			row++;
			col = 0;
		}
			
		move(row, col);
		addch('*');
		col++;
			
		refresh();
		FD_SET(0, &read_descriptors);
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;
	}

	endwin();

	return 0;
}
