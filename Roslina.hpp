#pragma once
#include "Organizm.hpp"
#include "Zwierze.hpp"

class Roslina : public Organizm
{
private:
    int drawn;

public:
    Roslina(int startX, int startY, Swiat *world);
    ~Roslina() override;

    virtual void plant();
    virtual void action();
    void do_turn() override;
    virtual int get_Color() const = 0;
    virtual char get_Draw() const override;

    void is_drawn();

    void draw();
    //  virtual void do_Effect(Zwierze *opponent);

    virtual void stepped_on(Zwierze *opponent) override;
};