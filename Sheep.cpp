#include "headers/Sheep.hpp"
#include "headers/World.hpp" 
Sheep::Sheep(int startX, int startY, World *world)
: Animal(startX, startY, world)
{
    strength = SHEEP_STRENGTH;
    initiative = SHEEP_INITIATIVE;
}


Sheep::Sheep(coordinates start_place, World *world)
: Animal(start_place, world)
{
    strength = SHEEP_STRENGTH;
    initiative = SHEEP_INITIATIVE;
}

Sheep::~Sheep()
{
}



void Sheep::create_offspring(coordinates place)
{
    Sheep *offspring = new Sheep(place, world);
    world->add_to_added(offspring);
    world->set_field(place, offspring);
}





char Sheep::get_draw() const
{
    return SHEEP_CHAR;
}


