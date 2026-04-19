#include "headers/Turtle.hpp"
#include "headers/World.hpp"

Turtle::Turtle(int startX, int startY, World *world)
    : Animal(startX, startY, world)
{
    strength = TURTLE_STRENGTH;
    initiative = TURTLE_INITIATIVE;
}


Turtle::Turtle(coordinates start_place, World *world)
    : Animal(start_place, world)
{
    strength = TURTLE_STRENGTH;
    initiative = TURTLE_INITIATIVE;
}

Turtle::~Turtle()
{
}

void Turtle::create_offspring(coordinates place)
{
    Turtle *offspring = new Turtle(place, world);
    debug_file << "new Turtle" << offspring->get_index() << "   x:" << place.x << "y:  " << place.y << endl;

    world->add_to_added(offspring);
    world->set_field(place, offspring);
}

char Turtle::get_draw() const
{
    return TURTLE_CHAR;
}

int Turtle::opponent_dodges(int attacker_strength)
{
    if (attacker_strength < TURTLE_DODGES)
    {
        debug_file << "Turtle sie schowal" << endl;
        return 1;
    }
    return 0;
}

coordinates Turtle::choose_movement()
{
    coordinates place = position;
    if (rand() % TURTLE_MOVEMENT_CHANCE)
    {
        place = choose_square();
    }
    return place;
}
