#include "headers/Antelope.hpp"
#include "headers/World.hpp"

Antelope::Antelope(int startX, int startY, World *world)
    : Animal(startX, startY, world)
{
    strength = ANTELOPE_STRENGTH;
    initiative = ANTELOPE_INITIATIVE;
}

Antelope::Antelope(coordinates start_place, World *world)
    : Animal(start_place, world)
{
    strength = ANTELOPE_STRENGTH;
    initiative = ANTELOPE_INITIATIVE;
}

Antelope::~Antelope()
{
}

void Antelope::create_offspring(coordinates place)
{
    Antelope *offspring = new Antelope(place, world);
    debug_file << "new Antelope" << offspring->get_index() << "   x:" << place.x << " y:  " << place.y << endl;

    world->add_to_added(offspring);
    world->set_field(place, offspring);
}

char Antelope::get_draw() const
{
    return ANTELOPE_CHAR;
}

coordinates Antelope::choose_movement()
{
    int potential_x, potential_y;
    int direction = rand() % 25;
    int dx = direction % 5 - 2;
    int dy = direction / 5 - 2;

    if (position.x + dx >= 0 && position.x + dx < world->get_width())
    {
        potential_x = position.x + dx;
    }
    else
    {
        potential_x = position.x;
    }
    if (position.y + dy >= 0 && position.y + dy < world->get_height())
    {
        potential_y = position.y + dy;
    }
    else
    {
        potential_y = position.y;
    }
    coordinates place = position;
    place.x = potential_x;
    place.y = potential_y;
    return place;
}

int Antelope::opponent_dodges(int strength)
{

    if (rand() % ANTELOPE_MISS_CHANCE)
    {

        coordinates possible_escape = choose_first_available();
        if (possible_escape == position)
        {
            return 0;
        }
        else
        {
            move_to(possible_escape);
            debug_file << "Antelope ran away" << endl;
            return 1;
        }
    }
    return 0;
}