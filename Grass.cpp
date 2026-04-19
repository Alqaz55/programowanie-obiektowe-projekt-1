#include "headers/Grass.hpp"
#include "headers/World.hpp"

void Grass::create_offspring(coordinates place)
{
    Grass *offspring = new Grass(place, world);
    world->add_to_added(offspring);
    world->set_field(place, offspring);
}

Grass::Grass(int startX, int startY, World *startworld)
    : Plant(startX, startY, startworld)
{
    strength = PLANT_STRENGTH;
        initiative = PLANT_INITIATIVE
;
}


Grass::Grass(coordinates start_place, World *startworld)
    : Plant(start_place, startworld)
{
    strength = PLANT_STRENGTH;
        initiative = PLANT_INITIATIVE
;
}

Grass::~Grass(){}

int Grass::get_color() const{
    return GRASS_COLOR;
}



char Grass::get_draw() const{
    return GRASS_CHAR;
}