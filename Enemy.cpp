#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* ren, int x, int y) {
    renderer = ren;
    enemyTex = Gallery::loadTexture("is.jpg", renderer);
    enemyPos.x = x;
    enemyPos.y = y;
}

void Enemy::update(){

    enemyRect.x = enemyPos.x;
    enemyRect.y = enemyPos.y;
    enemyRect.w = size;
    enemyRect.h = size;
}

void Enemy::render(SDL_Renderer* renderer) {
    update();
    SDL_RenderCopy(renderer, enemyTex, NULL, &enemyRect);
}

void Enemy::move(Direction direction) {
    switch(direction) {
        case UP: enemyPos.y -= 1*speed; break;
        case DOWN: enemyPos.y += 1*speed; break;
        case LEFT: enemyPos.x -= 1*speed; break;
        case RIGHT: enemyPos.x += 1*speed; break;
    }
}

bool Enemy::canMove(Direction direction, int map[20][30]){
    switch(direction) {
        case LEFT: return (enemyPos.x > 0 && map[enemyPos.y/30][(enemyPos.x)/30]==0);
        case RIGHT: return (enemyPos.x < 900-30 && map[enemyPos.y/30][(enemyPos.x)/30+1]==0);
        case UP: return (enemyPos.y > 0 && map[enemyPos.y/30][enemyPos.x/30]==0);
        case DOWN: return  (enemyPos.y < 600-30 && map[enemyPos.y/30+1][enemyPos.x/30]==0);
    }
}

void Enemy::horizontalMoving(int map[20][30]) {
    move(RIGHT);
    if (map[enemyPos.y/30][enemyPos.x/30+1]!=0) {
            speed*=-1;
    }
    if (map[enemyPos.y/30][(enemyPos.x+speed)/30]!=0) {
            speed*=-1;
    }
}
