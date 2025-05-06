#pragma once

/* LIBRARIES AND CONSTS */

#include <iostream>
#include <SDL3/SDL.h>
#include <vector>

using namespace std;

const int WINDOW_WIDTH = 600, WINDOW_HEIGHT = 600;
const int GAME_SCALE = 20;
const int GAME_SPEED = 200;

// pixel types
const int EMPTY_PIXEL = 10;
const int SOLID_PIXEL = 0;
const int FALLING_SAND_PIXEL = 1;
const int WATER_PIXEL = 2;

// button types
const int DRAW = 0;
const int ERASE = 1;
const int CLEAR = 2;
const int PAUSE = 3;
const int SHADER = 4;