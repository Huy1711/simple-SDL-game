#include "Goal.h"

void Goal::render(SDL_Renderer* renderer) {
//    position.x = 400;
  //  position.y = 300;
    SDL_Rect playerRect;
    playerRect.x = position.x;
    playerRect.y = position.y;
    playerRect.h = size;
    playerRect.w = size;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &playerRect);
    SDL_RenderCopy(renderer, playerTex, NULL, &playerRect);
}

void Goal::move() {
    position.x+=stepX;
    position.y+=stepY;
    stepX = 0;
    stepY = 0;
}

void Goal::moveRight() {
    stepX=size;
    stepY=0;
}
void Goal::moveLeft() {
    stepX=-size;
    stepY=0;
}
void Goal::moveUp() {
    stepY=-size;
    stepX=0;
}
void Goal::moveDown() {
    stepY=size;
    stepX=0;
}

