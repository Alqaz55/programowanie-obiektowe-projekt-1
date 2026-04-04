#pragma once
#include "../Organizm.hpp"

class Wilk : public Organizm
{
    private:
    int kierunek;
    int remembered;
public:
    Wilk(int startX, int startY, Swiat* world);
    ~Wilk() override;

    void action() override;
    void collision(Organizm *organizm) override;
    char get_Char() const override;
    void move() override;
    void do_turn() override;
    void remember_key(int key);
    int get_key();
};