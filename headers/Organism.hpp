#pragma once
#include "defines.hpp"
#include "World.hpp"

class Plant;
class Animal;

class Organism
{
protected:
    int strength;
    int initiative;
    coordinates position;
    int age;
    int did_turn;
    int alive;
    int drawn;
    typ type;
    Organism *next_in_line;
    Organism *previous;
    World *world;
    int index;
    int bred;

public:
    Organism();
    Organism(int new_x, int new_y, World *new_world);

    Organism(coordinates place, World *new_world);

    virtual ~Organism();

    int get_strength() const;
    int get_initiative() const;
    int get_x() const;
    int get_y() const;
    int get_age() const;
    int is_alive() const;
    coordinates get_field() const;

    virtual Organism *get_next() const;
    virtual Organism *get_previous() const;
    int get_bred();
    void set_bred(int value);

     void set_strength(int new_strength);
     void set_initiave(int new_initiative);
     void set_x(int new_x);
     void set_y(int new_y);
    void set_field(int new_x, int new_y);
    void set_field_this(coordinates new_posiiton);
     void set_age(int new_age);
     void set_drawn(int new_drawn);

    typ get_type();
     void set_next(Organism *new_next);
     void set_previous(Organism *new_previous);

    virtual coordinates choose_square();
    virtual void create_offspring(coordinates place) = 0;

    virtual char get_draw() const = 0;
    virtual void do_turn() = 0;
    virtual void draw_on_coordinates(int x, int y) = 0;
    virtual void death();
     void reset_turn();
    virtual void stepped_on(Animal *organism, Collision_effect &result) = 0;
    int get_index();

    void move_to(coordinates new_position);

     void change_field(coordinates place, Organism *organism);
     Organism *check_organism(coordinates place);
     int can_spawn();
    virtual void log_organism();
    void output_organism(std::ofstream &out);
     coordinates choose_first_available();
    virtual void update_kill();
};