#pragma once
#include "Organism.hpp"
#include "Animal.hpp"

class Sheep : public Animal
{
private:
public:
    Sheep(int startX, int startY, World *world);
    Sheep(coordinates place, World *world);

    ~Sheep() override;

    char get_draw() const override;
    void create_offspring(coordinates place) override;
};