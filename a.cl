initscr();

move(5, 15)
attron(A_REVERSE);
printw("%s", array { "Hello World" });
attroff(A_REVERSE);
refresh();

keypad(stdscr, true);

c := getch();

endwin();

if(c == KEY_BACKSPACE) {
    println("KEY_BACKSPACE");
}
else {
    println("!KEY_BACKSPACE");
}

