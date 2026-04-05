#include "Wilk.hpp"
#include "Swiat.hpp" // pełna definicja klasy Swiat potrzebna w cpp

// Konstruktor
Wilk::Wilk(int startX, int startY, Swiat *world)
    : Organizm(startX, startY, world), kierunek(0), remembered(0)
{
    strength = 5;
    initiative = 5;
}

Wilk::~Wilk()
{
}

void Wilk::action()
{
}

void Wilk::collision(Organizm *opponent)
{
    if (get_Char() == opponent->get_Char())
    {
        breed();
    }
    else
    {
        if (strength >= opponent->get_Strength())
        {
            world->set_Pole(x, y, nullptr);

            x = opponent->get_X();
            y = opponent->get_Y();
            opponent->death();
            world->set_Pole(x, y, this);
        }
        else
        {

            death();
        }
    }
}

void Wilk::breed()
{

    int direction = rand() % 9;
    int dx = direction % 3 - 1;
    int dy = direction / 3 - 1;
    int potential_x, potential_y;
    if (!dx && !dy)
    {
        return;
    }
    if (x + dx >= 0 && x + dx < WORLD_WIDTH)
    {
        potential_x = x + dx;
    }
    else
    {
        potential_x = x;
    }
    if (y + dy >= 0 && y + dy < WORLD_HEIGHT)
    {
        potential_y = y + dy;
    }
    else
    {
        potential_y = y;
    }
    Organizm *opponent = world->get_Pole(potential_x, potential_y)->organisms;
    if (opponent == NULL && opponent != this)
    {
        Wilk *offspring = new Wilk(potential_x, potential_y, world);
        world->add_to_added(offspring);
        world->set_Pole(potential_x, potential_y, offspring);
    }
}

char Wilk::get_Char() const
{
    return 'W';
}

void Wilk::move()
{
    int direction = rand() % 9;
    int dx = direction % 3 - 1;
    int dy = direction / 3 - 1;
    int potential_x, potential_y;
    if (!dx && !dy)
    {
        return;
    }
    if (x + dx >= 0 && x + dx < WORLD_WIDTH)
    {
        potential_x = x + dx;
    }
    else
    {
        potential_x = x;
    }
    if (y + dy >= 0 && y + dy < WORLD_HEIGHT)
    {
        potential_y = y + dy;
    }
    else
    {
        potential_y = y;
    }
    Organizm *opponent = world->get_Pole(potential_x, potential_y)->organisms;
    if (opponent == NULL || opponent == this)
    {
        debuguj << "Wilk x:" << x << " y:" << y << endl;

        world->set_Pole(x, y, nullptr);

        x = potential_x;
        y = potential_y;
        world->set_Pole(x, y, this);
    }
    else
    {

        debuguj << "Wilk kolizja x:" << x << " y:" << y << endl;

        collision(opponent);
    }
}

void Wilk::do_turn()
{
    move();
    did_turn = 1;
    wiek++;
}
