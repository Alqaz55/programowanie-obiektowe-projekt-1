#include "Zwierze.hpp"

Zwierze::Zwierze(int startx, int starty, Swiat *startworld) : Organizm(startx, starty, startworld)
{

    type = fauna;
    index = organism_number++;
}

Zwierze::~Zwierze() {}

void Zwierze::do_turn()
{
    did_turn = 1;
    wiek++;
    action();
}
int Zwierze::organism_number = 1;
void Zwierze::action()
{
    int potential_x = x, potential_y = y;

    choose_square(potential_x, potential_y);

    debuguj << get_draw() << get_index() << " jest na " << this->get_draw() << "x:" << x << " y:" << y << endl;
    if (potential_x == x && potential_y == y)
    {
    }
    else
    {

        Organizm *opponent = check_pole_of_type(potential_x, potential_y);
        Organizm *plant = world->get_pole(potential_x, potential_y)->roslina;
        if (opponent == this)
        {
            debuguj << get_draw() << get_index() << " stoi na " << this->get_draw() << "x:" << x << " y:" << y << endl;
        }
        else if (opponent == nullptr || (opponent != nullptr && !opponent->is_alive()))
        {

            change_pole_of_type(x, y, nullptr);

            x = potential_x;
            y = potential_y;
            debuguj << get_draw() << get_index() << " idzie na " << this->get_draw() << "x:" << x << " y:" << y << endl;

            change_pole_of_type(x, y, this);
        }
        else if (opponent != nullptr && opponent != this)
        {
            debuguj << get_draw() << get_index() << " kolizja z " << opponent->get_draw() << opponent->get_index() << "   x:" << x << " y:" << y << endl;

            opponent->stepped_on(this);
        }
        if (plant != nullptr)
        {
            plant->stepped_on(this);
        }
    }
}

void Zwierze::stepped_on(Zwierze *current)
{
    current->collision(this);
}

void Zwierze::collision(Zwierze *opponent)
{

    if (get_draw() == opponent->get_draw())
    {
        if (!opponent->did_turn)
        {
            breed();
            opponent->did_turn = 1;
        }
    }
    else
    {
        this->attack(opponent);
    }
}

void Zwierze::eat(Roslina *opponent)
{
    // world->set_pole_roslina(x, y, nullptr);


    this->set_age(get_age() + 3);
    // opponent->death();
}

void Zwierze::breed()
{

    int attempts = 3;
    while (attempts--)
    {

        int potential_x, potential_y;
        choose_square(potential_x, potential_y);
        Organizm *opponent = check_pole_of_type(potential_x, potential_y);
        if (opponent == nullptr)
        {
            create_offspring(potential_x, potential_y);
            debuguj << "udało sie" << endl;
            return;
        }
    }
    debuguj << "nie udało sie";
}

void Zwierze::attack(Zwierze *opponent)
{

    if (!attacker_avoids(opponent->get_strength()))
    {

        if (strength >= opponent->get_strength())
        {
            if (!opponent_dodges(opponent->get_strength()))
            {

                world->set_pole_zwierze(x, y, nullptr);
                x = opponent->get_X();
                y = opponent->get_Y();
                opponent->death();
                world->set_pole_zwierze(x, y, this);
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
    char symbol = get_draw();
    Roslina *plant = world->get_pole(x, y)->roslina;
    if (plant != nullptr && !plant->get_drawn())
    {

        attron(COLOR_PAIR(plant->get_Color()));
        mvaddch(y + 1, x + 1, symbol);
        attroff(COLOR_PAIR(plant->get_Color()));
        plant->set_drawn(1);
    }
    else
    {
        mvaddch(y + 1, x + 1, symbol);
    }
}

char Zwierze::get_draw() const
{
    return 'U';
}

void Zwierze::change_pole_of_type(int setx, int sety, Organizm *organism)
{
    if (organism == nullptr)
    {
        world->set_pole_zwierze(setx, sety, nullptr);
    }
    if (dynamic_cast<Zwierze *>(organism))
    {

        world->set_pole_zwierze(setx, sety, (Zwierze *)organism);
    }
}

Organizm *Zwierze::check_pole_of_type(int x, int y)
{
    return world->get_pole(x, y)->zwierze;
}