#include "player.h"
#include "collisions.h"

Player::Player() {
}

// Ahh position is top left remember...
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

    // Update position
    m_position += m_velocity;

    // Update rect
    m_rect.x = m_position.x;
    m_rect.y = m_position.y;

    // Test and resolve terrain collisions
    for (auto iter = tiles.begin(); iter < tiles.end(); iter++) {
        bool hasCollided = Collisions::isOverlapping(m_rect, *iter);
        if (hasCollided) {
            Collisions::resolveCollision(m_position, m_velocity, m_rect, *iter);
            return;
        }
    }
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
