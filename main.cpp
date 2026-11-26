#include <ncurses\curses.h>
#include <unistd.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <cstring>


const int SKOR_MENANG = 20;

    const int KELUAR = 0;
    const int MENANG = 1;
    const int KALAH = 2;

// PESAWAT

struct Pesawat {
    int x;
    int y;
};

void initPesawat(Pesawat &p, int lebar, int tinggi) {
    p.x = lebar / 2;
    p.y = tinggi - 2;
}

void gerakPesawat(Pesawat &p, int tombol, int lebar, int tinggi) {
    if (tombol == KEY_UP && p.y > 0) p.y--;
    if (tombol == KEY_DOWN && p.y < tinggi -1) p.y++;
    if (tombol == KEY_LEFT && p.x > 0) p.x--;
    if (tombol == KEY_RIGHT && p.x < lebar -1) p.x++;
}
 void gambarPesawat(Pesawat &p) {
    mvaddch(p.y, p.x, 'A');
 }

 //METEOR

 const int MAX_METEOR = 200;
 struct Meteor {
    int x;
    int y;
    bool aktif;
 };

 void initMeteor(Meteor meteor[], int lebar, int tinggi) {
    for (int i = 0; i < MAX_METEOR; i++) {
        meteor[i].aktif = false;
    }
 }

 void updateMeteor(Meteor meteor[], int lebar, int tinggi) {
    if (rand() % 1 == 0) {
        for (int i = 0; i < MAX_METEOR; i++) {
            if (!meteor [i].aktif) {
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
    for (int i= 0; i < MAX_METEOR; i++) {
        if (meteor[i].aktif) {
            mvprintw(meteor[i].y, meteor[i].x, "O");
        }
    }
}

//LOADING

void tampilanLoading() {
    int tinggi, lebar;
    getmaxyx(stdscr, tinggi, lebar);
    
    const char *judul = "loading...";
    const char *garis = "-----------";
    const char *kotak = "|         |";
    
    int xKotak = (lebar - strlen(kotak)) / 2;
    int xJudul = (lebar - strlen(judul)) / 2;
    int y = tinggi - 5;

    mvprintw(y, xJudul, "%s", judul);
    mvprintw(y + 1, xKotak, "%s", garis);
    mvprintw(y + 2, xKotak, "%s", kotak);
    mvprintw(y + 3, xKotak, "%s", garis);
    
    for (int f = 0; f < 3; f++) {
        mvprintw(y + 2, xKotak + 1 + f * 3, ">>>");
        
        refresh();
        sleep(1);
    }
}

//GAME

bool cekTabrakan(Meteor meteor[], Pesawat &p) {
    for (int i = 0; i < MAX_METEOR; i++) {
        if (meteor[i].aktif && meteor[i].x == p.x && meteor[i].y == p.y) {
            return true;
        }
    }
    return false;
}

int jalankanGame() {
    nodelay(stdscr, TRUE);
    
    int tinggi, lebar;
    getmaxyx(stdscr, tinggi, lebar);

    Pesawat pesawat;
    initPesawat(pesawat, lebar, tinggi);

    Meteor meteor[MAX_METEOR];
    initMeteor(meteor, lebar, tinggi);

    int tombol = 0;
    int hitungan = 0;
    bool tabrakan = false;

    time_t startTime = time(0);
    int skor = 0;


    while (tombol != 'q' && tombol != 'Q' && !tabrakan && skor < SKOR_MENANG) {
        tombol = getch();
        gerakPesawat(pesawat, tombol, lebar, tinggi);

        hitungan++;
        if (hitungan% 2 == 0) {
            updateMeteor(meteor, lebar, tinggi);
        }
        
        tabrakan = cekTabrakan(meteor, pesawat);
        
        skor = time(0) - startTime;

        erase();
        gambarPesawat(pesawat);
        gambarMeteor(meteor);
        mvprintw(0, 0, "SCORE: %d", skor);
        refresh();

        napms(50);
    }

    nodelay(stdscr, FALSE);

    if (tabrakan) return KALAH;
    if (skor >= SKOR_MENANG) return MENANG;
    return KELUAR;

}

bool mainMenu(int hasil) {
    int tinggi, lebar;
    getmaxyx(stdscr, tinggi, lebar);

    const char *judul;
    if (hasil == 1) {
        judul = "ANJAY! GG BANGET!";
    } else {
        judul = "YAHAHAHAHA! POKE! CUPU! AYAM! MAIN POU AJA!";
    }

    const char *pilihan = "tekan P kalo mau rematch, tekan Q kalo POKE!";
    
    erase();
    mvprintw(tinggi /2 -1, (lebar - strlen(judul)) / 2, "%s", judul);
    mvprintw(tinggi /2, (lebar - strlen(pilihan)) / 2, "%s", pilihan);
    refresh();

    flushinp();

    int tombol = 0;
    while (tombol != 'p' && tombol != 'P' && tombol != 'q' && tombol != 'Q') {
        tombol = getch();
    }

    return (tombol == 'p' || tombol == 'P');
}

int main() {
    srand(time(0));

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    tampilanLoading();
    
    bool lagi = true;
    while (lagi) {
        int hasil = jalankanGame();

        if (hasil == KELUAR) {
            lagi = false;
        } else  {
            lagi = mainMenu(hasil);
        }
    }

    endwin();
    return 0;

}
