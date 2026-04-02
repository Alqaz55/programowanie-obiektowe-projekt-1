#pragma once
#include "defines.hpp"
#include "zwierzyna/Wilk.hpp"

typedef struct pole{
Organizm* organisms[MAX_ORG_PER_SQUARE];
};


class Swiat {
private:
  int world[WORLD_WIDTH][WORLD_HEIGHT];

Organizm* organisms;
Organizm* added_organisms;

public:

void add_after_a(Organizm *a, Organizm *nowa);

void remove_after_a(Organizm *a);


  Swiat();
  ~Swiat();

  void draw_world();
  void turn();
  void add_to_organisms();
};