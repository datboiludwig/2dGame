#include "player.hpp"
#include "key.hpp"

#include <string>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

Player::Player(uint16_t x, uint16_t y, SDL_Texture* t) {
    this->x = x;
    this->y = y;
    this->texture = t;

    if (t == NULL) {
        std::cerr << IMG_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

    SDL_QueryTexture(t, NULL, NULL, &this->w, &this->h);
}

Player::~Player() {
    SDL_DestroyTexture(texture);
}

void Player::render(SDL_Renderer* renderer) {
    const SDL_Rect rect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Player::update() {
    int8_t dx = (!!(keyMap & KEY_D) - !!(keyMap & KEY_A)) * speed;
    int8_t dy = (!!(keyMap & KEY_S) - !!(keyMap & KEY_W)) * speed;

    //std::cout << (int) dx << " \\ " << (int) dy << "\n";

    this->x += dx;
    this->y += dy;
}
