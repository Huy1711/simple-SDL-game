#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* ren, int x, int y) {
    renderer = ren;
    enemyTex = TextureManager::loadTexture("HUST.jpg", renderer);
    enemyPos.x = x;
    enemyPos.y = y;
}

void Enemy::update(){

    enemyRect.x = enemyPos.x*size;
    enemyRect.y = enemyPos.y*size;
    enemyRect.w = size;
    enemyRect.h = size;
}

void Enemy::render(SDL_Renderer* renderer) {
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
