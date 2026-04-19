#include "headers/Guarana.hpp"
#include "headers/World.hpp"

void Guarana::create_offspring(coordinates place)
{
    Guarana *offspring = new Guarana(place, world);
    world->add_to_added(offspring);
    world->set_field(place, offspring);
}

Guarana::Guarana(int startX, int startY, World *startworld)
    : Plant(startX, startY, startworld)
{
    strength = PLANT_STRENGTH;
    initiative = PLANT_INITIATIVE;
}

Guarana::Guarana(coordinates start_place, World *startworld)
    : Plant(start_place, startworld)
{
    strength = PLANT_STRENGTH;
    initiative = PLANT_INITIATIVE;
}
Guarana::~Guarana() {}

int Guarana::get_color() const
{
    return GUARANA_COLOR;
}

void Guarana::do_effect(Organism *organism, Collision_effect &result)
{

    organism->set_strength(organism->get_strength() + GUARANA_STRNGTH_ADD);
}



char Guarana::get_draw() const{
    return GUARANA_CHAR;
}