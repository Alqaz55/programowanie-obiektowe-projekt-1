#pragma once
#include "../Organizm.hpp"

class Wilk : public Organizm
{
    private:
    int kierunek;
    int remembered;
public:
    Wilk(int startX, int startY);
    ~Wilk() override;

    void action() override;
    void collision(Organizm *organizm) override;
    void draw() override;
    void move() override;
    void do_turn() override;
    void remember_key(int key);
    int get_key();
};