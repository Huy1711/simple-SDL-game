#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cstring>
#include <SDL.h>
#include "SDL_utils.h"
#include "TextureManager.h"
#include "player.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "My Game";
int DELAY_TIME = 100;

int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_HEIGHT, SCREEN_WIDTH, WINDOW_TITLE);

    SDL_Texture* texture = NULL;

    Player player;
    SDL_Event e;

    while(player.isInside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)) {
        player.move();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        player.render(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(DELAY_TIME);

        if ( SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN) {
        	switch (e.key.keysym.sym) {
        		case SDLK_ESCAPE: break;
        		case SDLK_LEFT: player.moveLeft(); break;
            	case SDLK_RIGHT: player.moveRight(); break;
            	case SDLK_DOWN: player.moveDown(); break;
            	case SDLK_UP: player.moveUp(); break;
        		default: break;
			}
        }

    }

    waitUntilKeyPressed();
    SDL_DestroyTexture(texture);
    quitSDL(window, renderer);
    return 0;
}
