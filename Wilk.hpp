#pragma once
#include "Organizm.hpp"



class Wilk : public Organizm
{
private:

    int kierunek;
    int remembered;

public:
    Wilk(int startX, int startY, Swiat *world);
    ~Wilk() override;

    void action() override;

    void do_turn() override;
    
    void collision(Organizm *organizm) override;
    void move() override;
    void breed() override;


    char get_Char() const override;
};