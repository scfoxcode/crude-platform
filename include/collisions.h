#pragma once
#include "SDL.h" 
#include <glm/glm.hpp>

class Collisions {
public:
    static glm::vec2 centre(SDL_Rect& a);

    static bool isOverlapping(SDL_Rect& a, SDL_Rect& b);
    
    static void resolveCollision(
        glm::vec2& position,
        glm::vec2& velocity,
        SDL_Rect& a,
        SDL_Rect& b);
};
