#include "defines.hpp"
#include "Swiat.hpp"
#include "Organizm.hpp"

Organizm::Organizm() {}
Organizm::~Organizm() {}

Organizm::Organizm(int new_x, int new_y, Swiat *new_world)
{
  
    x = new_x;
    y = new_y;
    wiek = 0;
    did_turn = 0;
    next_in_line = nullptr;
    previous = nullptr;
    world = new_world;
}

int Organizm::get_Strength() const { return strength; }
int Organizm::get_Initiative() const { return initiative; }
int Organizm::get_X() const { return x; }
int Organizm::get_Y() const { return y; }
int Organizm::get_Age() const { return wiek; }

Organizm *Organizm::get_next() const { return next_in_line; }
Organizm *Organizm::get_previous() const { return previous; }

void Organizm::set_Strength(int new_strength) { strength = new_strength; }
void Organizm::set_Initiative(int new_initiative) { initiative = new_initiative; }
void Organizm::set_X(int new_x) { x = new_x; }
void Organizm::set_Y(int new_y) { y = new_y; }
void Organizm::set_Age(int new_age) { wiek = new_age; }

void Organizm::set_next(Organizm *new_next) { next_in_line = new_next; }
void Organizm::set_previous(Organizm *new_previous) { previous = new_previous; }

void Organizm::draw() {
mvaddch(y+1, x+1, get_Char());
}
void Organizm::death() { world->add_to_dead(this);}
void Organizm::reset_turn() {
    did_turn=0;
}
