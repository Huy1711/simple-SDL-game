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

int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_HEIGHT, SCREEN_WIDTH, WINDOW_TITLE);
    SDL_Texture* texture = NULL;

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 200, 200, 50);

    Painter painter(window, renderer);
    painter.setColor(CYAN_COLOR);



    SDL_RenderPresent(renderer);

    waitUntilKeyPressed();
    SDL_DestroyTexture(texture);
    quitSDL(window, renderer);
    return 0;
}
