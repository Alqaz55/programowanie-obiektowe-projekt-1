#pragma once
#include "Organizm.hpp"
#include "Zwierze.hpp"

class Czlowiek : public Zwierze
{
private:
int active_skill;
int cooldown;

public:
    Czlowiek(int startX, int startY, Swiat *world);
    ~Czlowiek() override;

    void choose_square(int& potential_x, int& potential_y) override;
    char get_Draw() const override;
    int get_key();
    void create_offspring(int x, int y) override;
    void do_turn() override;
    void action() override;
    void use_skill();
    void draw() override;

};
