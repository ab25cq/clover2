
initscr();
def_prog_mode();
start_color();
init_pair(1, COLOR_BLUE, COLOR_BLACK);
clear();
attron(COLOR_PAIR(1));
addstr("ABC");
addstr("あいう");
attroff(COLOR_PAIR(1));
refresh();
getch();

clear();
box(stdscr, '|', '-');
refresh();

getch();

clear();
border('|', '|', '+', '+', '|', '|', '+', '+');
refresh();

getch();

beep();

getch();

endwin();