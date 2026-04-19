#pragma once
#include "Organism.hpp"
#include "Plant.hpp"

class Animal : public Organism
{
private:
protected:
    static int organism_number;

public:
    Animal(int startX, int startY, World *world);
    Animal(coordinates start_place, World *world);

    ~Animal() override;

    virtual void collision(Animal *Organism, Collision_effect &result);

    virtual void breed(Collision_effect &result);
    virtual void attack(Animal *Organism, Collision_effect &result);
    virtual void action();
    virtual char get_draw() const;
    virtual void draw_on_coordinates(int x, int y);
    void stepped_on(Animal *opponent, Collision_effect &result) override;
    virtual void eat(Plant *opponent, Collision_effect &result);
    virtual coordinates choose_movement();

    virtual int attacker_avoids(int strength);
    virtual int opponent_dodges(int strength);
    void do_turn() override;
};