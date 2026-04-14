#pragma once
#include "Organizm.hpp"
#include "Roslina.hpp"

class Zwierze : public Organizm
{
private:
protected:
static int organism_number;
public:
    Zwierze(int startX, int startY, Swiat *world);
    ~Zwierze() override;

    virtual void collision(Zwierze *organizm);

    virtual void breed();
    virtual void attack(Zwierze *Organizm);
    virtual void action();
    virtual char get_draw() const;
    virtual void draw();
    void stepped_on(Zwierze *opponent) override;
    virtual void eat(Roslina *opponent);

    virtual int attacker_avoids(int strength);
    virtual int opponent_dodges(int strength);
    void do_turn() override;
    void change_pole_of_type(int setx, int sety, Organizm *organism) override;
    Organizm *check_pole_of_type(int x, int y);
};