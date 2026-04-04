
#include "Swiat.hpp"
#include "Organizm.hpp"

void Swiat::add_after_a(Organizm *a, Organizm *nowa)
{
    Organizm *dodatkowy = a->get_next();
    a->set_next(nowa);
    nowa->set_next(dodatkowy);
}

Swiat::Swiat()
{
    organisms = nullptr;
    added_organisms = nullptr;

    for (int i = 0; i < WORLD_WIDTH; i++)
    {
        for (int j = 0; j < WORLD_HEIGHT; j++)
        {
            world[i][j].organisms = nullptr;
        }
    }
}
Swiat::~Swiat() {}

void Swiat::draw_world()
{
    Organizm *current = organisms;
    while (current != NULL)
    {
        current->draw();
        current = current->get_next();
    }
}

 int Swiat::get_key(){ return key;}

void Swiat::turn()
{
    Organizm *current = organisms;
    while (current != NULL)
    {
        current->do_turn();
        current = current->get_next();
    }
}

void Swiat::add_to_organisms()
{

    Organizm *added = this->added_organisms;
    Organizm *current;
    Organizm *next_added;

    while (added != NULL)
    {
        next_added = added->get_next();
        if (this->organisms != NULL)
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
            add_after_a(current, added);
        }
        else
        {
            this->organisms = added;
            added->set_next(NULL);
        }
        added = next_added;

    }
}

void Swiat::remove_after_a(Organizm *a)
{
    if (a != NULL && a->get_next() != NULL)
    {

        Organizm *removed = a->get_next();
        a->set_next(removed->get_next());
        delete removed;
    }
}

void Swiat::add_to_added(Organizm *nowy)
{
    if (added_organisms == nullptr) {
        // lista pusta – nowy staje się head
        added_organisms = nowy;
        nowy->set_next(nullptr);
    } else {
        // idziemy na koniec listy
        Organizm *current = added_organisms;
        while (current->get_next() != nullptr) {
            current = current->get_next();
        }
        current->set_next(nowy);
        nowy->set_next(nullptr);
    }
}

pole *Swiat::get_Pole(int x, int y)
{
    return &this->world[x][y];
}
void Swiat::set_Pole(int x, int y, Organizm *organism)
{
    this->world[x][y].organisms = organism;
}


void Swiat::remember_key(int key) { this->key = key; }