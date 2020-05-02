#ifndef ENEMY_H
#define ENEMY_H
#include "Gallery.h"
#include "Position.h"
#include <cstring>
#include <SDL.h>

class Enemy {

    int size = 30;
    SDL_Renderer* renderer;
    SDL_Texture* enemyTex;

public:
    Position enemyPos;
    SDL_Rect enemyRect;
    int speed = 5;

    Enemy(SDL_Renderer* ren, int x, int y);
    ~Enemy() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(enemyTex);
    }
    void update();
    void render(SDL_Renderer* renderer);
    void move(Direction direction);
    bool canMove(Direction direction, int map[20][30]);
    void horizontalMoving(int map[20][30]);
};

#endif // ENEMY_H
