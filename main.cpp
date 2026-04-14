#include <ncurses.h>
#include "Wilk.hpp"
#include "Czlowiek.hpp"
#include "Trawa.hpp"
#include "Lis.hpp"

ofstream debuguj("debug.txt");
ofstream loguj_mape("map.txt");

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
        mvaddch(y, width + 2, '#');
    }
}

int main()
{

    srand(time(NULL));
    // --- ncurses init ---
    initscr();   // start ncurses
    cbreak();    // wyłącza buforowanie linii
    noecho();    // nie pokazuje wpisywanych znaków
    curs_set(0); // ukrywa kursor
    keypad(stdscr, TRUE);
    start_color();

    init_pair(KOLOR_TRAWY, COLOR_BLACK, COLOR_GREEN);
    init_pair(KOLOR_MLECZY, COLOR_CYAN, COLOR_BLACK);

    Swiat *swiat = new Swiat;

    Wilk *zwierzak1 = new Wilk(2, 2, swiat);
    Wilk *zwierzak2 = new Wilk(2, 3, swiat);
    Wilk *zwierzak3 = new Wilk(2, 3, swiat);

    swiat->add_to_added(zwierzak1);
    swiat->add_to_added(zwierzak2);
    swiat->add_to_added(zwierzak3);

    // Lis *lisek = new Lis(3, 6, swiat);
    // Lis *lisek2 = new Lis(2, 6, swiat);

    // swiat->add_to_added(lisek2);
    // swiat->add_to_added(lisek);

    // Czlowiek *czlowiek = new Czlowiek(3, 3, swiat);
    // swiat->add_to_added(czlowiek);

    Trawa *trawka1 = new Trawa(2, 2, swiat);
    swiat->add_to_added(trawka1);

    Trawa *trawka = new Trawa(1, 1, swiat);
    swiat->add_to_added(trawka);

    swiat->add_to_organisms();
    int ch;

    Organizm *current = swiat->organisms;
    while (current != nullptr)
    {
        if (current->is_alive())
        {

            debuguj << current->get_draw() << current->get_index() << "  x: " << current->get_X() << "  y: " << current->get_Y() << "  age: " << current->get_age() << endl;
        }
        current = current->get_next();
    }

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
        else if (ch == 'a' || ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)
        {
            swiat->remember_key(ch);
        }
        else if (ch == 'n')
        {
            swiat->turn();
            for (int i = 0; i < WORLD_HEIGHT; i++)
            {
                for (int j = 0; j < WORLD_WIDTH; j++)
                {
                    Zwierze *map = swiat->get_pole(j, i)->zwierze;
                    if (map != nullptr)
                    {
                        loguj_mape << map->get_index();
                    }
                    else
                        loguj_mape << ".";
                }
                loguj_mape << endl;
            }
            loguj_mape << endl;
            loguj_mape << endl;
            loguj_mape << endl;
        }
        swiat->remember_key(RESET_DIRECTION);
    }

    endwin();
    delete swiat;
    return 0;
}