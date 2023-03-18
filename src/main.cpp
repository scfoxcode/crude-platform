#include "SDL.h" 
#include "SDL_render.h"
#include <glm/glm.hpp>
#include <chrono>

const int RESX = 1280; //960;
const int RESY = 720; //540;
const int pixelCount = RESX * RESY;

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


    // Timers 
    auto startTime = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::high_resolution_clock::now();
    double elapsedMs = std::chrono::duration<double, std::milli>(endTime - startTime).count();
    printf("Time taken: %fms\n", elapsedMs);

    SDL_Rect rect;
    rect.x = 64;
    rect.y = 64;
    rect.w = 64;
    rect.h = 64;
    
    SDL_Event event;
    while (running) {
        SDL_RenderClear(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        //
        // Draw code
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderDrawRect(renderer, &rect);
        // SDL_RenderFillRect
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
