#pragma once
#include "Organizm.hpp"

class Czlowiek : public Organizm
{
    private:
    int kierunek;
    int remembered;
public:
    Czlowiek(int startX, int startY, Swiat* world);
    ~Czlowiek() override;

    void action() override;
    void collision(Organizm *organizm) override;
    char get_Char() const override;
    void move() override;
    void do_turn() override;
    int get_key();
    void breed() override;
};