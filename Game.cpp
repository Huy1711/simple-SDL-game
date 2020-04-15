#include "Game.h"
#include "TextureManager.h"


Game::Game(){


}

Game::~Game(){

}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
    case SDL_QUIT:
        status = GAME_STOP;
        break;
    default:
        break;
    }
}

void Game::update() {

}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
