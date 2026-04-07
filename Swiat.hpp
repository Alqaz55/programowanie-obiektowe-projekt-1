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
  Organizm* dead_organisms;
  int key;


public:

  Swiat();
  ~Swiat();


  void add_after_a(Organizm *a, Organizm *nowa);
  void remove_after_a(Organizm *a);
  
  
  void start_organisms(Organizm *a);
  void add_to_added(Organizm *nowy);
  void add_to_organisms();
  void delete_dead();
  void add_to_dead(Organizm* nowy);

  
  void remember_key(int key);
  int get_key();
  
  void reset_turn();
  void draw_world();
  void turn();


  pole *get_Pole(int x, int y);
  void set_Pole(int x, int y, Organizm *organism);
  
};