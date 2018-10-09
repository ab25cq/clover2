ls -al | less
pwd | less
vim src/main.c

initscr();
keypad(stdscr, true);
noecho();
getch();
endwin();
