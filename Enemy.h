#ifndef ENEMY_H
#define ENEMY_H
#include "TextureManager.h"
#include "Position.h"
#include <SDL.h>

class Enemy {

    int size = 30;
    SDL_Renderer* renderer;
    SDL_Texture* enemyTex;

public:
    Position enemyPos;
    SDL_Rect enemyRect;
    int speed = 1;

    Enemy(SDL_Renderer* ren, int x, int y);
    ~Enemy() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(enemyTex);
    }
    void update();
    void render(SDL_Renderer* renderer);
    void move(Direction direction);
};

#endif // ENEMY_H
