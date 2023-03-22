#include "key.hpp"

#include <SDL.h>

int64_t keyMap = 0;

void keyDown(SDL_Event* event) {
    switch (event->key.keysym.sym) {
    case SDLK_w:
        keyMap |= KEY_W;
        break;
    case SDLK_a:
        keyMap |= KEY_A;
        break;
    case SDLK_s:
        keyMap |= KEY_S;
        break;
    case SDLK_d:
        keyMap |= KEY_D;
        break;
    }
}

void keyUp(SDL_Event* event) {
    switch (event->key.keysym.sym) {
    case SDLK_w:
        keyMap ^= KEY_W;
        break;
    case SDLK_a:
        keyMap ^= KEY_A;
        break;
    case SDLK_s:
        keyMap ^= KEY_S;
        break;
    case SDLK_d:
        keyMap ^= KEY_D;
        break;
    }
}
