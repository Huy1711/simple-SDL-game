#include "BulletEnemy.h"

BulletEnemy::BulletEnemy(SDL_Renderer* ren, int x, int y) {
    renderer = ren;
    enemyTex = Gallery::loadTexture("ussh.jpg", renderer);
    enemyPos.x = x;
    enemyPos.y = y;
}

void BulletEnemy::update(){

    enemyRect.x = enemyPos.x;
    enemyRect.y = enemyPos.y;
    enemyRect.w = size;
    enemyRect.h = size;
}

void BulletEnemy::render(SDL_Renderer* renderer) {
    update();
    SDL_RenderCopy(renderer, enemyTex, NULL, &enemyRect);
}

void BulletEnemy::setPosition(int x, int y) {
    enemyPos.x = x;
    enemyPos.y = y;
    update();
}

void BulletEnemy::move(Direction direction) {
    switch(direction) {
        case UP: enemyPos.y -= 1*speed; break;
        case DOWN: enemyPos.y += 1*speed; break;
        case LEFT: enemyPos.x -= 1*speed; break;
        case RIGHT: enemyPos.x += 1*speed; break;
    }
}

bool BulletEnemy::canMove(Direction direction, int map[20][30]){
    switch(direction) {
        case LEFT: return (enemyPos.x > 0 && map[enemyPos.y/30][(enemyPos.x)/30]==0);
        case RIGHT: return (enemyPos.x < 900-30 && map[enemyPos.y/30][(enemyPos.x)/30+1]==0);
        case UP: return (enemyPos.y > 0 && map[enemyPos.y/30][enemyPos.x/30]==0);
        case DOWN: return  (enemyPos.y < 600-30 && map[enemyPos.y/30+1][enemyPos.x/30]==0);
    }
}

void BulletEnemy::bulletMoving(const Player &player, int map[20][30]) {
    if(canMove(DOWN, map)) move(DOWN);
    if(enemyPos.y >= 540) setPosition(player.position.x, 60);
}

