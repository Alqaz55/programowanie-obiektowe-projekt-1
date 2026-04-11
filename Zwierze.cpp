#include "Zwierze.hpp"

Zwierze::Zwierze(int startx, int starty, Swiat *startworld) : Organizm(startx, starty, startworld)
{

    type = fauna;
}

Zwierze::~Zwierze() {}

void Zwierze::do_turn()
{
    action();
    did_turn = 1;
    wiek++;
}

void Zwierze::action()
{
    int potential_x = x, potential_y = y;

    choose_square(potential_x, potential_y);

    Organizm *opponent = world->get_Pole(potential_x, potential_y)->organisms;
    if (opponent == NULL || opponent == this)
    {

        world->set_Pole(x, y, nullptr);

        x = potential_x;
        y = potential_y;
        world->set_Pole(x, y, this);
    }
    else
    {

        debuguj << get_Draw() << " kolizja z " << opponent->get_Draw() << "x:" << x << " y:" << y << endl;

        opponent->stepped_on(this);
    }
}

void Zwierze::stepped_on(Zwierze *current)
{
    current->collision(this);
}

void Zwierze::collision(Zwierze *opponent)
{

    if (get_Draw() == opponent->get_Draw())
    {
        if(!opponent->did_turn){
            breed();
            opponent->did_turn=1;

        }
    }
    else
    {
        this->attack(opponent);
    }
}

void Zwierze::eat(Roslina *opponent)
{
    world->set_Pole(x, y, NULL);

    this->set_X(opponent->get_X());
    this->set_Y(opponent->get_Y());

    this->set_Age(get_Age() + 3);
    opponent->death();
    world->set_Pole(x, y, this);
}

void Zwierze::breed()
{

    int attempts = 3;
    while (attempts--)
    {

        int potential_x, potential_y;
        choose_square(potential_x, potential_y);
        Organizm *opponent = world->get_Pole(potential_x, potential_y)->organisms;
        if (opponent == NULL && opponent != this)
        {
            create_offspring(potential_x, potential_y);
            return;
        }
    }
}

void Zwierze::attack(Zwierze *opponent)
{

    if (!attacker_avoids(opponent->get_Strength()))
    {

        if (strength >= opponent->get_Strength())
        {
            if (!opponent_dodges(opponent->get_Strength()))
            {

                world->set_Pole(x, y, nullptr);
                x = opponent->get_X();
                y = opponent->get_Y();
                opponent->death();
                world->set_Pole(x, y, this);
            }
        }
        else
        {
            death();
        }
    }
}

int Zwierze::attacker_avoids(int strength)
{
    return false;
}
int Zwierze::opponent_dodges(int strength)
{
    return false;
}

void Zwierze::draw()
{
    char symbol = get_Draw();
    mvaddch(y + 1, x + 1, symbol);
}
