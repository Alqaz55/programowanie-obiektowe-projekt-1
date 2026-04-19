#include "Plant.hpp"

class Guarana : public Plant
{
private:
public:
    Guarana(int startx, int starty, World *startworld);
    Guarana(coordinates new_place, World *startworld);

    ~Guarana();

    void create_offspring(coordinates place) override;
    int get_color() const override;
    void do_effect(Organism *organism, Collision_effect &result) override;
    virtual char get_draw() const override;
};
