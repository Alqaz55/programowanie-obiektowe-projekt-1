#include "Czlowiek.hpp"
#include "Swiat.hpp"
#include "Wilk.hpp"

// Konstruktor
Czlowiek::Czlowiek(int startX, int startY, Swiat *world)
    : Zwierze(startX, startY, world)
{
    strength = 10;
    initiative = 50;
}

Czlowiek::~Czlowiek()
{
}

void Czlowiek::breed()
{
}

void Czlowiek::create_offspring(int x, int y) {}

char Czlowiek::get_Draw() const
{
    return 'C';
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
