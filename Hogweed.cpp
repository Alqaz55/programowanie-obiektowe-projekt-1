#include "headers/Hogweed.hpp"
#include "headers/World.hpp"

void Hogweed::create_offspring(coordinates place)
{
    Hogweed *offspring = new Hogweed(place, world);
    world->add_to_added(offspring);
    world->set_field(place, offspring);
}

Hogweed::Hogweed(int startX, int startY, World *startworld)
    : Plant(startX, startY, startworld)
{
    strength = HOGWEED_STRENGTH;
    initiative = PLANT_INITIATIVE;
}

Hogweed::Hogweed(coordinates start_place, World *startworld)
    : Plant(start_place, startworld)
{
    strength = PLANT_STRENGTH;
    initiative = PLANT_INITIATIVE;
}
Hogweed::~Hogweed() {}

int Hogweed::get_color() const
{
    return HOGWEED_COLOR;
}

void Hogweed::do_effect(Organism *organism, Collision_effect &result)
{
    organism->death();
    result = DIE;
}


void Hogweed::action()
{

    coordinates place = position;

    for (int i = 0; i < 9; i++)
    {
        place.x = position.x + i % 3 - 1;
        place.y = position.y + i / 3 - 1;

        if (!world->is_in_bounds(place))
        {
            continue;
        }

        if (place == position)
            continue;

        field *square = world->get_field(place);
        if (!square)
            continue;

        Organism *organism = square->organism;

        if (organism != nullptr && dynamic_cast<Animal *>(organism))
        {
            debug_file << organism->get_draw() << "          death by Hogweed" << endl;
            organism->death();
        }
    }
}

char Hogweed::get_draw() const{
    return HOGWEED_CHAR;
}