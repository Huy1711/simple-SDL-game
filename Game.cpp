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

    SDL_RenderPresent(renderer);
}
