#include <ncurses.h>

int main()
{
    initscr();             
    cbreak();
    noecho();
    curs_set(0);

    if (!has_colors())
    {
        endwin();
        printf("Terminal nie wspiera kolorow\n");
        return 1;
    }

    start_color();

    // definicje par kolorów (foreground, background)
    init_pair(1, COLOR_RED,     COLOR_BLACK);
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4, COLOR_BLUE,    COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN,    COLOR_BLACK);
    init_pair(7, COLOR_WHITE,   COLOR_BLACK);

    int row = 1;

    mvprintw(0, 2, "NCURSES COLOR DEMO (press any key to exit)");

    for (int i = 1; i <= 7; i++)
    {
        attron(COLOR_PAIR(i));
        mvprintw(row++, 2, "Kolor testowy %d", i);
        attroff(COLOR_PAIR(i));
    }

    // dodatkowy test: kolorowe bloki
    row++;
    for (int i = 1; i <= 7; i++)
    {
        attron(COLOR_PAIR(i));
        mvprintw(row, i * 3, "###");
        attroff(COLOR_PAIR(i));
    }

    refresh();
    getch();

    endwin();
    return 0;
}