#pragma once
#include "SDL.h" 

class Collisions {
public:
    static bool isOverlapping(SDL_Rect& a, SDL_Rect& b);
};
