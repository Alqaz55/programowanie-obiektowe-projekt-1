#include <ncurses.h>
#include "zwierzyna/Wilk.hpp"  


void draw_frame(int width, int height)
{
    // górna i dolna krawędź
    for (int x = 0; x < width; x++) {
        mvaddch(0, x, '#');
        mvaddch(height - 1, x, '#');
    }

    // lewa i prawa krawędź
    for (int y = 0; y < height; y++) {
        mvaddch(y, 0, '#');
        mvaddch(y, width - 1, '#');
    }
}

int main() {

    srand(time(NULL));
    // --- ncurses init ---
    initscr();          // start ncurses
    cbreak();           // wyłącza buforowanie linii
    noecho();           // nie pokazuje wpisywanych znaków
    curs_set(0);        // ukrywa kursor
    keypad(stdscr, TRUE); // włącz obsługę klawiszy specjalnych

    // --- Tworzymy wilka ---
    Wilk zwierzak(2, 2);   // startowa pozycja (x=5, y=5)

    int ch;
    while (true) {
        clear();      
        draw_frame(WORLD_WIDTH, WORLD_HEIGHT);
        zwierzak.draw();        // rysuje wilka
        refresh();

        ch = getch();       // czekamy na klawisz

        if (ch == 27) {     // ESC kończy program
            break;
        } else if (ch == KEY_UP || ch == KEY_DOWN 
        || ch == KEY_LEFT || ch == KEY_RIGHT) { 
            zwierzak.remember_key(ch);
            zwierzak.do_turn();   
        }
    }

    // --- koniec ncurses ---
    endwin();
    return 0;
}