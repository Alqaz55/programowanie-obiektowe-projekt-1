#pragma once
#include "Organism.hpp"
#include "Animal.hpp"

class Human : public Animal
{
private:
    int active_skill;
    int cooldown;
    int kill_count;
    string collision_message;

public:
    Human(int startX, int startY, World *world);
    Human(coordinates start_place, World *world);

    ~Human() override;

    coordinates choose_movement() override;

    char get_draw() const override;
    int get_key();
    int get_cooldown();
    void death() override;
    int get_skill();
     void collision(Animal *Organism, Collision_effect &result) override;
    void create_offspring(coordinates place) override;
    void do_turn() override;
    void use_skill();
    int get_kill_count();
    virtual void update_kill();
    string get_collision_message();
    void set_collision_message(string new_message);
};
