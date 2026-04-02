#pragma once
#include "defines.hpp"

class Organizm
{
protected:
    int strength;
    int initiative;
    int x, y;
    int wiek;
    typ typ_organizmu;
    Organizm *next_in_line;

public:
    Organizm();
    virtual ~Organizm();

    virtual int get_Strength() const;
    virtual int get_Initiative() const;
    virtual int get_X() const;
    virtual int get_Y() const;
    virtual int get_Age() const;

    virtual Organizm *get_next() const;

    virtual void set_Strength(int new_strength);
    virtual void set_Initiative(int new_initiative);
    virtual void set_X(int new_x);
    virtual void set_Y(int new_y);
    virtual void set_Age();

    virtual void set_next(Organizm *next);

    virtual void do_turn() = 0;
    virtual void action() = 0;
    virtual void collision(Organizm *organizm) = 0;
    virtual void draw() = 0;
    virtual void move() = 0;
};