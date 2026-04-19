#include "headers/Human.hpp"
#include "headers/World.hpp"

Human::Human(int startX, int startY, World *world)
    : Animal(startX, startY, world)
{
    strength = HUMAN_STRENGTH;
    initiative = HUMAN_INITIATIVE;
    active_skill = 0;
    cooldown = 0;
}

Human::Human(coordinates start_place, World *world)
    : Animal(start_place, world)
{
    strength = HUMAN_STRENGTH;
    initiative = HUMAN_INITIATIVE;
    active_skill = 0;
    cooldown = 0;
}

Human::~Human()
{
}

void Human::create_offspring(coordinates place) {}

char Human::get_draw() const
{
    return HUMAN_CHAR;
}

coordinates Human::choose_movement()
{

    int potential_x, potential_y;
    int dx = 0;
    int dy = 0;

    switch (world->get_key())
    {
    case KEY_UP:
        dy = UP;
        break;
    case KEY_DOWN:
        dy = DOWN;
        break;
    case KEY_LEFT:
        dx = LEFT;
        break;
    case KEY_RIGHT:
        dx = RIGHT;
        break;

    default:
        break;
    }

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

void Human::do_turn()
{

    collision_message = "";
    age++;
    did_turn = 1;
    if (world->get_key() == 'a')
    {

        if (!active_skill && !cooldown)

        {
            active_skill = HUMAN_SKILL;
            use_skill();
        }
    }
    else
    {
        action();
        if (active_skill > 0 && is_alive())
        {
            use_skill();
            active_skill--;
            if (active_skill == 0)
            {
                cooldown = HUMAN_COOLDOWN;
            }
        }
        if (cooldown > 0)
        {
            cooldown--;
        }
    }

    debug_file << "skill:    " << active_skill << "cooldown:  " << cooldown << endl;
    world->update_log_data(this);
}

void Human::use_skill()
{
    coordinates place = position;

    for (int i = 0; i < SURROUNDING_SQUARES; i++)
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
            update_kill();
        }
    }
}

int Human::get_kill_count()
{
    return kill_count;
}

void Human::update_kill()
{
    kill_count++;
}

int Human::get_cooldown()
{
    return cooldown;
}
int Human::get_skill()
{
    return active_skill;
}

void Human::death()
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
        world->update_log_data(this);
    }
}

string Human::get_collision_message()
{
    return collision_message;
}
void Human::set_collision_message(string new_message)
{
    collision_message = new_message;
}

void Human::collision(Animal *opponent, Collision_effect &result)
{
    collision_message = std::string("Collided with ") + opponent->get_draw();
    this->attack(opponent, result);
}