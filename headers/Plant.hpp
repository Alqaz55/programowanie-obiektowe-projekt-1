#pragma once
#include "Organism.hpp"
#include "Animal.hpp"

class Plant : public Organism
{
private:
    int drawn;

protected:
    static int organism_number;

public:
    Plant(int startX, int startY, World *world);
    Plant(coordinates start_place, World *world);

    ~Plant() override;

    virtual void plant();
    virtual void action();
    virtual int get_color() const;

    void is_drawn();

    virtual void draw_on_coordinates(int x, int y);

    virtual void do_turn() override;
    virtual char get_draw() const override;
    virtual void create_offspring(coordinates place) override;
    void stepped_on(Animal *opponent, Collision_effect &result) override;
    virtual void do_effect(Organism *organism, Collision_effect &result);
    virtual void log_organism() override;
};