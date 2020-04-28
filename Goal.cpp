#include "Goal.h"

Goal::Goal(SDL_Renderer *ren, int x, int y) {
    renderer = ren;
    goalTex = TextureManager::loadTexture("blue.jpg", renderer);
    position.x = x;
    position.y = y;
}

void Goal::update(){

}

void Goal::render(SDL_Renderer* renderer) {
    goalRect.x = position.x*30;
    goalRect.y = position.y*30;
    goalRect.w = 3*30;
    goalRect.h = 5*30;
    SDL_RenderCopy(renderer, goalTex, NULL, &goalRect);
}
