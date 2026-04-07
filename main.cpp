#include <ncurses.h>
#include "Wilk.hpp"
#include "Czlowiek.hpp"
#include "Trawa.hpp"

ofstream debuguj("debug.txt");

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

int main()
{

    srand(time(NULL));
    // --- ncurses init ---
    initscr();            // start ncurses
    cbreak();             // wyłącza buforowanie linii
    noecho();             // nie pokazuje wpisywanych znaków
    curs_set(0);          // ukrywa kursor
    keypad(stdscr, TRUE); // włącz obsługę klawiszy specjalnych
    start_color();

    init_pair(KOLOR_TRAWY,COLOR_BLUE, COLOR_GREEN);
    init_pair(KOLOR_MLECZY,COLOR_BLACK, COLOR_YELLOW);


   
    
    Swiat *swiat = new Swiat;
    // --- Tworzymy wilka ---
    Wilk *zwierzak = new Wilk(2, 2, swiat);
        Wilk* zwierzak2=new Wilk(2, 3, swiat);

    Czlowiek* czlowiek=new Czlowiek(2, 4, swiat);
    Trawa* trawka = new Trawa(7,7,swiat);

    swiat->add_to_added(zwierzak);
    swiat->add_to_added(zwierzak2);
    swiat->add_to_added(trawka);
    swiat->add_to_added(czlowiek);

    swiat->add_to_organisms();

    int ch;
    while (true)
    {

        clear();
        draw_frame(WORLD_WIDTH, WORLD_HEIGHT);
        swiat->draw_world();
        mvaddch(20, 0, swiat->get_key());
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