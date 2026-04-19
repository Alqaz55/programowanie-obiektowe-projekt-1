#include "Plant.hpp"

class Hogweed : public Plant
{
private:
public:
    Hogweed(int startx, int starty, World *startworld);
    Hogweed(coordinates new_place, World *startworld);

    ~Hogweed();

    void create_offspring(coordinates place) override;
    int get_color() const override;
    void do_effect(Organism *organism, Collision_effect &result) override;
    void action() override;
    virtual char get_draw() const override;
};
