#include "Plant.hpp"

class Nightshade : public Plant
{
private:
public:
    Nightshade(int startx, int starty, World *startworld);
    Nightshade(coordinates new_place, World *startworld);

    ~Nightshade();

    void create_offspring(coordinates place) override;
    int get_color() const override;
    void do_effect(Organism *organism, Collision_effect &result) override;
    virtual char get_draw() const override;
};
