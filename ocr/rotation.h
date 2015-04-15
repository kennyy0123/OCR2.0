#ifndef HEADER_ROT
#define HEADER_ROT
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#include <SDL/SDL.h>
#include "filtre.h"
void rotation(float r);
SDL_Surface* SDL_CentralRotation(SDL_Surface* origin, float angle);
#endif
