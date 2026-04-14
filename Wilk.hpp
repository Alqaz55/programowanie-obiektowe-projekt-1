#pragma once
#include "Organizm.hpp"
#include "Zwierze.hpp"




class Wilk : public Zwierze
{
private:

 

public:
    Wilk(int startX, int startY, Swiat *world);
    ~Wilk() override;

    char get_draw() const override;
    void create_offspring(int potential_x, int potential_y) override;
};