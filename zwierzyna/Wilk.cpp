#include "Wilk.hpp"
#include <ncurses.h>




Wilk::Wilk(int startX, int startY, Swiat* world)
{
    x = startX;
    y = startY;
    strength = 10;
    initiative = 5;
    this->swiat=world;
}

Wilk::~Wilk() = default;

void Wilk::action()
{
}

void Wilk::collision(Organizm *organizm)
{
   cout << "uwu";
}

char Wilk::get_Char() const
{
   return 'W';
}

void Wilk::move()
{
    int potential_x, potential_y;
    int movement = rand() % 9;
    int dx, dy;
    dx = (movement % 3 - 1);
    dy = movement / 3 - 1;
    if (!dx && !dy)
    {
        return;
    }
    potential_x = x + dx;
    potential_y = y + dy;
    if (potential_y < 0 || potential_y >= WORLD_HEIGHT)
    {
        potential_y -=dy;
    }
    if (potential_x < 0 || potential_x >= WORLD_WIDTH)
    {
        potential_x -= dx;
    }

    if(potential_x == x && potential_y == y){
        return;
    }

    pole *square = swiat->get_Pole(potential_x, potential_y);
    if (square->organisms == NULL)
    {
        this->swiat->set_Pole(x, y, NULL);
        set_X(potential_x);
        set_Y(potential_y);
        this->swiat->set_Pole(x, y, this);

    }
    else collision(square->organisms);
}
void Wilk::do_turn()
{
    move();
}
void Wilk::remember_key(int key) { remembered = key; }
int Wilk::get_key() { return remembered; }