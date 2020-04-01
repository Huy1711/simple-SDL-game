#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <cstring>
#include <SDL.h>
#include "SDL_utils.h"
#include "painter.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "My Game";

bool isInside(const SDL_Rect &rect, int minX, int minY, int maxX, int maxY) {
    return (minX<=rect.x && rect.x+32<=maxX && minY<=rect.y && rect.y+32<=maxY);
}

    void move(SDL_Rect &rect, int &stepX, int &stepY) {
        rect.x+=stepX;
        rect.y+=stepY;
        stepX=0;
        stepY=0;
    }

    void moveRight(int &stepX) {
        stepX+=32;
    }
    void moveLeft(int &stepX) {
        stepX-=32;
    }
    void moveUp(int &stepY) {
        stepY-=32;
    }
    void moveDown(int &stepY) {
        stepY+=32;
    }

int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_HEIGHT, SCREEN_WIDTH, WINDOW_TITLE);
    SDL_Texture* texture = NULL;

    SDL_Texture* mapTex;
    SDL_Surface* tmpSurface = IMG_Load("ava.jpg");
    mapTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    SDL_Rect player;
    player.h = 32;
    player.w = 32;
    player.x = 50;
    player.y = 50;
    int stepX=0, stepY=0;

    SDL_Event e;


    Painter painter(window, renderer);
    texture = painter.loadTexture("ava.jpg");


    while(isInside(player, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)) {
        painter.createImage(texture);
        SDL_RenderCopy(renderer, mapTex, NULL, &player);
        SDL_RenderPresent(renderer);
        SDL_Delay(50);

        if ( SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN) {
        	switch (e.key.keysym.sym) {
        		case SDLK_ESCAPE: break;
        		case SDLK_LEFT: moveLeft(stepX); break;
            	case SDLK_RIGHT: moveRight(stepX); break;
            	case SDLK_DOWN: moveDown(stepY); break;
            	case SDLK_UP: moveUp(stepY); break;
        		default: break;
			}
			move(player, stepX, stepY);
        }
    }

    waitUntilKeyPressed();
    SDL_DestroyTexture(texture);
    quitSDL(window, renderer);
    return 0;
}
