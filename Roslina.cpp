#include "Roslina.hpp"

// Konstruktor
Roslina::Roslina(int startX, int startY, Swiat *startworld)
    : Organizm(startX, startY, startworld)
{

    initiative = 1;
    type = flora;
    alive = 1;
    index=organism_number++;
}

// Destruktor
Roslina::~Roslina()
{
}
int Roslina::organism_number=1;

void Roslina::plant()
{
    int attempts = 10;
    while (attempts--)
    {
        int potential_x, potential_y;
        choose_square(potential_x, potential_y);
        pole *square = world->get_pole(potential_x, potential_y);
        if (square->zwierze == nullptr && square->roslina == nullptr && square->roslina != this)
        {
            create_offspring(potential_x, potential_y);
            return;
        }
    }
}

void Roslina::action()
{
}
void Roslina::reset_turn()
{
    did_turn = 0;
    drawn = 0;
}

void Roslina::do_turn()
{
    plant();
}

void Roslina::is_drawn()
{
    drawn = 1;
}

void Roslina::draw()
{
    if (!drawn)
    {

        int color = get_Color();
        attron(COLOR_PAIR(color));
        mvaddch(y + 1, x + 1, ' ');
        attroff(COLOR_PAIR(color));
    }
}

void Roslina::stepped_on(Zwierze *current)
{
    current->eat(this);
}

char Roslina::get_draw() const
{
    return 'R';
}

int Roslina::get_Color() const
{
    return BRAK_KOLORU;
}
void Roslina::create_offspring(int x, int y)
{
}
void Roslina::change_pole_of_type(int setx, int sety, Organizm *organism)
{
    if (organism == nullptr)
    {
        world->set_pole_roslina(setx, sety, nullptr);
    }
    if (dynamic_cast<Roslina *>(organism))
    {

        world->set_pole_roslina(setx, sety, (Roslina *)organism);
    }
}

Organizm* Roslina::check_pole_of_type(int x, int y){
    return world->get_pole(x,y)->roslina;
}