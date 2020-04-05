#include "player.h"


void Player::render(SDL_Renderer* renderer) {
    SDL_Surface* tmpSurface = IMG_Load("pacman.jpg");
    playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    SDL_Rect playerRect;
    playerRect.x = x;
    playerRect.y = y;
    playerRect.h = size;
    playerRect.w = size;
    SDL_RenderCopy(renderer, playerTex, NULL, &playerRect);
}

bool Player::isInside(int minX, int minY, int maxX, int maxY) {
    return (minX<=x && x+size<=maxX && minY<=y && y+size<=maxY);
}
void Player::move() {
    x+=stepX;
    y+=stepY;
}

void Player::moveRight() {
    stepX=size;
    stepY=0;
}
void Player::moveLeft() {
    stepX=-size;
    stepY=0;
}
void Player::moveUp() {
    stepY=-size;
    stepX=0;
}
void Player::moveDown() {
    stepY=size;
    stepX=0;
}
