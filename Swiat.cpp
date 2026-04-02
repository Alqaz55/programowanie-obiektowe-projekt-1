
#include "Swiat.hpp"

void Swiat::add_after_a(Organizm *a, Organizm *nowa)
{
    Organizm *dodatkowy = a->get_next();
    a->set_next(nowa);
    nowa->set_next(dodatkowy);
}


Swiat::Swiat() {}
Swiat::~Swiat() {}

void Swiat::draw_world()
{
    Organizm *current = organisms;
    while (organisms != NULL)
    {
        organisms->draw();
    }
}


void Swiat::turn()
{
    Organizm *current = organisms;
    while (organisms != NULL)
    {
        organisms->do_turn();
    }
}

void Swiat::add_to_organisms()
{

    Organizm *added = this->added_organisms;
    Organizm *current;
    Organizm *next_added;
    
    while (added != NULL)
    {
        current = this->organisms;
        while (current->get_next() != NULL && added->get_Initiative() < current->get_next()->get_Initiative())
        {
            current = (current->get_next());
        }
        if (current->get_next() != NULL && added->get_Initiative() == current->get_next()->get_Initiative())
        {
            while (current->get_next() != NULL && added->get_Age() < current->get_next()->get_Age())
                current = (current->get_next());
        }
        next_added = added->get_next();
        add_after_a(current, added);
        added = next_added;
    }
}

void Swiat::remove_after_a(Organizm *a)
{
    if (a->get_next() != NULL)
    {

        Organizm *removed = a->get_next();
        a->set_next(removed->get_next());
        delete removed;
    }
}