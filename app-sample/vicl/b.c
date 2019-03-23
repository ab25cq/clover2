#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main() {
    initscr();

    clear();
    mvprintw(0,0, " ");
    mvprintw(0, 1, "愛");
    move(1, 0);
    mvprintw(1,0,"aaaa");
    refresh();

    getch();

    endwin();

    exit(0);
}
