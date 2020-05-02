#include "ChasingEnemy.h"

ChasingEnemy::ChasingEnemy(SDL_Renderer* ren, int x, int y) {
    renderer = ren;
    enemyTex = Gallery::loadTexture("ulis.jpg", renderer);
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
    update();
    SDL_RenderCopy(renderer, enemyTex, NULL, &enemyRect);
}

void ChasingEnemy::setPosition(int x, int y) {
    enemyPos.x = x;
    enemyPos.y = y;
    update();
}

void ChasingEnemy::move(Direction direction) {
    switch(direction) {
        case UP: enemyPos.y -= 1*speed; break;
        case DOWN: enemyPos.y += 1*speed; break;
        case LEFT: enemyPos.x -= 1*speed; break;
        case RIGHT: enemyPos.x += 1*speed; break;
    }
}

bool ChasingEnemy::canMove(Direction direction, int map[20][30]){
    switch(direction) {
        case LEFT: return (enemyPos.x > 0 && map[enemyPos.y/30][(enemyPos.x)/30]==0);
        case RIGHT: return (enemyPos.x < 900-30 && map[enemyPos.y/30][(enemyPos.x)/30+1]==0);
        case UP: return (enemyPos.y > 0 && map[enemyPos.y/30][enemyPos.x/30]==0);
        case DOWN: return  (enemyPos.y < 600-30 && map[enemyPos.y/30+1][enemyPos.x/30]==0);
    }
}

void ChasingEnemy::chasingEnemy(const Player &player, int map[20][30]) {
    int distanceX = abs(player.position.x - enemyPos.x);
    int distanceY = abs(player.position.y - enemyPos.y);
    if (enemyPos.x < player.position.x && enemyPos.y >= player.position.y) {
        if(distanceX<=distanceY && canMove(UP, map))
            move(UP);
        else if (distanceX>distanceY && canMove(RIGHT, map))
            move(RIGHT);
    } else if(enemyPos.x >= player.position.x && enemyPos.y > player.position.y) {
        if(distanceX<=distanceY && canMove(UP, map))
            move(UP);
        else if (distanceX>distanceY && canMove(LEFT, map))
            move(LEFT);
    } else if (enemyPos.x > player.position.x && enemyPos.y <= player.position.y) {
        if(distanceX<=distanceY && canMove(DOWN, map))
            move(DOWN);
        else if (distanceX>distanceY && canMove(LEFT, map))
            move(LEFT);
    } else if (enemyPos.x <= player.position.x && enemyPos.y < player.position.y) {
        if(distanceX<=distanceY && canMove(DOWN, map))
            move(DOWN);
        else if (distanceX>distanceY && canMove(RIGHT, map))
            move(RIGHT);
    }
}
