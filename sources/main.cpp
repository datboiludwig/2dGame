// C/C++ System libs

#include <iostream>

// Third-party libs

#include <SDL.h>
#include <SDL_image.h>

// Project headers
#include "env.hpp"
#include "player.hpp"
#include "loop.hpp"
#include "key.hpp"


int main(int, char**) {

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }
    if (!IMG_Init(IMG_INIT_PNG)) {
        std::cerr << IMG_GetError() << "\n";
        return EXIT_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    GameLoop loop(60.f);

    Player player(WIDTH / 2, HEIGHT / 2, IMG_LoadTexture(renderer, "assets/logo.png"));

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                keyDown(&e);
                break;
            case SDL_KEYUP:
                keyUp(&e);
                break;
            }
        }

        if (loop.shouldUpdate()) {
            player.update();
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        player.render(renderer);

        SDL_RenderPresent(renderer);
    }

    player.~Player();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}