#include <ncurses.h>
#include "headers/Wolf.hpp"
#include "headers/Human.hpp"
#include "headers/Grass.hpp"
#include "headers/Fox.hpp"
#include "headers/Antelope.hpp"
#include "headers/Turtle.hpp"
#include "headers/Guarana.hpp"

ofstream debug_file("debug.txt");
ofstream log_map_file("map.txt");

int main()
{

    World *world = new World(MAX_WORLD_WIDTH, MAX_WORLD_HEIGHT);

    if (!world->choose_map())
    {
        endwin();
        delete world;
        return 0;
    }
    int ch;
    world->game_loop();

    endwin();
    delete world;
    return 0;
}