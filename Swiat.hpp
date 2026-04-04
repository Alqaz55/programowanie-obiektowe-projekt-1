#pragma once
#include "defines.hpp"
class Organizm;

struct pole
{
  Organizm *organisms;
};

class Swiat
{
private:
  pole world[WORLD_WIDTH][WORLD_HEIGHT];

  Organizm *organisms;
  Organizm *added_organisms;
  int key;

public:
  void start_list(Organizm *a);

  void add_after_a(Organizm *a, Organizm *nowa);

  void remove_after_a(Organizm *a);


  void add_to_added(Organizm *nowy);


  Swiat();
  ~Swiat();

  void remember_key(int key);
  int get_key();

  void draw_world();
  void turn();
  void add_to_organisms();
  pole *get_Pole(int x, int y);
  void set_Pole(int x, int y, Organizm *organism);
};