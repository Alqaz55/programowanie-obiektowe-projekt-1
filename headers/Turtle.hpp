#pragma once
#include "Organism.hpp"
#include "Animal.hpp"




class Turtle : public Animal
{
private:

 

public:
    Turtle(int startX, int startY, World *world);
    Turtle(coordinates start_place, World *world);
    ~Turtle() override;

    int opponent_dodges(int strength) override;
    char get_draw() const override;
    void create_offspring(coordinates place) override;
    coordinates choose_movement() override;
};