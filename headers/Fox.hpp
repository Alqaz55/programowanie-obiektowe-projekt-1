#pragma once
#include "Organism.hpp"
#include "Animal.hpp"




class Fox : public Animal
{
private:

 

public:
    Fox(int startX, int startY, World *world);
        Fox(coordinates stat_place, World *world);

    ~Fox() override;

    char get_draw() const override;
    void create_offspring(coordinates place) override;
    int attacker_avoids(int opponent_strength) override;
};