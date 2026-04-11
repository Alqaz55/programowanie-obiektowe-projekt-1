#include "Czlowiek.hpp"
#include "Swiat.hpp"
#include "Wilk.hpp"

// Konstruktor
Czlowiek::Czlowiek(int startX, int startY, Swiat *world)
    : Zwierze(startX, startY, world)
{
    strength = CZLOWIEK_STRENGTH;
    initiative = CZLOWIEK_INITIATIVE;
    active_skill = 0;
    cooldown = 0;
}

Czlowiek::~Czlowiek()
{
}

void Czlowiek::create_offspring(int x, int y) {}

char Czlowiek::get_Draw() const
{
    return CZLOWIEK_CHAR;
}

void Czlowiek::choose_square(int &potential_x, int &potential_y)
{

    int dx = 0;
    int dy = 0;

    switch (world->get_key())
    {
    case KEY_UP:
        dy = UP;
        break;
    case KEY_DOWN:
        dy = DOWN;
        break;
    case KEY_LEFT:
        dx = LEFT;
        break;
    case KEY_RIGHT:
        dx = RIGHT;
        break;

    default:
        break;
    }

    if (!dx && !dy)
    {

        return;
    }
    if (x + dx >= 0 && x + dx < WORLD_WIDTH)
    {
        potential_x = x + dx;
    }
    else
    {
        potential_x = x;
    }
    if (y + dy >= 0 && y + dy < WORLD_HEIGHT)
    {
        potential_y = y + dy;
    }
    else
    {
        potential_y = y;
    }
}

void Czlowiek::action()
{

    debuguj << get_Draw() << "    idzie z x:" << x << "y:" << y << endl;
    int potential_x, potential_y;

    choose_square(potential_x, potential_y);
    if (potential_x == x && potential_y == y)
    {
        return;
    }
    Organizm *opponent = world->get_Pole(potential_x, potential_y)->organisms;
    if (opponent == NULL || opponent == this)
    {

        world->set_Pole(x, y, nullptr);
        x = potential_x;
        y = potential_y;
        world->set_Pole(x, y, this);
    }
    else
    {

        debuguj << get_Draw() << " kolizja z " << opponent->get_Draw() << "x:" << opponent->get_X() << " y:" << opponent->get_Y() << endl;
        opponent->stepped_on(this);
    }
}
void Czlowiek::do_turn()
{

    wiek++;
    did_turn = 1;
    if (world->get_key() == 'a')
    {

        if (!active_skill && !cooldown)

        {
            active_skill = 3;
            use_skill();
        }
    }
    else
    {
        action();
        if (active_skill > 0)
        {
            use_skill();
            active_skill--;
            if (active_skill == 0)
            {
                cooldown = 3;
            }
        }
        if (cooldown > 0)
        {
            cooldown--;
        }
    }
    debuguj << "skill:    " << active_skill << "cooldown:  " << cooldown << endl;
}

void Czlowiek::use_skill()
{

    for (int i = 0; i < 9; i++)
    {
        int current_x = x + i / 3 - 1;
        int current_y = y + i % 3 - 1;

        if (current_x < 0 || current_x >= WORLD_WIDTH ||
            current_y < 0 || current_y >= WORLD_HEIGHT)
            continue;

        if (current_x == x && current_y == y)
            continue;

        pole *p = world->get_Pole(current_x, current_y);
        if (!p)
            continue;

        Organizm *o = p->organisms;

        if (o)
        {
            debuguj << o->get_Draw() << "          smierc skillem" << endl;
            o->death();
        }
    }
}
void Czlowiek::draw()
{
    attron(COLOR_PAIR(KOLOR_MLECZY));
    char symbol = get_Draw();
    mvaddch(y + 1, x + 1, symbol);
    attroff(COLOR_PAIR(KOLOR_MLECZY));
}
