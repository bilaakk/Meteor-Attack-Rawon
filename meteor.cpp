#include <ncurses.h>
#include <cstdlib>
#include <ctime>

const int MAX_METEOR = 10;

struct Meteor {
    int x;
    int y;
    bool aktif;
};

void initMeteor(Meteor meteor[]) {
    for (int i = 0; i < MAX_METEOR; i++) {
        meteor[i].aktif = false;
    }
}

void updateMeteor(Meteor meteor[], int lebar, int tinggi) {
    if (rand() % 5 == 0) {
        for (int i = 0; i < MAX_METEOR; i++) {
            if (!meteor[i].aktif) {
                meteor[i].x = rand() % lebar;
                meteor[i].y = 0;
                meteor[i].aktif = true;
                break;
            }
        }
    }

    for (int i = 0; i < MAX_METEOR; i++) {
        if (meteor[i].aktif) {
            meteor[i].y++;
            if (meteor[i].y >= tinggi) {
                meteor[i].aktif = false;
            }
        }
    }
}

void gambarMeteor(Meteor meteor[]) {
    for (int i = 0; i < MAX_METEOR; i++) {
        if (meteor[i].aktif) {
            mvprintw(meteor[i].y, meteor[i].x, "O");
        }
    }
}

int main() {
    srand(time(0));

    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    Meteor meteor[MAX_METEOR];
    initMeteor(meteor);

    int tinggi, lebar;

    while (true) {
        getmaxyx(stdscr, tinggi, lebar);

        if (getch() == 'q') break;

        updateMeteor(meteor, lebar, tinggi);

        erase();
        gambarMeteor(meteor);
        refresh();

        napms(100);
    }

    endwin();
    return 0;
}