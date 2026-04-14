#pragma once
#include "defines.hpp"
#include "Swiat.hpp"

class Roslina;
class Zwierze;

class Organizm
{
protected:
    int strength;
    int initiative;
    int x, y;
    int wiek;
    int did_turn;
    int alive;
    int drawn;
    typ type;
    Organizm *next_in_line;
    Organizm *previous;
    Swiat *world;
    int index;
    static int organizm_number;

public:
    Organizm();
    Organizm(int new_x, int new_y, Swiat *new_world);

    virtual ~Organizm();

    virtual int get_strength() const;
    virtual int get_Initiative() const;
    virtual int get_X() const;
    virtual int get_Y() const;
    virtual int get_age() const;
    virtual int get_drawn() const;
    int is_alive() const;

    virtual Organizm *get_next() const;
    virtual Organizm *get_previous() const;

    virtual void set_strength(int new_strength);
    virtual void set_initiave(int new_initiative);
    virtual void set_X(int new_x);
    virtual void set_Y(int new_y);
    virtual void set_age(int new_age);
    virtual void set_drawn(int new_drawn);

    typ get_type();
    virtual void set_next(Organizm *new_next);
    virtual void set_previous(Organizm *new_previous);

    virtual void choose_square(int &potential_x, int &potential_y);
    virtual void create_offspring(int potential_x, int potential_y) = 0;

    virtual char get_draw() const = 0;
    virtual void do_turn() = 0;
    virtual void draw() = 0;
    void death();
    virtual void reset_turn();
    virtual void stepped_on(Zwierze *organism) = 0;
    int get_index();


    virtual void change_pole_of_type(int x, int y, Organizm *organism) = 0;
    virtual Organizm *check_roslina(int x, int y);
    virtual Organizm *check_zwierze(int x, int y);
    virtual Organizm *check_pole_of_type(int x, int y)=0;
};