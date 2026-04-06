#include "Roslina.hpp"


class Trawa : public Roslina
{
private:
public:
    Trawa(int startx, int starty, Swiat* startworld);
    ~Trawa();


    void create_offspring(int potential_x, int potential_y) override;
    int get_Color() const override;
};

