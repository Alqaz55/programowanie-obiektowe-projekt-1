#pragma once
#include "defines.hpp"
#include "Swiat.hpp"

class Organizm
{
protected:
    int strength;
    int initiative;
    int x, y;
    int wiek;
    int did_turn;
    typ typ_organizmu;
    Organizm *next_in_line;
    Organizm *previous;
    Swiat *world;

public:
    Organizm();
    Organizm(int new_x, int new_y, Swiat* new_wordl);

    virtual ~Organizm();

    virtual int get_Strength() const;
    virtual int get_Initiative() const;
    virtual int get_X() const;
    virtual int get_Y() const;
    virtual int get_Age() const;
    virtual char get_Char() const = 0;

    virtual Organizm *get_next() const;
    virtual Organizm *get_previous() const;

    virtual void set_Strength(int new_strength);
    virtual void set_Initiative(int new_initiative);
    virtual void set_X(int new_x);
    virtual void set_Y(int new_y);
    virtual void set_Age(int new_age);

    virtual void set_next(Organizm *new_next);
    virtual void set_previous(Organizm *new_previous);

    virtual void do_turn() = 0;
    virtual void action() = 0;
    virtual void collision(Organizm *organizm) = 0;
    void draw();
    virtual void move() = 0;
    void death();
    void reset_turn();
    virtual void breed() = 0;
    ;
};