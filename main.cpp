#include <iostream>
#include <SDL.h>
#include "SDL_utils.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "An Implementation of Code.org Painter";

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_HEIGHT, SCREEN_WIDTH, WINDOW_TITLE);

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 333, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 100, 100, 300, 200);

    SDL_SetRenderDrawColor(renderer, 0, 333, 0, 100);
    SDL_Rect filledRect;
    filledRect.x = 200;
    filledRect.y = 200;
    filledRect.h = 100;
    filledRect.w = 150;
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderFillRect(renderer, &filledRect);

    SDL_RenderPresent(renderer);

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
