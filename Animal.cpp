#include "headers/Animal.hpp"

Animal::Animal(int startx, int starty, World *startworld) : Organism(startx, starty, startworld)
{

    type = fauna;
    index = organism_number++;
}

Animal::Animal(coordinates start_place, World *startworld) : Organism(start_place, startworld)
{
    type = fauna;
    index = organism_number++;
}

Animal::~Animal() {}

void Animal::do_turn()
{
    did_turn = 1;
    age++;
    log_map_file << get_draw() << get_index() << "   x:" << position.x << "   y: " << position.y << endl;

    if (is_alive())
        action();

    log_map_file << get_draw() << get_index() << "   x:" << position.x << "   y: " << position.y << endl;
    world->log_map();
}

int Animal::organism_number = 1;

void Animal::action()
{

    if (!is_alive())
    {
        return;
    }
    coordinates new_square = choose_movement();
    if (!world->is_in_bounds(new_square))
    {
        return;
    }
    Collision_effect result = MOVE;

    debug_file << get_draw() << get_index() << " is on " << this->get_draw() << "x:" << position.x << " y:" << position.y << endl;
    debug_file << "has strength:     " << strength << endl;
    if (new_square != position)
    {
        Organism *opponent = check_organism(new_square);

        if (opponent == nullptr || !opponent->is_alive())
        {
            debug_file << get_draw() << get_index() << " goes to " << this->get_draw() << "x:" << new_square.x << " y:" << new_square.y << endl;
            result = MOVE;
        }
        else if (opponent != nullptr && opponent != this)
        {
            debug_file << get_draw() << get_index() << " collides with " << opponent->get_draw() << opponent->get_index() << "   x:" << opponent->get_x() << " y:" << opponent->get_y() << endl;

            opponent->stepped_on(this, result);
            if (!is_alive())
            {
                return;
            }
        }
    }
    else
    {
        debug_file << get_draw() << get_index() << " stays on " << this->get_draw() << "x:" << position.x << " y:" << position.y << endl;
    }

    if (result == MOVE)
    {
        move_to(new_square);
    }
}

void Animal::stepped_on(Animal *current, Collision_effect &result)
{
    current->collision(this, result);
}

void Animal::collision(Animal *opponent, Collision_effect &result)
{

    if (get_draw() == opponent->get_draw())
    {
        if (!opponent->get_bred())
        {
            breed(result);
            opponent->set_bred(1);
            set_bred(1);
        }
        result = STAY;
    }
    else
    {
        this->attack(opponent, result);
    }
}

void Animal::eat(Plant *opponent, Collision_effect &result)
{
    opponent->death();
    {
        opponent->do_effect(this, result);
    }
}

void Animal::breed(Collision_effect &result)
{

    coordinates potential_square = choose_square();
    Organism *organism = check_organism(potential_square);

    if (check_organism(potential_square) == nullptr)
    {
        create_offspring(potential_square);
        debug_file << "succesfull breed" << endl;
        return;
    }

    debug_file << "unsuccesfull breed";
}

void Animal::attack(Animal *opponent, Collision_effect &result)
{
    if (!attacker_avoids(opponent->get_strength()))
    {

        if (strength >= opponent->get_strength())
        {
            if (!opponent->opponent_dodges(get_strength()))
            {
                debug_file << endl
                        << "killed opponent" << endl;

                result = MOVE;
                opponent->death();
                update_kill();
            }
            else
                result = STAY;
        }
        else
        {
            debug_file << endl
                    << "died from opponent" << endl;
            opponent->update_kill();
            death();
            result = DIE;
        }
    }
    else
    {
        debug_file << endl
                << "ran away" << endl;
        result = STAY;
    }
}

int Animal::attacker_avoids(int strength)
{
    return false;
}

int Animal::opponent_dodges(int strength)
{
    return false;
}

char Animal::get_draw() const
{
    return '?';
}



coordinates Animal::choose_movement()
{
    return this->choose_square();
}


void Animal::draw_on_coordinates(int x, int y)
{
    mvaddch(y + BORDER, x + BORDER, get_draw());
}
