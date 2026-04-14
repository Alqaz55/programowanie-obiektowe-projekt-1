#include "Wilk.hpp"
#include "Swiat.hpp" // pełna definicja klasy Swiat potrzebna w cpp

// Konstruktor
Wilk::Wilk(int startX, int startY, Swiat *world)
    : Zwierze(startX, startY, world)
{
    strength = WILK_STRENGTH;
    initiative = WILK_INITIATIVE;
}

Wilk::~Wilk()
{
}

void Wilk::create_offspring(int potential_x, int potential_y)
{
    Wilk *offspring = new Wilk(potential_x, potential_y, world);
    debuguj << "nowy Wilk" << offspring->get_index() << "   x:" << potential_x << "y:  " << potential_y << endl;

    world->add_to_added(offspring);
    world->set_pole_zwierze(potential_x, potential_y, offspring);
}

char Wilk::get_draw() const
{
    return WILK_CHAR;
}
