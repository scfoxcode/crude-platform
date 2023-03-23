#include "SDL.h" 
#include "SDL_render.h"
#include <glm/glm.hpp>
#include <chrono>
#include <vector>
#include "player.h"

const int RESX = 1280; //960;
const int RESY = 720; //540;
const int TILE_SIZE = 64;

void buildTerrain(std::vector<SDL_Rect>& tiles, int num, int xOffset, int yOffset) {
    // Make some ground
    for (int i=0; i<num; i++) {
        SDL_Rect rect;
        rect.x = i * 64 + xOffset;
        rect.y = RESY - TILE_SIZE - yOffset * TILE_SIZE;
        rect.w = TILE_SIZE;
        rect.h = TILE_SIZE;
        tiles.push_back(rect);
    }
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    bool running = true;

    SDL_Window *window = SDL_CreateWindow(
        "platformer",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        RESX,
        RESY,
        0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    std::vector<SDL_Rect> tiles;
    buildTerrain(tiles, 1, TILE_SIZE, 0);
    buildTerrain(tiles, 4, TILE_SIZE * 6, 0);
    buildTerrain(tiles, 3, TILE_SIZE * 12, 0);
    buildTerrain(tiles, 2, TILE_SIZE * 16, 1);

    Player* player = new Player();
    player->init(glm::vec2(TILE_SIZE, float(RESY) * 0.5f));
    bool moveLeft = false;
    bool moveRight = false;
    
    SDL_Event event;
    while (running) {
        auto startTime = std::chrono::high_resolution_clock::now();
        SDL_RenderClear(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                // Player character controls
                if (event.key.keysym.sym == SDLK_a) {
                    moveLeft = true;
                }
                if (event.key.keysym.sym == SDLK_d) {
                    moveRight = true;
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    player->jump();
                }
            } else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_a) {
                    moveLeft = false;
                }
                if (event.key.keysym.sym == SDLK_d) {
                    moveRight = false;
                }
            }
        }

        // Updates
        if (moveLeft) {
            player->moveLeft();
        }
        if (moveRight) {
            player->moveRight();
        }
        player->update(16.0f / 1000.0f, tiles);


        // Draw terrain 
        for (auto iter = tiles.begin(); iter < tiles.end(); iter++) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            SDL_RenderFillRect(renderer, &(*iter));
        }

        // Draw character
        player->render(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderPresent(renderer);
        auto endTime = std::chrono::high_resolution_clock::now();
        double elapsedMs = std::chrono::duration<double, std::milli>(endTime - startTime).count();
        if (elapsedMs < 16) {
            SDL_Delay(16.0 - elapsedMs);
        }
    }

    delete player;
    player = nullptr;
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
