#pragma once
#include "defines.hpp"
class Organism;
class Animal;
class Plant;
class Human;

struct field
{
  Organism *organism;
};

struct coordinates
{
  int x;
  int y;
  bool operator==(const coordinates &other) const
  {
    return x == other.x && y == other.y;
  }

  bool operator!=(const coordinates &other) const
  {
    return !(x == other.x && y == other.y);
  }
};

struct log_menu
{
  int player_kill_count;
  int alive;
  int width;
  int height;
  int current_x;
  int current_y;
  int skill_time;
  int strength;
  int skill_cooldown;
  string collision_message;
};

class World
{
private:
  field *world;

  Organism *added_organisms;
  int key;
  
  log_menu log_data;
  int world_height;
  int world_width;
  Organism *organisms;
  static int turn_number;
  
  public:
  World(int height, int width);
  ~World();

  void add_after_a(Organism *a, Organism *new_organism);

  void add_to_added(Organism *new_organism);
  void add_to_organisms();
  void delete_dead();
  void add_to_dead(Organism *new_organism);

  int get_width();
  int get_height();

  void remember_key(int key);
  int get_key();

  void reset_turn();
  void draw_map();
  void log_map();
  void draw_log();
  void turn();
  int choose_map();
  void game_loop();

  void delete_list(Organism *&head);

  field *get_field(coordinates place);
  void set_field(coordinates place, Organism *organism);
  int organism_comes_before(Organism *organism, Organism *checked);
  int is_in_bounds(coordinates place);
  void start_game();

  void update_log_data(Human *player);

  Organism *create_from_symbol(char symbol, int new_x, int new_y);
  void save_to_file(std::ofstream &out);
  int load_from_file(std::istream &in);
  void draw_frame(int width, int height, int start_x, int start_y);
};