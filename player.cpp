#include "player.h"

void Player::render(SDL_Renderer* renderer) {

    SDL_Rect playerRect;
    playerRect.x = position.x;
    playerRect.y = position.y;
    playerRect.h = size;
    playerRect.w = size;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &playerRect);
    SDL_RenderCopy(renderer, playerTex, NULL, &playerRect);
}

bool Player::isInside(int minX, int minY, int maxX, int maxY) {
    return (minX<=position.x && position.x+size<=maxX &&
            minY<=position.y && position.y+size<=maxY);
}
void Player::move() {
    position.x+=stepX;
    position.y+=stepY;
    stepX = 0;
    stepY = 0;
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
