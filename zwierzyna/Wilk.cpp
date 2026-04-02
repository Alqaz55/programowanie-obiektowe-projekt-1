#include "Wilk.hpp"
#include <ncurses.h>

Wilk::Wilk(int startX, int startY)
{
    x = startX;
    y = startY;
    strength = 10;
    initiative = 5;
}

Wilk::~Wilk() = default;

void Wilk::action()
{
}

void Wilk::collision(Organizm *organizm)
{
    // tutaj logika kolizji
}

void Wilk::draw()
{
    mvaddch(y+1, x+1, 'W'); // rysowanie w ncurses
}

void Wilk::move()
{
    int potential_x = 0, potential_y = 0;
    int movement = rand() % 9;
    potential_x = (x + movement % 3 - 1);
    potential_y = y + movement / 3 - 1;
    if (potential_y >= 0 && potential_y < WORLD_HEIGHT){
        set_Y(potential_y);
    }
     if (potential_x >= 0 && potential_x < WORLD_WIDTH){
        set_X(potential_x);
    }
}
void Wilk::do_turn()
{
    move();
}
void Wilk::remember_key(int key) { remembered = key; }
int Wilk::get_key() { return remembered; }