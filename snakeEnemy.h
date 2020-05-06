#ifndef SNAKE_ENEMY__H
#define SNAKE_ENEMY__H
#include "Gallery.h"
#include "Position.h"
#include <cstring>
#include <SDL.h>
class SnakeEnemy {

    int size = 30;
    SDL_Renderer* renderer;
    SDL_Texture* enemyTex;

public:
    Position enemyPos;
    SDL_Rect enemyRect;
    int speed = 5;

    SnakeEnemy(SDL_Renderer* ren, int x, int y);
    ~SnakeEnemy() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(enemyTex);
    }
    void update();
    void render(SDL_Renderer* renderer);
    void move(Direction direction);
    bool canMove(Direction direction, int map[20][30]);
};
#endif

