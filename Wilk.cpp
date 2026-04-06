#include "Wilk.hpp"
#include "Swiat.hpp" // pełna definicja klasy Swiat potrzebna w cpp

// Konstruktor
Wilk::Wilk(int startX, int startY, Swiat *world)
: Zwierze(startX, startY, world)
{
    strength = 5;
    initiative = 5;
}

Wilk::~Wilk()
{
}



void Wilk::create_offspring(int potential_x, int potential_y)
{
    Wilk *offspring = new Wilk(potential_x, potential_y, world);
    world->add_to_added(offspring);
    world->set_Pole(potential_x, potential_y, offspring);
}





char Wilk::get_Draw() const
{
    return 'W';
}


