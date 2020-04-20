#include "player.h"

Player::Player(SDL_Renderer* ren, int x, int y) {
    renderer = ren;
    playerTex = TextureManager::loadTexture("UET.jpg", ren);
    position.position.x = x;
    position.position.y = y;
}

void Player::update(){
    playerRect.x = position.position.x;
    playerRect.y = position.position.y;
    playerRect.w = size;
    playerRect.h = size;
}

void Player::render(SDL_Renderer* renderer) {

    SDL_RenderCopy(renderer, playerTex, NULL, &playerRect);
}

bool Player::checkCollision( SDL_Rect b ) {
    {
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
}
