#pragma once


#include <vector>
using namespace std;
#include <iostream>
#include <cstdlib>  
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <ncurses.h>


#define WORLD_WIDTH 8
#define WORLD_HEIGHT 8
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
    BRAK_KOLORU,
    KOLOR_TRAWY,
    KOLOR_MLECZY
};


#define CZLOWIEK_STRENGTH 5
#define CZLOWIEK_INITIATIVE 4
#define CZLOWIEK_CHAR 'C'


#define WILK_STRENGTH 9
#define WILK_INITIATIVE 5
#define WILK_CHAR 'W'

#define OWCA_STRENGTH 4
#define OWCA_INITIATIVE 4
#define OWCA_CHAR 'O'

#define LIS_STRENGTH 3
#define LIS_INITIATIVE 7
#define LIS_CHAR 'L'

#define ZOLW_STRENGTH 2
#define ZOLW_INITIATIVE 1
#define ZOLW_CHAR 'Z'
#define ZOLW_DODGES 5
#define ZOLW_MOVEMENT_CHANCE 3

#define ANTILOPE_STRENGTH 4
#define ANTILOPE_INITIATIVE 4
#define ANTILOPE_CHAR 'A'