#include "Roslina.hpp"

// Konstruktor
Roslina::Roslina(int startX, int startY, Swiat *startworld)
    : Organizm(startX, startY, startworld)
{
   
    initiative = 0;
    type = flora;
}

// Destruktor
Roslina::~Roslina()
{
}

void Roslina::plant()
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

// Akcja rośliny
void Roslina::action()
{
    // pusta implementacja
}

// Tura organizmu
void Roslina::do_turn()
{
    plant();
    debuguj << "uwu"<< endl;
}

// Czy została narysowana
void Roslina::is_drawn()
{
    // pusta implementacja
}

void Roslina::draw()
{
    int color = get_Color();
    attron(COLOR_PAIR(color));
    mvaddch(y + 1, x + 1, 'R');
    attroff(COLOR_PAIR(color));
}


void Roslina::stepped_on(Zwierze* current){
    current->eat(this);
}


char Roslina::get_Draw() const{
    return 'R';
}