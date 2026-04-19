#include "headers/Fox.hpp"




Fox::Fox(int startX, int startY, World *world)

    : Animal(startX, startY, world)
{
    strength = FOX_STRENGTH;
    initiative = FOX_INITIATIVE;
}

Fox::Fox(coordinates start_place, World *world)
    : Animal(start_place, world)
{
    strength = FOX_STRENGTH;
    initiative = FOX_INITIATIVE;
}

Fox::~Fox()
{
}

void Fox::create_offspring(coordinates place)
{
    Fox *offspring = new Fox(place, world);
    debug_file << "new Fox" << offspring->get_index() << "   x:" << place.x << "y:  " << place.y << endl;
    world->add_to_added(offspring);
    world->set_field(place, offspring);
}

char Fox::get_draw() const
{
    return FOX_CHAR;
}

int Fox::attacker_avoids(int opponent_strength)
{
    if (strength < opponent_strength)
    {
        debug_file << "Fox ran away" << endl;
        return 1;
    }
    else
    {
        debug_file << "Fox didn't run away" << endl;
        return 0;
    }
    return 0;
}
