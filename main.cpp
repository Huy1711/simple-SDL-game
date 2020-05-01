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
#include "ChasingEnemy.h"
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

bool canMove(Direction direction, Position const &position, bool map[COLUMNS][ROWS]);
void interpretEvent(SDL_Event e, Game& game, Player &player, bool map1[COLUMNS][ROWS]);
void renderGamePlay(SDL_Renderer* renderer, const Game& game, Player &player, Enemy &enemy, Goal &goal, Enemy &enemy2, Enemy &enemy3, ChasingEnemy &enemyType2);
void drawVerticalLine(SDL_Renderer* renderer, int left, int top, int cells);
void drawHorizontalLine(SDL_Renderer* renderer, int left, int top, int cells);
void drawWall(SDL_Renderer* renderer);
void horizontalEnemy(Enemy &enemy);
bool playerHitEnemy(Player &player, Enemy &enemy, Enemy &enemy2, Enemy &enemy3, ChasingEnemy &enemyType2);
void chasingEnemy(ChasingEnemy &enemy, const Player &player);

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
    Player player(renderer, 120, 240);
    Enemy enemy(renderer, 240, 180);
    Enemy enemy2(renderer, 599, 240);
    Enemy enemy3(renderer, 240, 300);
    ChasingEnemy enemyType2(renderer, 600, 180);
    Goal goal(renderer, 23, 7);

    while(!player.checkCollision(goal.goalRect)) {
        interpretEvent(e, game, player, map1);
        horizontalEnemy(enemy);
        horizontalEnemy(enemy2);
        horizontalEnemy(enemy3);
        chasingEnemy(enemyType2, player);
        if (playerHitEnemy(player, enemy, enemy2, enemy3, enemyType2))
            player.setPosition(120, 240);

        cout << player.position.x << " " << player.position.y << endl;
        renderGamePlay(renderer, game, player, enemy, goal, enemy2, enemy3, enemyType2);


        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    player.setPosition(120, 240);
    while(!player.checkCollision(goal.goalRect)) {
        interpretEvent(e, game, player, map1);
        horizontalEnemy(enemy);
        horizontalEnemy(enemy2);
        horizontalEnemy(enemy3);
        playerHitEnemy(player, enemy, enemy2, enemy3, enemyType2);

        cout << player.position.x << " " << player.position.y << endl;
        renderGamePlay(renderer, game, player, enemy, goal, enemy2, enemy3, enemyType2);


        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    player.setPosition(120, 240);
    while(!player.checkCollision(goal.goalRect)) {
        interpretEvent(e, game, player, map1);
        horizontalEnemy(enemy);
        horizontalEnemy(enemy2);
        horizontalEnemy(enemy3);
        playerHitEnemy(player, enemy, enemy2, enemy3, enemyType2);

        cout << player.position.x << " " << player.position.y << endl;
        renderGamePlay(renderer, game, player, enemy, goal, enemy2, enemy3, enemyType2);


        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    player.setPosition(120, 240);
    while(!player.checkCollision(goal.goalRect)) {
        interpretEvent(e, game, player, map1);
        horizontalEnemy(enemy);
        horizontalEnemy(enemy2);
        horizontalEnemy(enemy3);
        playerHitEnemy(player, enemy, enemy2, enemy3, enemyType2);

        cout << player.position.x << " " << player.position.y << endl;
        renderGamePlay(renderer, game, player, enemy, goal, enemy2, enemy3, enemyType2);


        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    player.setPosition(120, 240);
    while(!player.checkCollision(goal.goalRect)) {
        interpretEvent(e, game, player, map1);
        horizontalEnemy(enemy);
        horizontalEnemy(enemy2);
        horizontalEnemy(enemy3);
        playerHitEnemy(player, enemy, enemy2, enemy3, enemyType2);

        cout << player.position.x << " " << player.position.y << endl;
        renderGamePlay(renderer, game, player, enemy, goal, enemy2, enemy3, enemyType2);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

bool canMove(Direction direction, const Position &position, bool map[20][30]){
    switch(direction) {
        case LEFT: return (position.x > 0 && !map[position.y/30][(position.x)/30-1]);
        case RIGHT: return (position.x < 900-30 && !map[position.y/30][(position.x)/30+1]);
        case UP: return (position.y > 0 && !map[position.y/30-1][position.x/30]);
        case DOWN: return  (position.y < 600-30 && !map[position.y/30+1][position.x/30]);
    }
}

void interpretEvent(SDL_Event e, Game& game, Player &player, bool map1[COLUMNS][ROWS])
{
    while (SDL_PollEvent(&e)){
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    if (canMove(UP, player.position, map1))
                        player.move(UP);
                    break;
                case SDLK_DOWN:
                    if (canMove(DOWN, player.position, map1))
                        player.move(DOWN);
                    break;
                case SDLK_LEFT:
                    if (canMove(LEFT, player.position, map1))
                        player.move(LEFT);
                    break;
                case SDLK_RIGHT:
                    if (canMove(RIGHT, player.position, map1))
                        player.move(RIGHT);
                    break;
                /*
                case SDLK_r:
                    resetMap();
                    break;
                */
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

void renderGamePlay(SDL_Renderer* renderer, const Game& game, Player &player, Enemy &enemy, Goal &goal, Enemy &enemy2, Enemy &enemy3, ChasingEnemy &enemyType2) {
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
    if (map1[enemy.enemyPos.y/30][enemy.enemyPos.x/30+1]) {
            enemy.speed*=-1;
    }
    if (map1[enemy.enemyPos.y/30][(enemy.enemyPos.x+enemy.speed)/30]) {
            enemy.speed*=-1;
    }
}

bool playerHitEnemy(Player &player, Enemy &enemy, Enemy &enemy2, Enemy &enemy3, ChasingEnemy &enemyType2) {
    return (player.checkCollision(enemy.enemyRect) || player.checkCollision(enemy2.enemyRect) || player.checkCollision(enemy3.enemyRect)
            || player.checkCollision(enemyType2.enemyRect));
}

void chasingEnemy(ChasingEnemy &enemy, const Player &player) {
    int distanceX = abs(player.position.x - enemy.enemyPos.x);
    int distanceY = abs(player.position.y - enemy.enemyPos.y);
    if (enemy.enemyPos.x < player.position.x && enemy.enemyPos.y >= player.position.y) {
        if(distanceX<=distanceY && enemy.canMove(UP, map1))
            enemy.move(UP);
        else if (distanceX>distanceY && enemy.canMove(RIGHT, map1))
            enemy.move(RIGHT);
    } else if(enemy.enemyPos.x >= player.position.x && enemy.enemyPos.y > player.position.y) {
        if(distanceX<=distanceY && enemy.canMove(UP, map1))
            enemy.move(UP);
        else if (distanceX>distanceY && enemy.canMove(LEFT, map1))
            enemy.move(LEFT);
    } else if (enemy.enemyPos.x > player.position.x && enemy.enemyPos.y <= player.position.y) {
        if(distanceX<=distanceY && enemy.canMove(DOWN, map1))
            enemy.move(DOWN);
        else if (distanceX>distanceY && enemy.canMove(LEFT, map1))
            enemy.move(LEFT);
    } else if (enemy.enemyPos.x <= player.position.x && enemy.enemyPos.y < player.position.y) {
        if(distanceX<=distanceY && enemy.canMove(DOWN, map1))
            enemy.move(DOWN);
        else if (distanceX>distanceY && enemy.canMove(RIGHT, map1))
            enemy.move(RIGHT);
    }
}
