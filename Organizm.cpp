#include "Organizm.hpp"

Organizm::Organizm() : strength(0), initiative(0), x(0), y(0) {}
Organizm::~Organizm() = default;

int Organizm::get_Strength() const { return strength; }
int Organizm::get_Initiative() const { return initiative; }
int Organizm::get_X() const { return x; }
int Organizm::get_Y() const { return y; }
int Organizm::get_Age() const { return wiek; }
Organizm* Organizm::get_next() const { return next_in_line; }

void Organizm::set_Strength(int new_strength) { strength = new_strength; }
void Organizm::set_Initiative(int new_initiative) { initiative = new_initiative; }
void Organizm::set_X(int new_x) { x = new_x; }
void Organizm::set_Y(int new_y) { y = new_y; }
void Organizm::set_Age(){ wiek = 0; }
void Organizm::set_next(Organizm* new_next) {  next_in_line = new_next;}