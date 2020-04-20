#include "Game.h"

Game::Game()
//    : player(*this, renderer, 120, 240)
{

}

Game::~Game(){
    SDL_DestroyRenderer(renderer);
}
/*
void Game::interpretEvent(SDL_Event e)
{
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        	case SDLK_UP: player.position.velocity.y=-1; break;
        	case SDLK_DOWN: player.position.velocity.y=1; break;
        	case SDLK_LEFT: player.position.velocity.x=-1; break;
        	case SDLK_RIGHT: player.position.velocity.x=1; break;
        }
    }
    if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
        	case SDLK_UP: player.position.velocity.y=0; break;
        	case SDLK_DOWN: player.position.velocity.y=0; break;
        	case SDLK_LEFT: player.position.velocity.x=0; break;
        	case SDLK_RIGHT: player.position.velocity.x=0; break;
        }
    }
}
*/
void Game::update() {

}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
