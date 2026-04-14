#include "Czlowiek.hpp"
#include "Swiat.hpp"
#include "Wilk.hpp"

// Konstruktor
Czlowiek::Czlowiek(int startX, int startY, Swiat *world)
    : Zwierze(startX, startY, world)
{
    strength = CZLOWIEK_STRENGTH;
    initiative = CZLOWIEK_INITIATIVE;
    active_skill = 0;
    cooldown = 0;
    debuguj << "cndkjsfhni" << endl;
}

Czlowiek::~Czlowiek()
{
}

void Czlowiek::create_offspring(int x, int y) {}

char Czlowiek::get_draw() const
{
    return CZLOWIEK_CHAR;
}

void Czlowiek::choose_square(int &potential_x, int &potential_y)
{

    int dx = 0;
    int dy = 0;

    switch (world->get_key())
    {
    case KEY_UP:
        dy = UP;
        break;
    case KEY_DOWN:
        dy = DOWN;
        break;
    case KEY_LEFT:
        dx = LEFT;
        break;
    case KEY_RIGHT:
        dx = RIGHT;
        break;

    default:
        break;
    }

    if (!dx && !dy)
    {

        return;
    }
    if (x + dx >= 0 && x + dx < WORLD_WIDTH)
    {
        potential_x = x + dx;
    }
    else
    {
        potential_x = x;
    }
    if (y + dy >= 0 && y + dy < WORLD_HEIGHT)
    {
        potential_y = y + dy;
    }
    else
    {
        potential_y = y;
    }
}

void Czlowiek::action()
{

    if (world->get_key() == RESET_DIRECTION)
    {
        debuguj << get_draw() << "   Nie idzie z x:" << x << "y:" << y << endl;
        return;
    }
    debuguj << get_draw() << "    idzie z x:" << x << "y:" << y << endl;
    int potential_x, potential_y;

    choose_square(potential_x, potential_y);
    if (potential_x == x && potential_y == y)
    {
        return;
    }

    pole *square = world->get_pole(potential_x, potential_y);
    if (square->zwierze == NULL || square->zwierze == this)
    {

        world->set_pole_zwierze(x, y, nullptr);
        x = potential_x;
        y = potential_y;
        world->set_pole_zwierze(x, y, this);
    }
    else
    {

        debuguj << get_draw() << " kolizja z " << square->zwierze->get_draw() << "x:" << square->zwierze->get_X() << " y:" << square->zwierze->get_Y() << endl;
        square->zwierze->stepped_on(this);
    }
    if (square->roslina != nullptr)
    {
        square->roslina->stepped_on(this);
    }
}

void Czlowiek::do_turn()
{

    wiek++;
    did_turn = 1;
    if (world->get_key() == 'a')
    {

        if (!active_skill && !cooldown)

        {
            active_skill = 3;
            use_skill();
        }
    }
    else
    {
        action();
        if (active_skill > 0)
        {
            use_skill();
            active_skill--;
            if (active_skill == 0)
            {
                cooldown = 3;
            }
        }
        if (cooldown > 0)
        {
            cooldown--;
        }
    }
    debuguj << "skill:    " << active_skill << "cooldown:  " << cooldown << endl;
}

void Czlowiek::use_skill()
{

    for (int i = 0; i < 9; i++)
    {
        int current_x = x + i / 3 - 1;
        int current_y = y + i % 3 - 1;

        if (current_x < 0 || current_x >= WORLD_WIDTH ||
            current_y < 0 || current_y >= WORLD_HEIGHT)
            continue;

        if (current_x == x && current_y == y)
            continue;

        pole *p = world->get_pole(current_x, current_y);
        if (!p)
            continue;

        Zwierze *animal = p->zwierze;
        Roslina *plant = p->roslina;

        if (animal != nullptr)
        {
            debuguj << animal->get_draw() << "          smierc skillem" << endl;
            animal->death();
        }
        if (plant != nullptr)
        {
            debuguj << plant->get_draw() << "          smierc skillem" << endl;
            plant->death();
        }
    }
}
void Czlowiek::draw()
{
    char symbol = get_draw();
    Roslina *plant = world->get_pole(x, y)->roslina;
    if (plant == nullptr)
    {

        attron(COLOR_PAIR(KOLOR_MLECZY));
        mvaddch(y + 1, x + 1, symbol);
        attroff(COLOR_PAIR(KOLOR_MLECZY));
    }
    else
    {
        attron(COLOR_PAIR(plant->get_Color()));
        mvaddch(y + 1, x + 1, symbol);
        attroff(COLOR_PAIR(plant->get_Color()));
        plant->set_drawn(1);
    }
}
