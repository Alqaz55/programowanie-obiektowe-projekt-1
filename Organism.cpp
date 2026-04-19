#include "headers/defines.hpp"
#include "headers/World.hpp"
#include "headers/Organism.hpp"
#include "headers/Plant.hpp"
#include "headers/Animal.hpp"

class Animal;
class Plant;

Organism::Organism() {}
Organism::~Organism() {}

Organism::Organism(int new_x, int new_y, World *new_world)
{

    position.x = new_x;
    position.y = new_y;
    age = 0;
    did_turn = 0;
    drawn = 0;
    next_in_line = nullptr;
    previous = nullptr;
    world = new_world;
    alive = 1;
}

Organism::Organism(coordinates place, World *new_world)
{

    position.x = place.x;
    position.y = place.y;
    age = 0;
    did_turn = 0;
    drawn = 0;
    next_in_line = nullptr;
    previous = nullptr;
    world = new_world;
    alive = 1;
}

int Organism::get_strength() const { return strength; }
int Organism::get_initiative() const { return initiative; }
int Organism::get_x() const { return position.x; }
int Organism::get_y() const { return position.y; }
coordinates Organism::get_field() const { return position; }
int Organism::get_age() const { return age; }
int Organism::is_alive() const { return alive; }

Organism *Organism::get_next() const { return next_in_line; }
Organism *Organism::get_previous() const { return previous; }

void Organism::set_strength(int new_strength) { strength = new_strength; }
void Organism::set_initiave(int new_initiative) { initiative = new_initiative; }
void Organism::set_x(int new_x) { position.x = new_x; }
void Organism::set_y(int new_y) { position.y = new_y; }
void Organism::set_age(int new_age) { age = new_age; }

void Organism::set_next(Organism *new_next) { next_in_line = new_next; }
void Organism::set_previous(Organism *new_previous) { previous = new_previous; }

void Organism::death()
{
    if (!alive)
    {
        return;
    }
    else
    {
        alive = 0;
        set_drawn(1);
        debug_file << "dies          " << get_draw() << get_index() << endl;
        this->change_field(position, nullptr);
    }
}
void Organism::reset_turn()
{
    did_turn = 0;
    bred = 0;
}

int Organism::can_spawn()
{
    coordinates square = get_field();
    if (check_organism(square) == nullptr || check_organism(square) == this)
    {
        return 1;
    }
    return 0;
}
coordinates Organism::choose_square()
{
    int potential_x, potential_y;
    int direction = rand() % 9;
    int dx = direction % 3 - 1;
    int dy = direction / 3 - 1;
    coordinates place = position;

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
    place.x = potential_x;
    place.y = potential_y;
    return place;
}

int Organism::get_index()
{
    return index;
}

typ Organism::get_type() { return type; }

Organism *Organism::check_organism(coordinates place)
{
    Organism *org = world->get_field(place)->organism;
    if (org != nullptr && !org->is_alive())
    {
        return nullptr;
    }
    return org;
}



void Organism::set_drawn(int new_drawn)
{
    drawn = new_drawn;
}

int Organism::get_bred()
{
    return bred;
}
void Organism::set_bred(int value)
{
    bred = value;
}

void Organism::move_to(coordinates place)
{
    change_field(position, nullptr);
    change_field(place, this);
    set_field_this(place);
}

void Organism::change_field(coordinates place, Organism *organism)
{

    if (world->is_in_bounds(place))
    {
        if (organism == nullptr)
        {
            world->set_field(place, nullptr);
        }

        world->set_field(place, organism);
    }
}

void Organism::set_field_this(coordinates place)
{
    position.x = place.x;
    position.y = place.y;
}

void Organism::log_organism()
{
    debug_file << get_draw() << get_index() << " is on:   x:" << position.x << "    y: " << position.y << "     ";
    if (is_alive())
    {
        debug_file << "alive" << endl;
    }
    else
    {
        debug_file << "dead" << endl;
    }
}

coordinates Organism::choose_first_available()
{
    coordinates current = position;

    int offset = rand() % 9;

    for (int i = offset; i < 9 + offset; i++)
    {
        int dx = (i % 9) % 3 - 1;
        int dy = (i % 9) / 3 - 1;
        current.x = position.x + dx;
        current.y = position.y + dy;
        if (world->is_in_bounds(current) && (check_organism(current) == nullptr || check_organism(current)->is_alive()))
        {
            return current;
        }
    }
    return position;
}

void Organism::output_organism(std::ofstream &out)
{
    if (!is_alive())
        return;
    out << get_draw() << " "
        << get_initiative() << " "
        << get_strength() << " "
        << get_age() << " "
        << get_x() << " "
        << get_y()
        << "\n";
}

void Organism::update_kill() {}