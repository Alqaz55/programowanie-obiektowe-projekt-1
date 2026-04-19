#include "Plant.hpp"

class Dandelion : public Plant
{
private:
public:
    Dandelion(int startx, int starty, World *startworld);
    Dandelion(coordinates start_place, World *startworld);

    ~Dandelion();

    void create_offspring(coordinates place) override;
    int get_color() const override;
    virtual char get_draw() const override;
    void do_turn() override;
};
