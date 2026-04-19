#pragma once
#include "Organism.hpp"
#include "Animal.hpp"

class Antelope : public Animal
{
private:
public:
    Antelope(int startX, int startY, World *world);
    Antelope(coordinates start_place, World *world);

    ~Antelope() override;

    char get_draw() const override;
    void create_offspring(coordinates place) override;
    coordinates choose_movement() override;
    int opponent_dodges(int strength) override;
};