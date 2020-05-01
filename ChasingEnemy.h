#ifndef CHASINGENEMY_H
#define CHASINGENEMY_H
#include "TextureManager.h"
#include "Position.h"
#include <cstring>
#include <SDL.h>

class ChasingEnemy {

    int size = 30;
    SDL_Renderer* renderer;
    SDL_Texture* enemyTex;

public:
    Position enemyPos;
    SDL_Rect enemyRect;
    int speed = 1;

    ChasingEnemy(SDL_Renderer* ren, int x, int y);
    ~ChasingEnemy() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(enemyTex);
    }
    void update();
    void render(SDL_Renderer* renderer);
    void move(Direction direction);
    bool canMove(Direction direction, bool map[20][30]);
};

#endif
