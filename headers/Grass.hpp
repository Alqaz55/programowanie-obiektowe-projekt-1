#include "Plant.hpp"

class Grass : public Plant
{
private:
public:
    Grass(int startx, int starty, World *startworld);
    Grass(coordinates start_place, World *startworld);

    ~Grass();

    void create_offspring(coordinates place) override;
    int get_color() const override;
    virtual char get_draw() const override;
};
