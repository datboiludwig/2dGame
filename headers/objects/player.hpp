#pragma once

#include <string>

#include <SDL.h>

#include "game_object.hpp"

class Player: public GameObject {
private:

public:
    const uint16_t speed = 3;

    SDL_Texture* texture;
    int w, h;


    Player(uint16_t x, uint16_t y, SDL_Texture* t);
    ~Player();

    void render(SDL_Renderer* renderer);
    void update();
};