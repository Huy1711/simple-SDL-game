#include <iostream>
#include <stdlib.h>
#include <ctime>
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

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 300, 300, 50);


    Painter painter(window, renderer);
    for (int j=0; j<36; j++) {
        for (int i=0; i<10; i++) {
            painter.setRandomColor();
            painter.moveForward(30);
        }
        painter.setPosition(400, 300);
        painter.turnRight(10);
    }

    SDL_RenderPresent(renderer);

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
