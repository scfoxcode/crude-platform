#pragma once
#include <glm/glm.hpp>
#include "SDL.h" 
#include "SDL_render.h"
#include <vector>

class Player {
private:
    glm::vec2 m_position;
    glm::vec2 m_velocity;

    SDL_Rect m_rect;
    
public:
    Player();

    void init(glm::vec2 pos);

    void update(float dt, std::vector<SDL_Rect>& tiles);

    void moveLeft();
    void moveRight();
    void jump();

    void render(SDL_Renderer* renderer);
};
