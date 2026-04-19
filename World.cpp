#include "headers/defines.hpp"
#include "headers/World.hpp"
#include "headers/Organism.hpp"
#include "headers/Plant.hpp"
#include "headers/Animal.hpp"
#include "headers/Wolf.hpp"
#include "headers/Human.hpp"
#include "headers/Grass.hpp"
#include "headers/Fox.hpp"
#include "headers/Antelope.hpp"
#include "headers/Turtle.hpp"
#include "headers/Guarana.hpp"
#include "headers/Sheep.hpp"
#include "headers/Nightshade.hpp"
#include "headers/Hogweed.hpp"
#include "headers/Dandelion.hpp"

class Organism;

World::World(int height, int width)
{

    srand(time(NULL));
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();

    init_pair(GRASS_COLOR, COLOR_BLACK, COLOR_GREEN);
    init_pair(DANDELION_COLOR, COLOR_CYAN, COLOR_YELLOW);
    init_pair(GUARANA_COLOR, COLOR_CYAN, COLOR_RED);
    init_pair(HOGWEED_COLOR, COLOR_CYAN, COLOR_CYAN);
    init_pair(NIGHTSHADE_COLOR, COLOR_CYAN, COLOR_WHITE);
    init_pair(BORDER_COLOR, COLOR_MAGENTA, COLOR_CYAN);

    organisms = nullptr;
    added_organisms = nullptr;
    key = RESET_DIRECTION;

    world_height = height;
    world_width = width;
    world = new field[world_height * world_width];
    coordinates current;
    for (int i = 0; i < world_width; i++)
    {
        current.x = i;
        for (int j = 0; j < world_height; j++)
        {
            current.y = j;
            set_field(current, nullptr);
        }
    }

    log_data.width = LOG_WIDTH;
    log_data.height = LOG_HEIGHT;
}

World::~World()
{
    delete_list(organisms);
    delete_list(added_organisms);

    coordinates current;
    for (int i = 0; i < world_width; i++)
    {
        current.x = i;
        for (int j = 0; j < world_height; j++)
        {
            current.y = j;
            set_field(current, nullptr);
        }
    }
    delete[] world;
}

void World::add_after_a(Organism *a, Organism *new_organism)
{
    if (new_organism != nullptr)
    {
        if (a == nullptr)
        {
            return;
        }
        else
        {

            new_organism->set_previous(a);
            new_organism->set_next(a->get_next());
            if (a->get_next() != nullptr)
            {
                a->get_next()->set_previous(new_organism);
            }
            a->set_next(new_organism);
        }
    }
}

void World::add_to_added(Organism *new_organism)
{
    if (added_organisms == nullptr)
    {
        added_organisms = new_organism;

        added_organisms->set_previous(nullptr);
        added_organisms->set_next(nullptr);
    }
    else
    {
        add_after_a(added_organisms, new_organism);
    }
}

void World::add_to_organisms()
{
    Organism *being_added = added_organisms;

    while (being_added != nullptr)
    {
        Organism *next_added = being_added->get_next();
        debug_file << being_added->get_draw() << being_added->get_index() << "         considers" << endl;

        being_added->set_previous(nullptr);
        being_added->set_next(nullptr);

        coordinates square = being_added->get_field();

        if (!is_in_bounds(square))
        {
            debug_file << being_added->get_draw() << being_added->get_index() << " wanted to be outside the map" << endl;
            delete being_added;
            being_added = next_added;

            continue;
        }
        if (!being_added->can_spawn())
        {
            debug_file << being_added->get_draw() << being_added->get_index() << " wanted to be on an occupied square" << endl;
            delete being_added;
            being_added = next_added;

            continue;
        }

        if (organisms == nullptr)
        {
            debug_file << "puste Organismy" << endl;
            organisms = being_added;
            debug_file << being_added->get_draw() << being_added->get_index() << "         is added" << endl;
        }
        else
        {
            Organism *current = organisms;
            if (organism_comes_before(being_added, current))
            {

                Organism *old = organisms;
                being_added->set_next(current);
                current->set_previous(being_added);
                organisms = being_added;
                if (old != nullptr)
                {
                    old->set_previous(being_added);
                }
                debug_file << being_added->get_draw() << being_added->get_index() << "         is added" << endl;
            }
            else
            {

                while (current->get_next() != nullptr && organism_comes_before(current->get_next(), being_added))
                {
                    current = current->get_next();
                }

                Organism *next = current->get_next();

                being_added->set_next(next);
                being_added->set_previous(current);
                current->set_next(being_added);

                if (next != nullptr)
                {
                    next->set_previous(being_added);
                }
                debug_file << being_added->get_draw() << being_added->get_index() << "         is added" << endl;
            }
        }

        being_added->change_field(square, being_added);

        being_added = next_added;
    }
    added_organisms = nullptr;
}

void World::delete_dead()
{
    Organism *current = organisms;

    while (current != nullptr)
    {
        Organism *next = current->get_next();

        if (!current->is_alive())
        {
            Organism *prev = current->get_previous();
            coordinates pos = current->get_field();

            if (is_in_bounds(pos))
            {
                if (get_field(pos)->organism == current)
                {
                    set_field(pos, nullptr);
                }
            }

            if (prev == nullptr)
            {
                organisms = next;
                if (organisms != nullptr)
                    organisms->set_previous(nullptr);
            }
            else
            {
                prev->set_next(next);
            }

            if (next != nullptr)
                next->set_previous(prev);

            current->set_next(nullptr);
            current->set_previous(nullptr);

            delete current;
        }

        current = next;
    }
}
void World::remember_key(int key) { this->key = key; }

int World::get_key() { return key; }

void World::reset_turn()
{
    Organism *current = organisms;
    while (current != nullptr)
    {
        current->reset_turn();
        current = current->get_next();
    }
}

void World::turn()
{
    debug_file << endl
               << endl
               << "NEW TURN:    " << turn_number++ << endl
               << endl
               << endl;

    Organism *current = organisms;
    if (current == nullptr)
    {
        return;
    }
    Organism *next;
    while (current != nullptr)
    {
        next = current->get_next();

        if (current->is_alive())
        {
            current->do_turn();
            if (dynamic_cast<Animal *>(current))
                debug_file << current->get_draw() << current->get_index() << "  x: " << current->get_x() << "  y: " << current->get_y() << "  age: " << current->get_age() << endl;
        }
        current = next;
    }

    debug_file << endl;

    add_to_organisms();

    current = organisms;
    next = current->get_next();

    while (current != nullptr)
    {
        next = current->get_next();

        current->log_organism();
        current = next;
    }
    delete_dead();
    reset_turn();

    debug_file << endl
               << endl;

    current = organisms;
    next = current->get_next();

    while (current != nullptr)
    {
        next = current->get_next();

        current->log_organism();
        current = next;
    }
}

field *World::get_field(coordinates place) { return &this->world[place.x + world_width * place.y]; }

void World::set_field(coordinates place, Organism *organism)
{
    if (is_in_bounds(place))
    {

        world[world_width * place.y + place.x].organism = organism;
    }
}

void World::delete_list(Organism *&head)
{
    Organism *being_killed = head;

    while (being_killed != nullptr)
    {
        Organism *next_killed = being_killed->get_next();
        set_field(being_killed->get_field(), nullptr);
        being_killed->set_previous(nullptr);
        being_killed->set_next(nullptr);

        delete being_killed;
        being_killed = next_killed;
    }
    head = nullptr;
}
void World::draw_map()
{
    coordinates current;
    draw_frame(world_width, world_height, 0, 0);

    for (int y = 0; y < world_height; y++)
    {
        current.y = y;
        for (int x = 0; x < world_width; x++)
        {
            current.x = x;
            Organism *animal = get_field(current)->organism;
            if (animal != nullptr)
            {
                animal->draw_on_coordinates(x, y);
            }
            else
            {
                mvaddch(y + BORDER, x + BORDER, ' ');
            }
        }
    }
    draw_log();
}

int World::organism_comes_before(Organism *organism, Organism *checked)
{
    if (organism->get_initiative() != checked->get_initiative())
        return organism->get_initiative() > checked->get_initiative();

    if (organism->get_age() != checked->get_age())
        return organism->get_age() > checked->get_age();

    return organism->get_index() < checked->get_index();
}

int World::get_height()
{
    return world_height;
}

int World::get_width()
{
    return world_width;
}

int World::turn_number = 1;

int World::is_in_bounds(coordinates place)
{
    return (place.x >= 0 && place.x < world_width && place.y >= 0 && place.y < world_height);
}

void World::start_game()
{

    Human *player = new Human(rand() % world_width, rand() % world_height, this);
    update_log_data(player);
    add_to_added(player);
    int randomizer = 1 + rand() % 3;
    while (randomizer--)
    {
        Organism *new_organism =
            new Wolf(rand() % world_width, rand() % world_height, this);
        add_to_added(new_organism);
    }

    randomizer = 1 + rand() % 3;
    while (randomizer--)
    {
        Organism *new_organism =
            new Sheep(rand() % world_width, rand() % world_height, this);
        add_to_added(new_organism);
    }

    randomizer = 1 + rand() % 3;
    while (randomizer--)
    {
        Organism *new_organism =
            new Fox(rand() % world_width, rand() % world_height, this);
        add_to_added(new_organism);
    }

    randomizer = 1 + rand() % 10;
    while (randomizer--)
    {
        Organism *new_organism =
            new Antelope(rand() % world_width, rand() % world_height, this);
        add_to_added(new_organism);
    }

    randomizer = 1 + rand() % 3;
    while (randomizer--)
    {
        Organism *new_organism =
            new Turtle(rand() % world_width, rand() % world_height, this);
        add_to_added(new_organism);
    }

    randomizer = 1 + rand() % 3;
    while (randomizer--)
    {
        Organism *new_organism =
            new Grass(rand() % world_width, rand() % world_height, this);
        add_to_added(new_organism);
    }

    randomizer = 1 + rand() % 4;
    while (randomizer--)
    {
        Organism *new_organism =
            new Dandelion(rand() % world_width, rand() % world_height, this);
        add_to_added(new_organism);
    }

    randomizer = 1 + rand() % 3;
    while (randomizer--)
    {
        Organism *new_organism =
            new Guarana(rand() % world_width, rand() % world_height, this);
        add_to_added(new_organism);
    }

    randomizer = 1 + rand() % 3;
    while (randomizer--)
    {
        Organism *new_organism =
            new Nightshade(rand() % world_width, rand() % world_height, this);
        add_to_added(new_organism);
    }

    randomizer = 1 + rand() % 3;
    while (randomizer--)
    {
        Organism *new_organism =
            new Hogweed(rand() % world_width, rand() % world_height, this);
        add_to_added(new_organism);
    }

    add_to_organisms();
}

void World::log_map()
{
    coordinates current;
    for (int y = 0; y < world_height; y++)
    {
        current.y = y;
        for (int x = 0; x < world_width; x++)
        {
            current.x = x;
            Organism *animal = get_field(current)->organism;
            if (animal != nullptr)
            {
                log_map_file << animal->get_draw();
            }
            else
            {
                log_map_file << ".";
            }
        }
        log_map_file << endl;
    }
    log_map_file << endl;
    log_map_file << endl;
    log_map_file << endl;
}

void World::save_to_file(std::ofstream &out)
{
    Organism *current = organisms;

    out << "world_width  " << world_width << " world_height " << world_height << '\n';

    while (current != nullptr)
    {
        Organism *next = current->get_next();
        current->output_organism(out);
        current = next;
    }
    out << endl;
}

int World::load_from_file(std::istream &in)
{

    string buffer;
    Organism *organism;
    char symbol;
    int new_world_width, new_world_height, new_strength, new_initiative, new_age, new_x, new_y;
    in >> buffer >> new_world_width >> buffer >> new_world_height;
    world_height = new_world_height;
    world_width = new_world_width;

    if (new_world_height <= MAX_WORLD_HEIGHT && new_world_height > 0 && new_world_width <= MAX_WORLD_WIDTH && new_world_width > 0)
    {

        debug_file << "trying to load" << endl;

        while (in >> symbol >> new_initiative >> new_strength >> new_age >> new_x >> new_y)
        {

            organism = create_from_symbol(symbol, new_x, new_y);

            if (!organism)
            {
                debug_file << "No such organism: " << symbol << endl;
                continue;
            }
            organism->set_strength(new_strength);
            organism->set_age(new_age);
            if (symbol == 'C')
            {
                update_log_data(dynamic_cast<Human *>(organism));
            }
            add_to_added(organism);
        }
        debug_file << "successfull load" << endl;

        add_to_organisms();
        return 1;
    }
    else
    {
        debug_file << "unsuccessfull";
        return 0;
    }
}

Organism *World::create_from_symbol(char c, int new_x, int new_y)
{
    coordinates place;
    place.x = new_x;
    place.y = new_y;
    switch (c)
    {
    case HUMAN_CHAR:
        return new Human(place, this);
    case WOLF_CHAR:
        return new Wolf(place, this);
    case SHEEP_CHAR:
        return new Sheep(place, this);
    case FOX_CHAR:
        return new Fox(place, this);
    case TURTLE_CHAR:
        return new Turtle(place, this);
    case ANTELOPE_CHAR:
        return new Antelope(place, this);

    case GRASS_CHAR:
        return new Grass(place, this);
    case DANDELION_CHAR:
        return new Dandelion(place, this);
    case GUARANA_CHAR:
        return new Guarana(place, this);
    case HOGWEED_CHAR:
        return new Hogweed(place, this);
    case NIGHTSHADE_CHAR:
        return new Nightshade(place, this);

    default:
        return nullptr;
    }
}

void World::update_log_data(Human *player)
{
    log_data.player_kill_count = player->get_kill_count();
    log_data.current_x = player->get_x();
    log_data.current_y = player->get_y();
    log_data.strength = player->get_strength();
    log_data.skill_cooldown = player->get_cooldown();
    log_data.skill_time = player->get_skill();
    log_data.alive = player->is_alive();
    log_data.collision_message = player->get_collision_message();
}

void World::draw_log()
{
    int line = 1;
    int start_x = world_width + BORDER * 2, start_y = world_height + BORDER;
    draw_frame(log_data.width, log_data.height, start_x, 0);
    mvaddstr(line++, start_x + BORDER, "208379");
    mvaddstr(line++, start_x + BORDER, "ALICJA PISZCZEWIAT");

    if (!log_data.alive)
    {
        mvaddstr(line++, start_x + BORDER, "PLAYER DIED");
        return;
    }

    string help1 = log_data.collision_message;
    mvaddstr(line++, start_x + BORDER, help1.c_str());
   string help = "killed: " + to_string(log_data.player_kill_count);
    mvaddstr(line++, start_x + BORDER, help.c_str());
    help = "x: " + to_string(log_data.current_x);
    mvaddstr(line++, start_x + BORDER, help.c_str());
    help = "y: " + to_string(log_data.current_y);
    mvaddstr(line++, start_x + BORDER, help.c_str());
    help = "strength: " + to_string(log_data.strength);
    mvaddstr(line++, start_x + BORDER, help.c_str());
    if (log_data.skill_time > 0)
    {
        help = "skill active for: " + to_string(log_data.skill_time);
        mvaddstr(line++, start_x + BORDER, help.c_str());
    }
    else if (log_data.skill_cooldown > 0)
    {
        help = "cooldown for: " + to_string(log_data.skill_cooldown);
        mvaddstr(line++, start_x + BORDER, help.c_str());
    }
    else
        mvaddstr(line++, start_x + BORDER, "[a]ctivate skill");

    switch (get_key())
    {
    case KEY_UP:
        help = "UP";
        break;
    case KEY_LEFT:
        help = "LEFT";
        break;
    case KEY_DOWN:
        help = "DOWN";
        break;
    case KEY_RIGHT:
        help = "RIGHT";
        break;
    case 'a':
        help = "SPECIAL";
        break;
    default:
        help = "NO KEY";
        break;
    }
    mvaddstr(line++, start_x + BORDER, help.c_str());

    mvaddstr(line++, start_x + BORDER, "[n]ext turn");
    mvaddstr(line++, start_x + BORDER, "[q] try again");
    mvaddstr(line++, start_x + BORDER, "[s]ave");
}

void World::draw_frame(int width, int height, int start_x, int start_y)
{
    attron(COLOR_PAIR(BORDER_COLOR));
    mvaddch(start_y, start_x, ACS_ULCORNER);
    mvaddch(start_y + height + BORDER, start_x, ACS_LLCORNER);
    mvaddch(start_y, start_x + width + BORDER, ACS_URCORNER);
    mvaddch(start_y + height + BORDER, start_x + width + BORDER, ACS_LRCORNER);

    for (int x = BORDER; x < width + BORDER; x++)
    {
        mvaddch(start_y, start_x + x, ACS_HLINE);
        mvaddch(start_y + height + BORDER, start_x + x, ACS_HLINE);
    }

    for (int y = BORDER; y < height + BORDER; y++)
    {
        mvaddch(start_y + y, start_x, ACS_VLINE);
        mvaddch(start_y + y, start_x + width + BORDER, ACS_VLINE);
    }
    attroff(COLOR_PAIR(BORDER_COLOR));
}

int World::choose_map()
{

    delete_list(organisms);
    delete_list(added_organisms);
    organisms = nullptr;
    added_organisms = nullptr;

    coordinates current;
    for (int i = 0; i < world_width; i++)
    {
        current.x = i;
        for (int j = 0; j < world_height; j++)
        {
            current.y = j;
            set_field(current, nullptr);
        }
    }
    clear();
    draw_frame(LOG_WIDTH, LOG_HEIGHT, 0, 0);
    int lines = 0;
    mvaddstr(BORDER + lines++, BORDER, "choose map ");
    mvaddstr(BORDER + lines++, BORDER, "[1] from file");
    mvaddstr(BORDER + lines++, BORDER, "[2] randomized");
    refresh();
    while (true)
    {
        int ch = getch();
        if (ch == 27)
        {
            return 0;
        }
        else if (ch == '2')
        {
            refresh();
            int index = 4;
            string width = "";
            string height = "";
            while (index != 0)
            {

                int lines = 0;
                clear();
                mvaddstr(BORDER + lines++, BORDER, ("height: " + height).c_str());
                mvaddstr(BORDER + lines++, BORDER, ("width: " + width).c_str());
                refresh();

                ch = getch();
                char symbol = ch;
                if (ch == 27)
                {
                    return 0;
                }
                else

                    if (ch >= '0' && ch <= '9')
                {

                    index--;
                    if (index < 2)
                    {
                        width += symbol;
                    }
                    else
                    {
                        height += symbol;
                    }
                }
            }
            if (stoi(height) > MAX_WORLD_HEIGHT || stoi(height) < 0)
            {
                debug_file << "wrong map size";
                choose_map();
            }
            if (stoi(width) > MAX_WORLD_WIDTH || stoi(width) < 0)
            {
                debug_file << "wrong map size";
                choose_map();
            }
            world_height = stoi(height);
            world_width = stoi(width);

            start_game();
            break;
        }
        else if (ch == '1')
        {
            std::ifstream input_file("pliczek.txt");

            if (!input_file.is_open())
            {
                debug_file << "No file!" << endl;
                return 0;
            }
            if (!load_from_file(input_file))
            {
                return 0;
            }
            break;
        }
    }
    return 1;
}

void World::game_loop()
{
    int ch;
    while (true)
    {

        clear();

        draw_map();

        refresh();

        ch = getch();
        if (ch == 27)
        {
            break;
        }
        else if (ch == 'a' || ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)
        {
            remember_key(ch);
        }
        else if (ch == 'n')
        {
            turn();

            remember_key(RESET_DIRECTION);
        }
        else if (ch == 's')
        {
            std::ofstream out("pliczek.txt");
            if (out.is_open())
            {
                save_to_file(out);
            }
            else
                debug_file << "SAVE NOT AVAILABLE";
        }
        else if (ch == 'q')
        {
            clear();

            if (!choose_map())
            {
                break;
            }
        }
    }
}