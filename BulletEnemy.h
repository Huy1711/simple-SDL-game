#ifndef BULLET_ENEMY__H
#define BULLET_ENEMY__H
#include "Gallery.h"
#include "Position.h"
#include <cstring>
#include <SDL.h>
#include "player.h"
class BulletEnemy {

    int size = 30;
    SDL_Renderer* renderer;
    SDL_Texture* enemyTex;

public:
    Position enemyPos;
    SDL_Rect enemyRect;
    int speed = 5;

    BulletEnemy(SDL_Renderer* ren, int x, int y);
    ~BulletEnemy() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(enemyTex);
    }
    void setPosition(int x, int y);
    void update();
    void render(SDL_Renderer* renderer);
    void move(Direction direction);
    bool canMove(Direction direction, int map[20][30]);
    void bulletMoving(const Player &player, int map[20][30]);
};

#endif

