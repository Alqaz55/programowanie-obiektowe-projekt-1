#include "defines.hpp"
#include "Swiat.hpp"
#include "Organizm.hpp"
class Organizm;

Swiat::Swiat()
{
    {
        organisms = nullptr;
        added_organisms = nullptr;
        dead_organisms = nullptr;
        key = 0;

        for (int i = 0; i < WORLD_WIDTH; i++)
        {
            for (int j = 0; j < WORLD_HEIGHT; j++)
            {
                world[i][j].organisms = nullptr;
            }
        }
    }
}

Swiat::~Swiat()
{
    Organizm *current = organisms;
    while (current != nullptr)
    {
        Organizm *next = current->get_next();

        if (dead_organisms == nullptr)
        {
            dead_organisms = current;

            dead_organisms->set_previous(nullptr);
            dead_organisms->set_next(nullptr);
        }
        else
        {
            add_after_a(dead_organisms, current);
        }
        current = next;
    }
    current = added_organisms;
    while (current != nullptr)
    {
        Organizm *next = current->get_next();

        if (dead_organisms == nullptr)
        {
            dead_organisms = current;

            dead_organisms->set_previous(nullptr);
            dead_organisms->set_next(nullptr);
        }
        else
        {
            add_after_a(dead_organisms, current);
        }
        current = next;
    }
    organisms = nullptr;
    added_organisms = nullptr;
    delete_dead();
}

void Swiat::start_organisms(Organizm *a)
{
    organisms = a;

    organisms->set_previous(nullptr);
    organisms->set_next(nullptr);
}

void Swiat::add_after_a(Organizm *a, Organizm *nowa)
{
    if (nowa != nullptr)
    {
        if (a == nullptr)
        {
            start_organisms(nowa);
        }
        else
        {

            nowa->set_previous(a);
            nowa->set_next(a->get_next());
            if (a->get_next() != nullptr)
            {
                a->get_next()->set_previous(nowa);
            }
            a->set_next(nowa);
        }
    }
}

void Swiat::rechoose_square_after_a(Organizm *a)
{
    if (a != nullptr && a->get_next() != nullptr)
    {
        Organizm *being_rechoose_squared = a->get_next();
        Organizm *new_next = being_rechoose_squared->get_next();
        a->set_next(new_next);
        if (new_next != nullptr)
        {

            new_next->set_previous(a);
        }
        delete being_rechoose_squared;
    }
}

void Swiat::add_to_added(Organizm *nowy)
{
    if (added_organisms == nullptr)
    {
        added_organisms = nowy;

        added_organisms->set_previous(nullptr);
        added_organisms->set_next(nullptr);
    }
    else
    {
        add_after_a(added_organisms, nowy);
    }
}

void Swiat::add_to_organisms()
{
    Organizm *being_added = added_organisms;

    while (being_added != nullptr)
    {
        Organizm *next_added = being_added->get_next();
        being_added->set_previous(nullptr);
        being_added->set_next(nullptr);

        if (organisms == nullptr)
        {
            start_organisms(being_added);
        }
        else
        {
            Organizm *current = organisms;
            if (current->get_Initiative() < being_added->get_Initiative() || (current->get_Initiative() == being_added->get_Initiative() && current->get_Age() < being_added->get_Age()))
            {
                Organizm *old = organisms;
                start_organisms(being_added);
                add_after_a(being_added, old);
            }
            else
            {

                while (current->get_next() != nullptr && (current->get_next()->get_Initiative() > being_added->get_Initiative() ||
                                                          (current->get_next()->get_Initiative() == being_added->get_Initiative() &&
                                                           current->get_next()->get_Age() > being_added->get_Age())))
                {
                    current = current->get_next();
                }
                add_after_a(current, being_added);
            }
        }
        being_added = next_added;
    }
    added_organisms = nullptr;
}

void Swiat::delete_dead()
{
    Organizm *being_killed = dead_organisms;

    while (being_killed != nullptr)
    {
        Organizm *next_killed = being_killed->get_next();
        being_killed->set_previous(nullptr);
        being_killed->set_next(nullptr);

        delete being_killed;
        being_killed = next_killed;
    }
    dead_organisms = nullptr;
}

void Swiat::add_to_dead(Organizm *nowy)
{
    if (nowy->get_previous() != nullptr)
    {
        nowy->get_previous()->set_next(nowy->get_next());
    }
    if (nowy->get_next() != nullptr)
    {
        nowy->get_next()->set_previous(nowy->get_previous());
    }

    if (nowy == organisms)
    {
        organisms = nowy->get_next();
        if (organisms != nullptr)
            organisms->set_previous(nullptr);
    }
    if (nowy == added_organisms)
    {
        added_organisms = nowy->get_next();
        if (added_organisms != nullptr)

            added_organisms->set_previous(nullptr);
    }

    nowy->set_next(nullptr);
    nowy->set_previous(nullptr);

    if (dead_organisms == nullptr)
    {
        dead_organisms = nowy;
    }
    else
    {
        add_after_a(dead_organisms, nowy);
    }
    set_Pole(nowy->get_X(), nowy->get_Y(), nullptr);
}

void Swiat::remember_key(int key) { this->key = key; }

int Swiat::get_key() { return key; }

void Swiat::reset_turn()
{
    Organizm *current = organisms;
    while (current != nullptr)
    {
        current->reset_turn();
        current = current->get_next();
    }
}

void Swiat::draw_world()
{
    Organizm *current = organisms;
    while (current != nullptr)
    {
        current->draw();
        current = current->get_next();
    }
}

void Swiat::turn()
{
    debuguj << "NOWA TURA" << endl
            << endl
            << endl;

    Organizm *current = organisms;
    while (current != nullptr)
    {
        current->do_turn();
        debuguj << current->get_Draw() << "  x: " << current->get_X() << "  y: " << current->get_Y() << "  age: " << current->get_Age() << endl;
        current = current->get_next();
    }
   
    debuguj << endl;

    add_to_organisms();
}

pole *Swiat::get_Pole(int x, int y) { return &this->world[x][y]; }
void Swiat::set_Pole(int x, int y, Organizm *organism) { this->world[x][y].organisms = organism; }
