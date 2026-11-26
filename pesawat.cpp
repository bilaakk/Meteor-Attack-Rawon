#include <ncurses\curses.h>
#include <windows.h>

int main(){
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int tinggi, lebar;
    getmaxyx(stdscr, tinggi, lebar);

    int x = lebar / 2;
    int y = tinggi - 2;

    int tombol = 0;
    while(tombol != 'q' && tombol != 'Q'){
        erase();
        mvaddch(y, x, 'A');
        refresh();

        tombol = getch();

        if (tombol == KEY_UP    && y > 0)            y--;
        if (tombol == KEY_DOWN  && y < tinggi - 1)    y++;
        if (tombol == KEY_LEFT  && x > 0)            x--;
        if (tombol == KEY_RIGHT && x < lebar - 1)   x++;

    }

    endwin();
    return 0;
}