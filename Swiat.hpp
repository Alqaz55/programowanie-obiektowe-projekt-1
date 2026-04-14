#pragma once
#include "defines.hpp"
class Organizm;
class Zwierze;
class Roslina;


struct pole
{
  Zwierze *zwierze;
  Roslina *roslina;
};

class Swiat
{
private:
  pole world[WORLD_WIDTH][WORLD_HEIGHT];

  Organizm *added_organisms;
  Organizm *dead_organisms;
  int key;
  
  public:
  Organizm *organisms;
  Swiat();
  ~Swiat();

  void add_after_a(Organizm *a, Organizm *nowa);
  void remove_after_a(Organizm *a);

  void start_organisms(Organizm *a);
  void add_to_added(Organizm *nowy);
  void add_to_organisms();
  void delete_dead();
  void add_to_dead(Organizm *nowy);

  void remember_key(int key);
  int get_key();

  void reset_turn();
  void draw_world();
  void turn();

  void delete_list(Organizm *&head);

  pole *get_pole(int x, int y);
  void set_pole(int x, int y, Roslina* plant, Zwierze* animal);
  void set_pole_zwierze(int x, int y, Zwierze* animal);
  void set_pole_roslina(int x, int y, Roslina* plant);


};