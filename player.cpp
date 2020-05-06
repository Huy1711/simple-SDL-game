#include "player.h"

Player::Player(SDL_Renderer *ren, int x, int y) {
    renderer = ren;
    playerTex = Gallery::loadTexture("UET.jpg", renderer);
    position.x = x;
    position.y = y;
}

void Player::update(){
    playerRect.x = position.x;
    playerRect.y = position.y;
    playerRect.w = size;
    playerRect.h = size;
}

void Player::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
    update();
}

void Player::render(SDL_Renderer* renderer) {
    update();
    SDL_RenderCopy(renderer, playerTex, NULL, &playerRect);
}

bool Player::canMove(Direction direction, int map[20][30]){
    switch(direction) {
        case LEFT: return (position.x > 0 && map[position.y/30][(position.x-speed)/30]==0);
        case RIGHT: return (position.x < 900-30 && map[position.y/30][(position.x+speed)/30]==0);
        case UP: return (position.y > 0 && map[(position.y-speed)/30][position.x/30]==0);
        case DOWN: return  (position.y < 600-30 && map[(position.y+speed)/30][position.x/30]==0);
    }
}

void Player::move(Direction direction) {
    switch(direction) {
        case UP: position.y -= speed; break;
        case DOWN: position.y += speed; break;
        case LEFT: position.x -= speed; break;
        case RIGHT: position.x += speed; break;
    }
}

bool Player::checkCollision(const SDL_Rect &b) { //lazyfoo
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = playerRect.x;
    rightA = playerRect.x + playerRect.w;
    topA = playerRect.y;
    bottomA = playerRect.y + playerRect.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    if( bottomA <= topB )
    {
        return false;
    }
    if( topA >= bottomB )
    {
        return false;
    }
    if( rightA <= leftB )
    {
        return false;
    }
    if( leftA >= rightB )
    {
        return false;
    }
    return true;
}
