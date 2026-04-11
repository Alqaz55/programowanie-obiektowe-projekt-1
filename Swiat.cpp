#include "defines.hpp"
#include "Swiat.hpp"
#include "Organizm.hpp"
class Organizm;

Swiat::Swiat()
{

    organisms = nullptr;
    added_organisms = nullptr;
    key = 0;

    for (int i = 0; i < WORLD_WIDTH; i++)
    {
        for (int j = 0; j < WORLD_HEIGHT; j++)
        {
            world[i][j].organisms = nullptr;
        }
    }
}

Swiat::~Swiat()
{
    delete_list(organisms);
    delete_list(added_organisms);
    for (int i = 0; i < WORLD_WIDTH; i++)
    {
        for (int j = 0; j < WORLD_HEIGHT; j++)
        {
            world[i][j].organisms = nullptr;
        }
    }
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

void Swiat::remove_after_a(Organizm *a)
{
    if (a != nullptr && a->get_next() != nullptr)
    {
        Organizm *being_removed = a->get_next();
        Organizm *new_next = being_removed->get_next();
        a->set_next(new_next);
        if (new_next != nullptr)
        {

            new_next->set_previous(a);
        }
        delete being_removed;
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
            this->set_Pole(being_added->get_X(), being_added->get_Y(), being_added);
        }
        else
        {
            Organizm *current = organisms;
            if (current->get_Initiative() < being_added->get_Initiative() || (current->get_Initiative() == being_added->get_Initiative() && current->get_Age() < being_added->get_Age()))
            {
                Organizm *old = organisms;
                start_organisms(being_added);
                add_after_a(being_added, old);
                this->set_Pole(being_added->get_X(), being_added->get_Y(), being_added);
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
                this->set_Pole(being_added->get_X(), being_added->get_Y(), being_added);
            }
        }
        being_added = next_added;
    }
    added_organisms = nullptr;
}
void Swiat::delete_dead()
{
    Organizm *current = organisms;

    while (current != nullptr)
    {
        Organizm *next = current->get_next();

        if (!current->is_alive())
        {
            Organizm *prev = current->get_previous();

            set_Pole(current->get_X(), current->get_Y(), nullptr);

            if (prev != nullptr)
                prev->set_next(next);
            else
                organisms = next;

            if (next != nullptr)
                next->set_previous(prev);

            delete current;
        }

        current = next;
    }
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
        if (current->is_alive())
        {

            current->draw();
        }
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
        if (current->is_alive())
        {

            current->do_turn();
            debuguj << current->get_Draw() << "  x: " << current->get_X() << "  y: " << current->get_Y() << "  age: " << current->get_Age() << endl;
        }
        current = current->get_next();
    }

    debuguj << endl;

    add_to_organisms();
    delete_dead();
    reset_turn();
}

pole *Swiat::get_Pole(int x, int y) { return &this->world[x][y]; }
void Swiat::set_Pole(int x, int y, Organizm *organism) { this->world[x][y].organisms = organism; }

void Swiat::delete_list(Organizm *&head)
{
    Organizm *being_killed = head;

    while (being_killed != nullptr)
    {
        Organizm *next_killed = being_killed->get_next();
        set_Pole(being_killed->get_X(), being_killed->get_Y(), nullptr);
        being_killed->set_previous(nullptr);
        being_killed->set_next(nullptr);

        delete being_killed;
        being_killed = next_killed;
    }
    head = nullptr;
}