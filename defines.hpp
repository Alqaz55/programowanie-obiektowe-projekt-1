#pragma once


#include <vector>
using namespace std;
#include <iostream>
#include <cstdlib>  
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <ncurses.h>


#define WORLD_WIDTH 10
#define WORLD_HEIGHT 10
#define MAX_ORG_PER_SQUARE 2

#define LEFT -1
#define RIGHT 1
#define DOWN 1
#define UP -1



enum typ{
fauna,
flora
};

extern ofstream debuguj;


enum Kolory{
    KOLOR_TRAWY,
    KOLOR_MLECZY
};