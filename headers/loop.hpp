#pragma once

#include <SDL.h>

#include <iostream>

class GameLoop {
public:
    float fps;
    uint64_t lastTime;
    double ms;
    double delta = 0;
    long timer;
    int updates = 0;

    GameLoop(float fps) {
        this->fps = fps;
        lastTime = SDL_GetTicks64();
        timer = SDL_GetTicks64();
        ms = 1000 / this->fps;
    }

    bool shouldUpdate() {
        bool result = false;
        long now = SDL_GetTicks64();
        delta += (now - lastTime) / ms;
        lastTime = now;
        while (delta >= 1) {
            result = true;
            updates++;
            delta--;
        }

        if (SDL_GetTicks64() - timer > 1000) {
            timer += 1000;
            updates = 0;
        }

        return result;
    }
};