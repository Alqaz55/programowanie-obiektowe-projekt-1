#include "headers/Plant.hpp"

Plant::Plant(int startX, int startY, World *startworld)
    : Organism(startX, startY, startworld)
{

    initiative = PLANT_INITIATIVE;
    type = flora;
    alive = 1;
    index = organism_number++;
}

Plant::Plant(coordinates start_place, World *startworld)
    : Organism(start_place, startworld)
{

    initiative = PLANT_INITIATIVE;
    type = flora;
    alive = 1;
    index = organism_number++;
}

Plant::~Plant()
{
}
int Plant::organism_number = 1;

void Plant::plant()
{

    int potential_x, potential_y;
    coordinates new_square = choose_square();
    Organism *organism = check_organism(new_square);
    if (organism == nullptr)
    {
        create_offspring(new_square);
        set_bred(1);
        return;
    }
}

void Plant::action()
{
}


void Plant::do_turn()
{
    plant();
    action();
}

void Plant::is_drawn()
{
    drawn = 1;
}



void Plant::stepped_on(Animal *current, Collision_effect &result)
{
    current->eat(this, result);
}

char Plant::get_draw() const
{
    return 'R';
}

int Plant::get_color() const
{
    return NO_COLOR;
}
void Plant::create_offspring(coordinates place)
{
}


void Plant::do_effect(Organism *organism, Collision_effect &result)
{
}




void Plant::draw_on_coordinates(int x, int y)
{
    attron(COLOR_PAIR(get_color()));
    mvaddch(y + BORDER, x + BORDER, ' ');
    attroff(COLOR_PAIR(get_color()));
}

void Plant::log_organism() {}
