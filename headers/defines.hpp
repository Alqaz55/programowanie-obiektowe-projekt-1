#pragma once

#include <vector>
using namespace std;
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <ncurses.h>

#define MAX_WORLD_WIDTH 40
#define MAX_WORLD_HEIGHT 40
#define MAX_ORG_PER_SQUARE 2

#define LEFT -1
#define RIGHT 1
#define DOWN 1
#define UP -1

#define BORDER 1
#define LOG_WIDTH 30
#define LOG_HEIGHT 20

typedef enum
{
    flora,
    fauna,
    ilosc_typow
} typ;

extern ofstream debug_file;

extern ofstream log_map_file;

enum Kolory
{
    NO_COLOR,
    GRASS_COLOR,
    DANDELION_COLOR,
    GUARANA_COLOR,
    HOGWEED_COLOR,
    NIGHTSHADE_COLOR,
    BORDER_COLOR

};

enum Collision_effect
{
    DIE,
    STAY,
    MOVE,
    RELOCATED
};

#define SURROUNDING_SQUARES 9

#define HUMAN_STRENGTH 10
#define HUMAN_INITIATIVE 40
#define HUMAN_CHAR 'C'
#define HUMAN_COOLDOWN 5
#define HUMAN_SKILL 5

#define WOLF_STRENGTH 9
#define WOLF_INITIATIVE 5
#define WOLF_CHAR 'W'

#define SHEEP_STRENGTH 4
#define SHEEP_INITIATIVE 4
#define SHEEP_CHAR 'O'

#define FOX_STRENGTH 3
#define FOX_INITIATIVE 1
#define FOX_CHAR 'L'

#define TURTLE_STRENGTH 2
#define TURTLE_INITIATIVE 1
#define TURTLE_CHAR 'Z'
#define TURTLE_DODGES 100
#define TURTLE_MOVEMENT_CHANCE 4

#define ANTELOPE_STRENGTH 4
#define ANTELOPE_INITIATIVE 4
#define ANTELOPE_CHAR 'A'
#define ANTELOPE_MISS_CHANCE 2

#define GUARANA_STRNGTH_ADD 3
#define DANDELION_ATTEMPT 3
#define HOGWEED_STRENGTH 10
#define NIGHTSHADE_STRENGTH 99
#define PLANT_STRENGTH 0
#define PLANT_INITIATIVE 0

#define RESET_DIRECTION ' '

#define GRASS_CHAR 'G'
#define DANDELION_CHAR 'D'
#define GUARANA_CHAR 'U'
#define HOGWEED_CHAR 'H'
#define NIGHTSHADE_CHAR 'N'