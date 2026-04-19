#pragma once
#include "Organism.hpp"
#include "Animal.hpp"




class Wolf : public Animal
{
private:

 

public:
    Wolf(int startX, int startY, World *world);
    Wolf(coordinates start_place, World *world);
    ~Wolf() override;

    char get_draw() const override;
    void create_offspring(coordinates place) override;
};