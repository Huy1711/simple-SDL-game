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
    SDL_SetRenderDrawColor(renderer, 0, 200, 200, 50);

    Painter painter(window, renderer);
    painter.setColor(CYAN_COLOR);

    painter.turnLeft(30);
    for (int j=0; j<4; j++){
        for (int i=0; i<4; i++) {
            painter.setRandomColor();
            painter.moveForward(50);
            painter.turnRight(20);
        }
        painter.turnRight(100);
        for (int i=0; i<4; i++) {
            painter.setRandomColor();
            painter.moveForward(50);
            painter.turnRight(20);
        }
        painter.turnLeft(180);
    }

    painter.setPosition(400, 300);
    painter.setAngle(60);
    painter.turnRight(15);
    int i=110, rad=10;
    do {
        painter.setRandomColor();
        painter.moveForward(i);
        painter.turnRight(rad);
        i/=2;
        rad+=20;
    } while(i>0);
    painter.setPosition(400, 300);
    painter.setAngle(60);
    painter.turnLeft(15);
    int i2=110, rad2=10;
    do {
        painter.setRandomColor();
        painter.moveForward(i2);
        painter.turnLeft(rad2);
        i2/=2;
        rad2+=20;
    } while(i2>0);


    SDL_RenderPresent(renderer);

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}
