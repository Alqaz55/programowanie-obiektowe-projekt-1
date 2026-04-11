#pragma once
#include "Organizm.hpp"
#include "Roslina.hpp"

class Zwierze : public Organizm
{
private:
public:
    Zwierze(int startX, int startY, Swiat *world);
    ~Zwierze() override;

    virtual void collision(Zwierze *organizm);

    virtual void breed();
    virtual void attack(Zwierze *Organizm);
    virtual void action();
    virtual char get_Draw() const = 0;
    virtual void draw();
    void stepped_on(Zwierze *opponent) override;
    virtual void eat(Roslina *opponent);

    virtual int attacker_avoids(int strength);
    virtual int opponent_dodges(int strength);
    void do_turn() override;
};