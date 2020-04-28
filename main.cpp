#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <SDL.h>
#include "SDL_utils.h"
#include "TextureManager.h"
#include "Map.h"
#include "player.h"
#include "Game.h"
#include "Goal.h"
#include "Enemy.h"
using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "My Game";

const int BOARD_WIDTH = 30;
const int BOARD_HEIGHT = 30;
const int CELL_SIZE = 30;

const int ROWS = SCREEN_WIDTH/BOARD_WIDTH;
const int COLUMNS = SCREEN_HEIGHT/BOARD_HEIGHT;

const SDL_Color BOARD_COLOR = {0, 0, 0};
const SDL_Color LINE_COLOR = {128, 128, 128};

void interpretEvent(SDL_Event e, Game& game, Player &player, bool map1[COLUMNS][ROWS]);
void renderGamePlay(SDL_Renderer* renderer, const Game& game, Player &player, Enemy &enemy, Goal &goal, Enemy &enemy2, Enemy &enemy3, Enemy &enemyType2);
void drawVerticalLine(SDL_Renderer* renderer, int left, int top, int cells);
void drawHorizontalLine(SDL_Renderer* renderer, int left, int top, int cells);
void drawWall(SDL_Renderer* renderer);
void horizontalEnemy(Enemy &enemy);
bool playerHitEnemy(Player &player, Enemy &enemy, Enemy &enemy2, Enemy &enemy3);
void chasingEnemy(Enemy &enemy, const Player &player);

int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_HEIGHT, SCREEN_WIDTH, WINDOW_TITLE);
    Game game;
    SDL_Event e;


    const int fps = 60;         // let's make game youtube chanel
    const int frameDelay = 1000/fps;
    unsigned int frameStart;
    int frameTime;

    frameStart = SDL_GetTicks();
    Player player(renderer, 4, 8);
    Enemy enemy(renderer, 7, 6);
    Enemy enemy2(renderer, 20, 8);
    Enemy enemy3(renderer, 7, 10);
    Enemy enemyType2(renderer, 20, 6);
    Goal goal(renderer, 23, 7);

    while(!player.checkCollision(goal.goalRect)) {
        interpretEvent(e, game, player, map1);
        horizontalEnemy(enemy);
        horizontalEnemy(enemy2);
        horizontalEnemy(enemy3);
        chasingEnemy(enemyType2, player);
        if (playerHitEnemy(player, enemy, enemy2, enemy3))
            player.setPosition(4, 8);

        cout << player.position.x << " " << player.position.y << endl;
        //hitWall(player, tmpRect);
        renderGamePlay(renderer, game, player, enemy, goal, enemy2, enemy3, enemyType2);


        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
        SDL_Delay(100);
    }
    player.setPosition(4, 8);
    player.update();
    while(!player.checkCollision(goal.goalRect)) {
        interpretEvent(e, game, player, map1);
        horizontalEnemy(enemy);
        horizontalEnemy(enemy2);
        horizontalEnemy(enemy3);
        playerHitEnemy(player, enemy, enemy2, enemy3);

        cout << player.position.x << " " << player.position.y << endl;
        //hitWall(player, tmpRect);
        renderGamePlay(renderer, game, player, enemy, goal, enemy2, enemy3, enemyType2);


        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
        SDL_Delay(50);
    }

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

void interpretEvent(SDL_Event e, Game& game, Player &player, bool map1[COLUMNS][ROWS])
{
    while (SDL_PollEvent(&e)){
        if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    if (player.position.y > 0
                        && !map1[player.position.y-1][player.position.x])
                        player.move(UP);
                    break;
                case SDLK_DOWN:
                    if (player.position.y < COLUMNS-1
                        && !map1[player.position.y+1][player.position.x])
                        player.move(DOWN);
                    break;
                case SDLK_LEFT:
                    if (player.position.x > 0
                        && !map1[player.position.y][player.position.x-1])
                        player.move(LEFT);
                    break;
                case SDLK_RIGHT:
                    if (player.position.x < ROWS-1
                        && !map1[player.position.y][player.position.x+1])
                        player.move(RIGHT);
                    break;
            }
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

void drawCell(SDL_Renderer* renderer, Position pos, SDL_Texture* texture)
{
	SDL_Rect cell;
	cell.x = pos.x * CELL_SIZE + 5;
	cell.y = pos.y * CELL_SIZE + 5;
	cell.w = CELL_SIZE-10;
	cell.h = CELL_SIZE-10;
	SDL_RenderCopy(renderer, texture, NULL, &cell);
}

void drawWall(SDL_Renderer* renderer)
{
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

}

void renderGamePlay(SDL_Renderer* renderer, const Game& game, Player &player, Enemy &enemy, Goal &goal, Enemy &enemy2, Enemy &enemy3, Enemy &enemyType2) {
    int top = 0, left = 0;
    SDL_SetRenderDrawColor(renderer, BOARD_COLOR.r, BOARD_COLOR.g, BOARD_COLOR.b, 0);
    SDL_RenderClear(renderer);

    for (int x = 0; x <= BOARD_WIDTH; x++)
        drawVerticalLine(renderer, left + x*CELL_SIZE, top, BOARD_HEIGHT);
    for (int y = 0; y <= BOARD_HEIGHT; y++)
        drawHorizontalLine(renderer, left, top+y * CELL_SIZE, BOARD_WIDTH);

    drawWall(renderer);

    enemy.update();
    enemy2.update();
    enemy3.update();
    enemyType2.update();

    player.update();
    enemy.render(renderer);
    enemy2.render(renderer);
    enemy3.render(renderer);
    enemyType2.render(renderer);
    player.render(renderer);
    goal.render(renderer);
    SDL_RenderPresent(renderer);
}

void horizontalEnemy(Enemy &enemy) {
    enemy.move(RIGHT);
    if (map1[enemy.enemyPos.y][enemy.enemyPos.x]) {
            enemy.move(LEFT);
            enemy.speed*=-1;
    }
}

bool playerHitEnemy(Player &player, Enemy &enemy, Enemy &enemy2, Enemy &enemy3) {
    return (player.checkCollision(enemy.enemyRect) || player.checkCollision(enemy2.enemyRect) || player.checkCollision(enemy3.enemyRect));
}

void chasingEnemy(Enemy &enemy, const Player &player) {
    int distanceX = abs(player.position.x - enemy.enemyPos.x);
    int distanceY = abs(player.position.y - enemy.enemyPos.y);
    if (enemy.enemyPos.x <= player.position.x && enemy.enemyPos.y > player.position.y) {
        if(distanceX>=distanceY && !map1[enemy.enemyPos.y][enemy.enemyPos.x+1])
            enemy.move(RIGHT);
        else if (distanceX<distanceY && !map1[enemy.enemyPos.y-1][enemy.enemyPos.x])
            enemy.move(UP);
    } else if(enemy.enemyPos.x > player.position.x && enemy.enemyPos.y >= player.position.y) {
        if(distanceX>=distanceY && !map1[enemy.enemyPos.y][enemy.enemyPos.x-1])
            enemy.move(LEFT);
        else if (distanceX<distanceY && !map1[enemy.enemyPos.y-1][enemy.enemyPos.x])
            enemy.move(UP);
    } else if (enemy.enemyPos.x >= player.position.x && enemy.enemyPos.y < player.position.y) {
        if(distanceX>=distanceY && !map1[enemy.enemyPos.y][enemy.enemyPos.x-1])
            enemy.move(LEFT);
        else if (distanceX<distanceY && !map1[enemy.enemyPos.y+1][enemy.enemyPos.x])
            enemy.move(DOWN);
    } else if (enemy.enemyPos.x < player.position.x && enemy.enemyPos.y <= player.position.y) {
        if(distanceX>=distanceY && !map1[enemy.enemyPos.y][enemy.enemyPos.x+1])
            enemy.move(RIGHT);
        else if (distanceX<distanceY && !map1[enemy.enemyPos.y+1][enemy.enemyPos.x])
            enemy.move(DOWN);
    }
}
