#include "player.h"
#include "collisions.h"

Player::Player() {
}

void Player::init(glm::vec2 pos) {
    m_position = pos;

    m_rect.x = m_position.x;
    m_rect.y = m_position.y;
    m_rect.w = 64;
    m_rect.h = 128;
}

// dt in seconds since last update
void Player::update(float dt, std::vector<SDL_Rect>& tiles) {
    // Apply gravity
    m_velocity.x *= 0.93;
    m_velocity.y += 60.0f * dt;

    // Apply friction, whether you are touching a surface or not
    // m_velocity.x *=

    SDL_Rect newRect = m_rect;
    glm::vec2 newPosition = m_position;

    // Proposed position
    newPosition += m_velocity;

    // Proposed rect
    newRect.x = newPosition.x;
    newRect.y = newPosition.y;

    // Resolve terrain collisions
    for (auto iter = tiles.begin(); iter < tiles.end(); iter++) {
        bool hasCollided = Collisions::isOverlapping(newRect, *iter);
        if (hasCollided) {
            // m_velocity.x = 0; // Can't keep this, it assumes a top down collision
            m_position.x = newPosition.x;
            m_rect.x = newRect.x;
            m_velocity.y = 0;
            return;
        }
    }

    // No collision
    m_position = newPosition;
    m_rect = newRect;
}

void Player::moveLeft() {
    m_velocity.x -= 0.5f;
}

void Player::moveRight() {
    m_velocity.x += 0.5f;
}

void Player::jump() {
    m_velocity.y = -20.f;
}

void Player::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &m_rect);
}
