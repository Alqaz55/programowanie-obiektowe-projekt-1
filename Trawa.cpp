#include "Trawa.hpp"

void Trawa::create_offspring(int potential_x, int potential_y)
{
    Trawa *offspring = new Trawa(potential_x, potential_y, world);
    world->add_to_added(offspring);
    world->set_Pole(potential_x, potential_y, offspring);
}

Trawa::Trawa(int startX, int startY, Swiat *startworld)
    : Roslina(startX, startY, startworld)
{
    strength = 0;
    initiative = 0;
}

Trawa::~Trawa(){}

int Trawa::get_Color() const{
    return KOLOR_TRAWY;
}