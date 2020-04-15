#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cstring>
#include <SDL.h>
#include "SDL_utils.h"
#include "TextureManager.h"
#include "player.h"
#include "Game.h"
using namespace std;

Game *game = nullptr;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "My Game";

int main(int argc, char* argv[])
{
    srand(time(0));
    game = new Game();
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_HEIGHT, SCREEN_WIDTH, WINDOW_TITLE);

    const int FPS = 60;
    const int frameDelay = 1000/FPS;
    unsigned int frameStart;
    int frameTime;

    SDL_Texture* playerTex;
    playerTex = TextureManager::loadTexture("UET.jpg", renderer);

    Player player;

    while(true) {
        frameStart = SDL_GetTicks();


        SDL_RenderCopy(renderer, playerTex, NULL, NULL);
        // game->handleEvents();
        game->update();
        game->render();
        SDL_RenderPresent(renderer);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
