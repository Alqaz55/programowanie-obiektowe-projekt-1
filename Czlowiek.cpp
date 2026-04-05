#include "Czlowiek.hpp"
#include "Swiat.hpp"
#include "Wilk.hpp"

// Konstruktor
Czlowiek::Czlowiek(int startX, int startY, Swiat *world)
    : Organizm(startX, startY, world), kierunek(0), remembered(0)
{
    strength = 10;
    initiative = 1;
}

Czlowiek::~Czlowiek()
{
}

void Czlowiek::action()
{
}

void Czlowiek::breed()
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

void Czlowiek::collision(Organizm *opponent)
{
    debuguj << "kolizja" << endl;
    if (get_Char() == opponent->get_Char())
    {

        breed();
    }
    else
    {
        if (strength >= opponent->get_Strength())
        {
            debuguj << "czlowiek pokonal" << endl;

            world->set_Pole(x, y, nullptr);

            x = opponent->get_X();
            y = opponent->get_Y();
            opponent->death();
            world->set_Pole(x, y, this);
        }
        else
        {

            debuguj << "czlowiek zmarl" << endl;

            death();
        }
    }
}

char Czlowiek::get_Char() const
{
    return 'C';
}

void Czlowiek::move()
{

    int dx = 0;
    int dy = 0;

    switch (world->get_key())
    {
    case KEY_UP:
        dy = -1;
        break;
    case KEY_DOWN:
        dy = 1;
        break;
    case KEY_LEFT:
        dx = -1;
        break;
    case KEY_RIGHT:
        dx = 1;
        break;

    default:
        break;
    }

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
        world->set_Pole(x, y, nullptr);

        x = potential_x;
        y = potential_y;
        world->set_Pole(x, y, this);
        debuguj << "Czlowiek x:" << x << " y:" << y << endl;
    }
    else
    {
        debuguj << "Czlowiek kolizja x:" << x << " y:" << y << endl;

        collision(opponent);
    }
}

void Czlowiek::do_turn()
{
    move();
    did_turn = 1;
    wiek++;
}

int Czlowiek::get_key()
{
    return remembered;
}
