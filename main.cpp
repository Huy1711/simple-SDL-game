#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <SDL.h>
#include <chrono>
#include "SDL_utils.h"
#include "TextureManager.h"
#include "player.h"
#include "Game.h"
using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "My Game";

const int BOARD_WIDTH = 30;
const int BOARD_HEIGHT = 20;
const int CELL_SIZE = 30;

const SDL_Color BOARD_COLOR = {0, 0, 0};
const SDL_Color LINE_COLOR = {128, 128, 128};

const double STEP_DELAY = 0.2;
#define CLOCK_NOW chrono::system_clock::now
typedef chrono::duration<double> ElapsedTime;

void interpretEvent(SDL_Event e, Game& game, Player &player);
void renderGamePlay(SDL_Renderer* renderer, const Game& game, Player &player, SDL_Rect tmpRect);
void drawVerticalLine(SDL_Renderer* renderer, int left, int top, int cells);
void drawHorizontalLine(SDL_Renderer* renderer, int left, int top, int cells);

int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_HEIGHT, SCREEN_WIDTH, WINDOW_TITLE);
    Game game;
    SDL_Event e;
    // Player player;

    SDL_Rect tmpRect;
    tmpRect.x = 690;
    tmpRect.y = 210;
    tmpRect.w = 30*3;
    tmpRect.h = 30*5;

    auto start = CLOCK_NOW();
    Player player(renderer, 120, 240);

    while(true) {
        while (SDL_PollEvent(&e)) {
            interpretEvent(e, game, player);
        }

        auto end = CLOCK_NOW();
        ElapsedTime elapsed = end-start;
        if (elapsed.count() > STEP_DELAY) {

            renderGamePlay(renderer, game, player, tmpRect);
            start = end;
        }
    }

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

void interpretEvent(SDL_Event e, Game& game, Player &player)
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

void drawVerticalLine(SDL_Renderer* renderer, int left, int top, int cells)
{
    SDL_SetRenderDrawColor(renderer, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b, 0);
    SDL_RenderDrawLine(renderer, left, top, left, top + cells * CELL_SIZE);
}

void drawHorizontalLine(SDL_Renderer* renderer, int left, int top, int cells)
{
    SDL_SetRenderDrawColor(renderer, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b, 0);
    SDL_RenderDrawLine(renderer, left, top, left + cells * CELL_SIZE, top);
}

void renderGamePlay(SDL_Renderer* renderer, const Game& game, Player &player, SDL_Rect tmpRect) {
    int top = 0, left = 0;
    SDL_SetRenderDrawColor(renderer, BOARD_COLOR.r, BOARD_COLOR.g, BOARD_COLOR.b, 0);
    SDL_RenderClear(renderer);

    for (int x = 0; x <= BOARD_WIDTH; x++)
        drawVerticalLine(renderer, left + x*CELL_SIZE, top, BOARD_HEIGHT);
    for (int y = 0; y <= BOARD_HEIGHT; y++)
        drawHorizontalLine(renderer, left, top+y * CELL_SIZE, BOARD_WIDTH);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_Rect rect1;
    rect1.x=2*CELL_SIZE;
    rect1.y=5*CELL_SIZE;
    rect1.w=5*CELL_SIZE;
    rect1.h=8*CELL_SIZE;
    SDL_RenderDrawRect(renderer, &rect1);

    rect1.x += 20*CELL_SIZE;
    SDL_RenderDrawRect(renderer, &rect1);

    rect1.x=8*CELL_SIZE;
    rect1.y=6*CELL_SIZE;
    rect1.w=13*CELL_SIZE;
    rect1.h=6*CELL_SIZE;
    SDL_RenderDrawRect(renderer, &rect1);

    rect1.x=7*CELL_SIZE;
    rect1.y=12*CELL_SIZE;
    rect1.w=2*CELL_SIZE;
    rect1.h=CELL_SIZE;
    SDL_RenderDrawRect(renderer, &rect1);

    rect1.x += 13*CELL_SIZE;
    rect1.y -= 7*CELL_SIZE;
    SDL_RenderDrawRect(renderer, &rect1);

    SDL_SetRenderDrawColor(renderer, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b, 255);
    SDL_RenderDrawLine(renderer, 7*CELL_SIZE, 12*CELL_SIZE, 7*CELL_SIZE, 13*CELL_SIZE);

    SDL_SetRenderDrawColor(renderer,255,0,0,0);
    SDL_RenderFillRect(renderer, &tmpRect);
    player.position.update();
    player.update();
    player.render(renderer);
    SDL_RenderPresent(renderer);
}

