#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <SDL.h>
#include "SDL_utils.h"
#include "Gallery.h"
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

bool canMove(Direction direction, Position const &position, int map[COLUMNS][ROWS]);
void interpretEvent(SDL_Event e, Player &player, int map1[COLUMNS][ROWS]);
void renderGameplay(SDL_Renderer* renderer);
void renderLevel1(SDL_Renderer* renderer, Player &player, Goal &goal);
void renderLevel3(SDL_Renderer* renderer, Player &player, Enemy &enemy, Goal &goal, Enemy &enemy2, Enemy &enemy3);
void renderLevel4(SDL_Renderer* renderer, Player &player, Enemy &enemy, Goal &goal, Enemy &enemy2, Enemy &enemy3, ChasingEnemy &enemyType2);
void renderLevel5(SDL_Renderer* renderer, Player &player, Goal &goal, ChasingEnemy &enemy1, ChasingEnemy &enemy2);
void renderLevel6(SDL_Renderer* renderer, Player &player, Goal &goal, ChasingEnemy &enemy1, ChasingEnemy &enemy2, ChasingEnemy &enemy3);
void drawVerticalLine(SDL_Renderer* renderer, int left, int top, int cells);
void drawHorizontalLine(SDL_Renderer* renderer, int left, int top, int cells);
void drawWall(SDL_Renderer* renderer, int map[COLUMNS][ROWS]);
void horizontalEnemy(Enemy &enemy, int map[COLUMNS][ROWS]);
bool playerHitEnemy3(Player &player, Enemy &enemy, Enemy &enemy2, Enemy &enemy3);
bool playerHitEnemy4(Player &player, Enemy &enemy, Enemy &enemy2, Enemy &enemy3, ChasingEnemy &enemyType2);
bool playerHitEnemy5(Player &player, ChasingEnemy &enemy, ChasingEnemy &enemy2);
bool playerHitEnemy6(Player &player, ChasingEnemy &enemy, ChasingEnemy &enemy2, ChasingEnemy &enemy3);
bool passLevel(Player &player, Goal &goal);

Gallery* gallery = nullptr; // global picture manager

int main(int argc, char* argv[])
{
    srand(time(0));
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_HEIGHT, SCREEN_WIDTH, WINDOW_TITLE);
    gallery = new Gallery(renderer);
    Game game;
    SDL_Event e;

    const int fps = 60;         // let's make game youtube chanel
    const int frameDelay = 1000/fps;
    unsigned int frameStart;
    int frameTime;

    frameStart = SDL_GetTicks();
    Player player(renderer, 120, 240);
    Goal goal(renderer, 690, 210);

    //Level 1
    while(!passLevel(player, goal)) {
        interpretEvent(e, player, map12);

        cout << player.position.x << " " << player.position.y << endl;
        renderLevel1(renderer, player, goal);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    //Level 2
    //Level 3
    player.setPosition(120, 240);
    Enemy enemy(renderer, 599, 180);
    Enemy enemy2(renderer, 240, 240);
    Enemy enemy3(renderer, 599, 300);

    while(!passLevel(player, goal)) {
        interpretEvent(e, player, map34);
        enemy.horizontalMoving(map34);
        enemy2.horizontalMoving(map34);
        enemy3.horizontalMoving(map34);
        if (playerHitEnemy3(player, enemy, enemy2, enemy3))
            player.setPosition(120, 240);

        cout << player.position.x << " " << player.position.y << endl;
        renderLevel3(renderer, player, enemy, goal, enemy2, enemy3);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    //Level 4
    player.setPosition(120, 240);
    ChasingEnemy enemyType2(renderer, 600, 180);

    while(!passLevel(player, goal)) {
        interpretEvent(e, player, map34);
        enemy.horizontalMoving(map34);
        enemy2.horizontalMoving(map34);
        enemy3.horizontalMoving(map34);
        enemyType2.chasingEnemy(player, map34);
        if (playerHitEnemy4(player, enemy, enemy2, enemy3, enemyType2))
            player.setPosition(120, 240);

        cout << player.position.x << " " << player.position.y << endl;
        renderLevel4(renderer, player, enemy, goal, enemy2, enemy3, enemyType2);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    //Level 5
    player.setPosition(120, 240);
    ChasingEnemy CEnemy1(renderer, 600, 100);
    ChasingEnemy CEnemy2(renderer, 600, 300);

    while(!passLevel(player, goal)) {
        interpretEvent(e, player, map567);
        CEnemy1.chasingEnemy(player, map567);
        CEnemy2.chasingEnemy(player, map567);
        if(playerHitEnemy5(player, CEnemy1, CEnemy2))
            player.setPosition(120, 240);

        cout << player.position.x << " " << player.position.y << endl;
        renderLevel5(renderer, player, goal, CEnemy1, CEnemy2);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    //Level 6
    player.setPosition(120, 240);
    CEnemy1.setPosition(600, 100);
    CEnemy2.setPosition(600, 300);
    ChasingEnemy CEnemy3(renderer, 600, 500);
    goal.setPosition(450, 300);

    while(!passLevel(player, goal)) {
        interpretEvent(e, player, map567);
        CEnemy1.chasingEnemy(player, map567);
        CEnemy2.chasingEnemy(player, map567);
        CEnemy3.chasingEnemy(player, map567);
        goal.movingGoal(player, map567);
        if(playerHitEnemy6(player, CEnemy1, CEnemy2, CEnemy3))
            player.setPosition(120, 240);

        cout << player.position.x << " " << player.position.y << endl;
        renderLevel6(renderer, player, goal, CEnemy1, CEnemy2, CEnemy3);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

bool passLevel(Player &player, Goal &goal) {
    return (player.checkCollision(goal.goalRect));
}

bool canMove(Direction direction, const Position &position, int map[20][30]){
    switch(direction) {
        case LEFT: return (position.x > 0 && map[position.y/30][(position.x)/30-1]==0);
        case RIGHT: return (position.x < 900-30 && map[position.y/30][(position.x)/30+1]==0);
        case UP: return (position.y > 0 && map[position.y/30-1][position.x/30]==0);
        case DOWN: return  (position.y < 600-30 && map[position.y/30+1][position.x/30]==0);
    }
}

void interpretEvent(SDL_Event e, Player &player, int map[COLUMNS][ROWS])
{
    while (SDL_PollEvent(&e)){
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    if (canMove(UP, player.position, map))
                        player.move(UP);
                    break;
                case SDLK_DOWN:
                    if (canMove(DOWN, player.position, map))
                        player.move(DOWN);
                    break;
                case SDLK_LEFT:
                    if (canMove(LEFT, player.position, map))
                        player.move(LEFT);
                    break;
                case SDLK_RIGHT:
                    if (canMove(RIGHT, player.position, map))
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

void drawCell(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture)
{
	SDL_Rect cell;
	cell.x = x * CELL_SIZE;
	cell.y = y * CELL_SIZE;
	cell.w = CELL_SIZE;
	cell.h = CELL_SIZE;
	SDL_RenderCopy(renderer, texture, NULL, &cell);
}

void drawWall(SDL_Renderer* renderer, int map[COLUMNS][ROWS])
{
    int left = 0, top = 0;
    int type = 0;
    for(int row=0; row<30; row++) {
        for(int column=0; column<20; column++) {
            type = map[column][row];
            switch(type) {
                case GROUND: break;
                case TOP_WALL: drawCell(renderer, row, column, gallery->getImage(TOP_WALL)); break;
                case BOTTOM_WALL: drawCell(renderer, row, column, gallery->getImage(BOTTOM_WALL)); break;
                case LEFT_WALL: drawCell(renderer, row, column, gallery->getImage(LEFT_WALL)); break;
                case RIGHT_WALL: drawCell(renderer, row, column, gallery->getImage(RIGHT_WALL)); break;
                case TOP_RIGHT_CORNER: drawCell(renderer, row, column, gallery->getImage(TOP_RIGHT_CORNER)); break;
                case TOP_LEFT_CORNER: drawCell(renderer, row, column, gallery->getImage(TOP_LEFT_CORNER)); break;
                case BOT_RIGHT_CORNER: drawCell(renderer, row, column, gallery->getImage(BOT_RIGHT_CORNER)); break;
                case BOT_LEFT_CORNER: drawCell(renderer, row, column, gallery->getImage(BOT_LEFT_CORNER)); break;
                case U_TOP: drawCell(renderer, row, column, gallery->getImage(U_TOP)); break;
                case U_BOTTOM: drawCell(renderer, row, column, gallery->getImage(U_BOTTOM)); break;
                case U_LEFT: drawCell(renderer, row, column, gallery->getImage(U_LEFT)); break;
                case U_RIGHT: drawCell(renderer, row, column, gallery->getImage(U_RIGHT)); break;
                case LR_PARALLEL: drawCell(renderer, row, column, gallery->getImage(LR_PARALLEL)); break;
                case TB_PARALLEL: drawCell(renderer, row, column, gallery->getImage(TB_PARALLEL)); break;
                case FULL: drawCell(renderer, row, column, gallery->getImage(FULL)); break;
            }

        }
    }
}

void renderGameplay(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    /*
    int top = 0, left = 0;
    for (int x = 0; x <= BOARD_WIDTH; x++)
        drawVerticalLine(renderer, left + x*CELL_SIZE, top, BOARD_HEIGHT);
    for (int y = 0; y <= BOARD_HEIGHT; y++)
        drawHorizontalLine(renderer, left, top+y * CELL_SIZE, BOARD_WIDTH);
    */
}

void renderLevel1(SDL_Renderer* renderer, Player &player, Goal &goal) {
    renderGameplay(renderer);
    drawWall(renderer, map12);
    goal.render(renderer);
    player.render(renderer);
    SDL_RenderPresent(renderer);
}

void renderLevel3(SDL_Renderer* renderer, Player &player, Enemy &enemy, Goal &goal, Enemy &enemy2, Enemy &enemy3) {
    renderGameplay(renderer);
    drawWall(renderer, map34);
    goal.render(renderer);
    enemy.render(renderer);
    enemy2.render(renderer);
    enemy3.render(renderer);
    player.render(renderer);

    SDL_RenderPresent(renderer);
}

void renderLevel4(SDL_Renderer* renderer, Player &player, Enemy &enemy, Goal &goal, Enemy &enemy2, Enemy &enemy3, ChasingEnemy &enemyType2) {
    renderGameplay(renderer);
    drawWall(renderer, map34);
    goal.render(renderer);
    enemy.render(renderer);
    enemy2.render(renderer);
    enemy3.render(renderer);
    enemyType2.render(renderer);
    player.render(renderer);

    SDL_RenderPresent(renderer);
}

void renderLevel5(SDL_Renderer* renderer, Player &player, Goal &goal, ChasingEnemy &enemy1, ChasingEnemy &enemy2) {
    renderGameplay(renderer);
    drawWall(renderer, map567);
    goal.render(renderer);
    enemy1.render(renderer);
    enemy2.render(renderer);
    player.render(renderer);

    SDL_RenderPresent(renderer);
}

void renderLevel6(SDL_Renderer* renderer, Player &player, Goal &goal, ChasingEnemy &enemy1, ChasingEnemy &enemy2, ChasingEnemy &enemy3) {
    renderGameplay(renderer);
    drawWall(renderer, map567);
    goal.render(renderer);
    enemy1.render(renderer);
    enemy2.render(renderer);
    enemy3.render(renderer);
    player.render(renderer);

    SDL_RenderPresent(renderer);
}

bool playerHitEnemy3(Player &player, Enemy &enemy, Enemy &enemy2, Enemy &enemy3) {
    return (player.checkCollision(enemy.enemyRect) || player.checkCollision(enemy2.enemyRect) || player.checkCollision(enemy3.enemyRect));
}

bool playerHitEnemy4(Player &player, Enemy &enemy, Enemy &enemy2, Enemy &enemy3, ChasingEnemy &enemyType2) {
    return (player.checkCollision(enemy.enemyRect) || player.checkCollision(enemy2.enemyRect) || player.checkCollision(enemy3.enemyRect)
            || player.checkCollision(enemyType2.enemyRect));
}

bool playerHitEnemy5(Player &player, ChasingEnemy &enemy, ChasingEnemy &enemy2) {
    return (player.checkCollision(enemy.enemyRect) || player.checkCollision(enemy2.enemyRect));
}

bool playerHitEnemy6(Player &player, ChasingEnemy &enemy, ChasingEnemy &enemy2, ChasingEnemy &enemy3) {
    return (player.checkCollision(enemy.enemyRect) || player.checkCollision(enemy2.enemyRect) || player.checkCollision(enemy3.enemyRect));
}
