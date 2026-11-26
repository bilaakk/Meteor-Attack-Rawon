  #include <ncurses.h>
#include <chrono>

const int DURASI_START = 1;

void gambarStart() {
    int baris, kolom;
    getmaxyx(stdscr, baris, kolom);

    attron (COLOR_PAIR(2) | A_BOLD);
    mvprintw (baris / 2, (kolom - 5) / 2,"'START!'");
    attroff (COLOR_PAIR(2) |A_BOLD);
}
int main() {
    initscr();
    curs_set(0);
    start_color();
    init_pair(2, COLOR_RED, COLOR_BLACK); 

     gambarStart();
    refresh();
    napms(1500);

     endwin();
    return 0;
} 