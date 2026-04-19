#include "headers/Nightshade.hpp"
#include "headers/World.hpp"

void Nightshade::create_offspring(coordinates place)
{
    Nightshade *offspring = new Nightshade(place, world);
    world->add_to_added(offspring);
    world->set_field(place, offspring);
}

Nightshade::Nightshade(int startX, int startY, World *startworld)
    : Plant(startX, startY, startworld)
{
    strength = NIGHTSHADE_STRENGTH;
    initiative = PLANT_INITIATIVE;
}

Nightshade::Nightshade(coordinates start_place, World *startworld)
    : Plant(start_place, startworld)
{
    strength = NIGHTSHADE_STRENGTH;
    initiative = PLANT_INITIATIVE;
}
Nightshade::~Nightshade() {}

int Nightshade::get_color() const
{
    return NIGHTSHADE_COLOR;
}

void Nightshade::do_effect(Organism *organism, Collision_effect &result)
{
    organism->death();
    result = DIE;
}



char Nightshade::get_draw() const{
    return NIGHTSHADE_CHAR;
}