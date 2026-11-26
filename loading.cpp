#include <ncurses\curses.h>
#include <unistd.h>
#include <windows.h>

int main(){
  initscr();
  curs_set(0);

  int tinggi, lebar;
  getmaxyx(stdscr, tinggi, lebar);

  const char *judul = "loading...";
  const char *garis = "-----------";
  const char *kotak = "|         |";

  int xKotak = (lebar - strlen(garis)) / 2;
  int xJudul = (lebar - strlen(judul)) / 2;
  int y = tinggi - 5;

  mvprintw(y, xJudul, "%s", judul);
  mvprintw(y + 1, xKotak, "%s", garis);
  mvprintw(y + 2, xKotak, "%s", kotak);
  mvprintw(y + 3, xKotak, "%s", garis);

  for (int f = 0; f < 3; f ++){
    mvprintw(y + 2, xKotak + 1 + f * 3, ">>>");
    refresh();
    sleep(1);
  }

  endwin();
  
  return 0;
}