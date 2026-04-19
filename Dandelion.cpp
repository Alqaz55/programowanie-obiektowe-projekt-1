#include "headers/Dandelion.hpp"

void Dandelion::create_offspring(coordinates place)
{
    Dandelion *offspring = new Dandelion(place, world);
    world->add_to_added(offspring);
    world->set_field(place, offspring);
}

Dandelion::Dandelion(int startX, int startY, World *startworld)
    : Plant(startX, startY, startworld)
{
    strength = PLANT_STRENGTH;
    initiative = PLANT_INITIATIVE;
}

Dandelion::Dandelion(coordinates start_place, World *startworld)
    : Plant(start_place, startworld)
{
    strength = PLANT_STRENGTH;
    initiative = PLANT_INITIATIVE;
}

Dandelion::~Dandelion(){}

int Dandelion::get_color() const{
    return DANDELION_COLOR;
}

char Dandelion::get_draw() const{
    return DANDELION_CHAR;
}

void Dandelion::do_turn(){

    int attempt = DANDELION_ATTEMPT;
    while (attempt--){
        plant();
    }
}