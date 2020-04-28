#include "Game.h"

Game::Game()
{

}

Game::~Game(){
    SDL_DestroyRenderer(renderer);
}

void Game::update() {

}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

