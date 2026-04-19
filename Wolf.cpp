#include "headers/Wolf.hpp"
#include "headers/World.hpp"
Wolf::Wolf(int startX, int startY, World *world)
    : Animal(startX, startY, world)
{
    strength = WOLF_STRENGTH;
    initiative = WOLF_INITIATIVE;
}
Wolf::Wolf(coordinates start_place, World *world)
    : Animal(start_place, world)
{
    strength = WOLF_STRENGTH;
    initiative = WOLF_INITIATIVE;
}

Wolf::~Wolf()
{
}

void Wolf::create_offspring(coordinates place)
{
    Wolf *offspring = new Wolf(place, world);
    debug_file << "new Wolf" << offspring->get_index() << "   x:" << place.x << "y:  " << place.y << endl;

    world->add_to_added(offspring);
    world->set_field(place, offspring);
}

char Wolf::get_draw() const
{
    return WOLF_CHAR;
}
