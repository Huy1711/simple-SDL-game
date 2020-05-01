#include "ChasingEnemy.h"

ChasingEnemy::ChasingEnemy(SDL_Renderer* ren, int x, int y) {
    renderer = ren;
    enemyTex = TextureManager::loadTexture("ulis.jpg", renderer);
    enemyPos.x = x;
    enemyPos.y = y;
}

void ChasingEnemy::update(){

    enemyRect.x = enemyPos.x;
    enemyRect.y = enemyPos.y;
    enemyRect.w = size;
    enemyRect.h = size;
}

void ChasingEnemy::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, enemyTex, NULL, &enemyRect);
}

void ChasingEnemy::move(Direction direction) {
    switch(direction) {
        case UP: enemyPos.y -= 1*speed; break;
        case DOWN: enemyPos.y += 1*speed; break;
        case LEFT: enemyPos.x -= 1*speed; break;
        case RIGHT: enemyPos.x += 1*speed; break;
    }
}

bool ChasingEnemy::canMove(Direction direction, bool map[20][30]){
    switch(direction) {
        case LEFT: return (enemyPos.x > 0 && !map[enemyPos.y/30][(enemyPos.x)/30]);
        case RIGHT: return (enemyPos.x < 900-30 && !map[enemyPos.y/30][(enemyPos.x)/30+1]);
        case UP: return (enemyPos.y > 0 && !map[enemyPos.y/30][enemyPos.x/30]);
        case DOWN: return  (enemyPos.y < 600-30 && !map[enemyPos.y/30+1][enemyPos.x/30]);
    }
}
