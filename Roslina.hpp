#pragma once
#include "Organizm.hpp"
#include "Zwierze.hpp"

class Roslina : public Organizm
{
private:
    int drawn;

protected:
    static int organism_number;

public:
    Roslina(int startX, int startY, Swiat *world);
    ~Roslina() override;

    virtual void plant();
    virtual void action();
    virtual int get_Color() const;

    void is_drawn();

    virtual void draw() override;
    void reset_turn() override;

    virtual void do_turn() override;
    virtual char get_draw() const override;
    virtual void create_offspring(int x, int y) override;
    virtual void stepped_on(Zwierze *opponent) override;
    void change_pole_of_type(int setx, int sety, Organizm *organism) override;
    Organizm *check_pole_of_type(int x, int y);
};