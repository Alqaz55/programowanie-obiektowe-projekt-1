#include <ncurses.h>
#include "zwierzyna/Wilk.hpp"
#include "zwierzyna/Czlowiek.hpp"

void draw_frame(int width, int height)
{
    // górna i dolna krawędź
    for (int x = 0; x <= width; x++)
    {
        mvaddch(0, x, '#');
        mvaddch(height + 1, x, '#');
    }

    // lewa i prawa krawędź
    for (int y = 0; y <= height; y++)
    {
        mvaddch(y, 0, '#');
        mvaddch(y, width + 1, '#');
    }
}
FILE *plik = fopen("pliczek.txt", "w");

int main()
{

    srand(time(NULL));
    // --- ncurses init ---
    initscr();            // start ncurses
    cbreak();             // wyłącza buforowanie linii
    noecho();             // nie pokazuje wpisywanych znaków
    curs_set(0);          // ukrywa kursor
    keypad(stdscr, TRUE); // włącz obsługę klawiszy specjalnych

    Swiat *swiat = new Swiat;
    // --- Tworzymy wilka ---
    Wilk zwierzak(2, 2, swiat);
    Czlowiek czlowiek(2, 3, swiat);

    swiat->add_to_added(&czlowiek);
    swiat->add_to_added(&zwierzak);

    swiat->add_to_organisms();

    int ch;
    while (true)
    {

        clear();
        draw_frame(WORLD_WIDTH, WORLD_HEIGHT);
        zwierzak.draw(); // rysuje wilka
        czlowiek.draw();
        mvaddch(15, 0, swiat->get_key());
        refresh();

        ch = getch(); // czekamy na klawisz

        if (ch == 27)
        { // ESC kończy program
            break;
        }
        else if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)
        {
            swiat->remember_key(ch);

            swiat->turn();
        }
        else if (ch == 'a' || ch == 'b')
        {
            swiat->remember_key(ch);
        }
    }

    // --- koniec ncurses ---
    endwin();
    delete swiat;
    return 0;
}