#include "defines.hpp"
#include "Swiat.hpp"
#include "Organizm.hpp"
#include "Roslina.hpp"
#include "Zwierze.hpp"
class Organizm;

Swiat::Swiat()
{

    organisms = nullptr;
    added_organisms = nullptr;
    key = RESET_DIRECTION;

    debuguj << "wuw" << endl;
    for (int i = 0; i < WORLD_WIDTH; i++)
    {
        for (int j = 0; j < WORLD_HEIGHT; j++)
        {

            world[i][j].zwierze = nullptr;
            world[i][j].roslina = nullptr;
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

            world[i][j].zwierze = nullptr;
            world[i][j].roslina = nullptr;
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
        debuguj << being_added->get_draw() << being_added->get_index() << "         zastanawiam sie" << endl;

        being_added->set_previous(nullptr);
        being_added->set_next(nullptr);
        Organizm *square_occupied = nullptr;

        square_occupied = being_added->check_pole_of_type(being_added->get_X(), being_added->get_Y());

        if (being_added->get_X() < 0 || being_added->get_X() > WORLD_WIDTH || being_added->get_Y() < 0 || being_added->get_Y() > WORLD_HEIGHT)
        {
            debuguj << being_added->get_draw() << being_added->get_index() << " chcial byc poza mapa" << endl;
        }
        else if (square_occupied != nullptr && square_occupied != being_added)
        {
            debuguj << being_added->get_draw() << being_added->get_index() << " chcial byc na zajetym polu" << endl;
        }
        else
        {

            if (organisms == nullptr)
            {
                debuguj << "puste organizmy" << endl;
                start_organisms(being_added);
                being_added->change_pole_of_type(being_added->get_X(), being_added->get_Y(), being_added);
                debuguj << being_added->get_draw() << being_added->get_index() << "         dodany" << endl;
            }
            else
            {
                Organizm *current = organisms;
                if (current->get_Initiative() < being_added->get_Initiative() || (current->get_Initiative() == being_added->get_Initiative() && current->get_age() < being_added->get_age()))
                {
                    debuguj << "pierwszy" << endl;

                    Organizm *old = organisms;
                    organisms = being_added;
                    being_added->set_previous(nullptr);
                    being_added->set_next(old);
                    being_added->change_pole_of_type(being_added->get_X(), being_added->get_Y(), being_added);
                    debuguj << being_added->get_draw() << being_added->get_index() << "         dodany" << endl;
                }
                else
                {

                    while (current->get_next() != nullptr && (current->get_next()->get_Initiative() > being_added->get_Initiative() ||
                                                              (current->get_next()->get_Initiative() == being_added->get_Initiative() &&
                                                               current->get_next()->get_age() > being_added->get_age())))
                    {
                        current = current->get_next();
                    }
                    debuguj << "pozniej" << endl;

                    add_after_a(current, being_added);
                    being_added->change_pole_of_type(being_added->get_X(), being_added->get_Y(), being_added);
                    debuguj << being_added->get_draw() << being_added->get_index() << "         dodany" << endl;
                }
            }
        }

        being_added = next_added;

        // Organizm *help = organisms;
        // debuguj << endl
        //         << endl
        //         << " DODAWANE" << endl;
        // while (help != nullptr)
        // {
        //     if (help->is_alive())
        //     {

        //         debuguj << help->get_draw() << help->get_index() << "  x: " << help->get_X() << "  y: " << help->get_Y() << "  age: " << help->get_age() << endl;
        //     }
        //     help = help->get_next();
        // }
        // debuguj << endl
        //         << endl;
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

            current->change_pole_of_type(current->get_X(), current->get_Y(), nullptr);

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
        if (current->is_alive() && !current->get_drawn())
        {
            current->draw();
            current->set_drawn(1);
        }
        current = current->get_next();
    }
    Organizm *reset_current = organisms;
    while (reset_current != nullptr)
    {
        if (reset_current->is_alive())
        {

            reset_current->set_drawn(0);
        }
        reset_current = reset_current->get_next();
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
            if (dynamic_cast<Zwierze *>(current))
                debuguj << current->get_draw() << current->get_index() << "  x: " << current->get_X() << "  y: " << current->get_Y() << "  age: " << current->get_age() << endl;
        }
        current = current->get_next();
    }

    debuguj << endl;

    add_to_organisms();
    delete_dead();
    reset_turn();
}

pole *Swiat::get_pole(int x, int y) { return &this->world[x][y]; }

void Swiat::set_pole(int x, int y, Roslina *plant, Zwierze *animal)
{
    world[x][y].roslina = plant;
    world[x][y].zwierze = animal;
}

void Swiat::set_pole_roslina(int x, int y, Roslina *plant)
{
    world[x][y].roslina = plant;
}
void Swiat::set_pole_zwierze(int x, int y, Zwierze *animal)
{
    world[x][y].zwierze = animal;
}

void Swiat::delete_list(Organizm *&head)
{
    Organizm *being_killed = head;

    while (being_killed != nullptr)
    {
        Organizm *next_killed = being_killed->get_next();
        set_pole(being_killed->get_X(), being_killed->get_Y(), nullptr, nullptr);
        being_killed->set_previous(nullptr);
        being_killed->set_next(nullptr);

        delete being_killed;
        being_killed = next_killed;
    }
    head = nullptr;
}