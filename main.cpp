#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <SDL.h>
#include "SDL_utils.h"
#include "Gallery.h"
#include "Map.h"
#include "player.h"
#include "Goal.h"
#include "Enemy.h"
#include "ChasingEnemy.h"
#include "BulletEnemy.h"
#include "Menu.h"
using namespace std;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "VNU Game";

const int BOARD_WIDTH = 30;
const int BOARD_HEIGHT = 30;
//const int CELL_SIZE = 30;

const int ROWS = SCREEN_WIDTH/BOARD_WIDTH;
const int COLUMNS = SCREEN_HEIGHT/BOARD_HEIGHT;

void interpretEvent(SDL_Event e, Player &player, int map[COLUMNS][ROWS]);
void renderGameplay(SDL_Renderer* renderer);
void renderLevel1(SDL_Renderer* renderer, Player &player, Goal &goal);
void renderLevel2(SDL_Renderer* renderer, Player &player, Goal &goal, SDL_Rect &rect1, SDL_Rect &rect2);
void renderLevel3(SDL_Renderer* renderer, Player &player, Enemy &enemy, Goal &goal, Enemy &enemy2, Enemy &enemy3);
void renderLevel4(SDL_Renderer* renderer, Player &player, Enemy &enemy, Goal &goal, Enemy &enemy2, Enemy &enemy3, ChasingEnemy &enemyType2);
void renderLevel5(SDL_Renderer* renderer, Player &player, Goal &goal, ChasingEnemy &enemy1, ChasingEnemy &enemy2);
void renderLevel6(SDL_Renderer* renderer, Player &player, Goal &goal, ChasingEnemy &enemy1, ChasingEnemy &enemy2, ChasingEnemy &enemy3);
void renderLevel7(SDL_Renderer* renderer, Player &player, Goal &goal, ChasingEnemy &enemy1, ChasingEnemy &enemy2, ChasingEnemy &enemy3, BulletEnemy &enemy4);
void renderLevel8(SDL_Renderer* renderer, Player &player, Goal &goal, ChasingEnemy &enemy1, ChasingEnemy &enemy2, ChasingEnemy &enemy3, BulletEnemy &enemy4, BulletEnemy &enemy5);
bool playerHitEnemy2(Player &player, SDL_Rect &rect1, SDL_Rect &rect2);
bool playerHitEnemy3(Player &player, Enemy &enemy, Enemy &enemy2, Enemy &enemy3);
bool playerHitEnemy4(Player &player, Enemy &enemy, Enemy &enemy2, Enemy &enemy3, ChasingEnemy &enemyType2);
bool playerHitEnemy5(Player &player, ChasingEnemy &enemy, ChasingEnemy &enemy2);
bool playerHitEnemy6(Player &player, ChasingEnemy &enemy, ChasingEnemy &enemy2, ChasingEnemy &enemy3);
bool playerHitEnemy7(Player &player, ChasingEnemy &enemy, ChasingEnemy &enemy2, ChasingEnemy &enemy3, BulletEnemy &enemy4);
bool playerHitEnemy8(Player &player, ChasingEnemy &enemy, ChasingEnemy &enemy2, ChasingEnemy &enemy3, BulletEnemy &enemy4, BulletEnemy &enemy5);
void drawVerticalLine(SDL_Renderer* renderer, int left, int top, int cells);
void drawHorizontalLine(SDL_Renderer* renderer, int left, int top, int cells);
void drawWall(SDL_Renderer* renderer, int map[COLUMNS][ROWS]);
void renderSplashScreen(Menu &menu, SDL_Renderer *renderer);
void renderClock(SDL_Renderer *renderer, int frameStart, int deaths, int level);
bool passLevel(int &level, Player &player, Goal &goal);
void setFirstPosition(Player &player);

Gallery* gallery = nullptr; // global picture manager
Map map;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_HEIGHT, SCREEN_WIDTH, WINDOW_TITLE);

    gallery = new Gallery(renderer);
    SDL_Event e;

    const int fps = 30;         // let's make game youtube chanel
    const int frameDelay = 1000/fps;
    unsigned int frameStart;
    int frameTime;
    Menu menu(renderer);
    Player player(renderer, 150, 240);
    Goal goal(renderer, 690, 210);
    map.loadMap("map12.txt");
    int level = 1;

    while(!menu.selected[PLAY]) {
        renderSplashScreen(menu, renderer);
        if(menu.selected[QUIT]) {
            delete gallery;
            quitSDL(window, renderer);
        }
    }
    frameStart = SDL_GetTicks();
    //Level 1
    while(!passLevel(level, player, goal)) {
        interpretEvent(e, player, map.map);
        renderLevel1(renderer, player, goal);
        renderClock(renderer, frameStart, player.deaths, level);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    //Level 2
    player.setPosition(150, 240);
    SDL_Rect rect1;
    rect1.x = 270;
    rect1.y = 210;
    rect1.h = 150;
    rect1.w = 150;
    SDL_Rect rect2;
    rect2.x = 480;
    rect2.y = 150;
    rect2.h = 150;
    rect2.w = 150;
    while(!passLevel(level, player, goal)) {
        interpretEvent(e, player, map.map);
        renderLevel2(renderer, player, goal, rect1, rect2);
        renderClock(renderer, frameStart, player.deaths, level);
        if (playerHitEnemy2(player, rect1, rect2))
            setFirstPosition(player);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    map.loadMap("map34.txt");
    //Level 3
    player.setPosition(120, 240);
    Enemy enemy(renderer, 599, 180);
    Enemy enemy2(renderer, 240, 240);
    Enemy enemy3(renderer, 599, 300);
    while(!passLevel(level, player, goal)) {
        interpretEvent(e, player, map.map);
        enemy.horizontalMoving(map.map);
        enemy2.horizontalMoving(map.map);
        enemy3.horizontalMoving(map.map);

        if (playerHitEnemy3(player, enemy, enemy2, enemy3))
            setFirstPosition(player);
        renderLevel3(renderer, player, enemy, goal, enemy2, enemy3);
        renderClock(renderer, frameStart, player.deaths, level);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    //Level 4
    player.setPosition(120, 240);
    ChasingEnemy enemyType2(renderer, 600, 180);

    while(!passLevel(level, player, goal)) {
        interpretEvent(e, player, map.map);
        enemy.horizontalMoving(map.map);
        enemy2.horizontalMoving(map.map);
        enemy3.horizontalMoving(map.map);
        enemyType2.chasingEnemy(player, map.map);
        if (playerHitEnemy4(player, enemy, enemy2, enemy3, enemyType2))
            setFirstPosition(player);
        renderLevel4(renderer, player, enemy, goal, enemy2, enemy3, enemyType2);
        renderClock(renderer, frameStart, player.deaths, level);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    map.loadMap("map5678.txt");
    //Level 5
    player.setPosition(120, 240);
    ChasingEnemy CEnemy1(renderer, 600, 100);
    ChasingEnemy CEnemy2(renderer, 600, 300);

    while(!passLevel(level, player, goal)) {
        interpretEvent(e, player, map.map);
        CEnemy1.chasingEnemy(player, map.map);
        CEnemy2.chasingEnemy(player, map.map);
        if(playerHitEnemy5(player, CEnemy1, CEnemy2))
            setFirstPosition(player);
        renderLevel5(renderer, player, goal, CEnemy1, CEnemy2);
        renderClock(renderer, frameStart, player.deaths, level);
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

    while(!passLevel(level, player, goal)) {
        interpretEvent(e, player, map.map);
        CEnemy1.chasingEnemy(player, map.map);
        CEnemy2.chasingEnemy(player, map.map);
        CEnemy3.chasingEnemy(player, map.map);
        goal.movingGoal(player, map.map);
        if(playerHitEnemy6(player, CEnemy1, CEnemy2, CEnemy3))
            setFirstPosition(player);
        renderLevel6(renderer, player, goal, CEnemy1, CEnemy2, CEnemy3);
        renderClock(renderer, frameStart, player.deaths, level);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    //Level 7
    player.setPosition(120, 240);
    goal.setPosition(690, 210);
    CEnemy1.setPosition(600, 200);
    CEnemy2.setPosition(600, 300);
    CEnemy2.setPosition(600, 500);
    BulletEnemy BEnemy(renderer, 150, 30);
    while(!passLevel(level, player, goal)) {
        interpretEvent(e, player, map.map);
        CEnemy1.chasingEnemy(player, map.map);
        CEnemy2.chasingEnemy(player, map.map);
        CEnemy3.chasingEnemy(player, map.map);
        BEnemy.bulletMoving(player, map.map);
        goal.movingGoal(player, map.map);
        if(playerHitEnemy7(player, CEnemy1, CEnemy2, CEnemy3, BEnemy))
            setFirstPosition(player);
        renderLevel7(renderer, player, goal, CEnemy1, CEnemy2, CEnemy3, BEnemy);
        renderClock(renderer, frameStart, player.deaths, level);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    //Level 8
    player.setPosition(120, 240);
    goal.setPosition(690, 210);
    CEnemy1.setPosition(600, 200);
    CEnemy2.setPosition(600, 300);
    CEnemy2.setPosition(600, 500);
    BEnemy.setPosition(90, 300);
    BulletEnemy BEnemy2(renderer, 200, 30);
    while(!passLevel(level, player, goal)) {
        interpretEvent(e, player, map.map);
        CEnemy1.chasingEnemy(player, map.map);
        CEnemy2.chasingEnemy(player, map.map);
        CEnemy3.chasingEnemy(player, map.map);
        BEnemy.bulletMoving(player, map.map);
        BEnemy2.bulletMoving(player, map.map);
        goal.movingGoal(player, map.map);
        if(playerHitEnemy8(player, CEnemy1, CEnemy2, CEnemy3, BEnemy, BEnemy2))
            setFirstPosition(player);
        renderLevel8(renderer, player, goal, CEnemy1, CEnemy2, CEnemy3, BEnemy, BEnemy2);
        renderClock(renderer, frameStart, player.deaths, level);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Congrat!", "You win", NULL);
    waitUntilKeyPressed();
    delete gallery;
    quitSDL(window, renderer);
    return 0;
}

bool passLevel(int &level, Player &player, Goal &goal) {
    if (player.checkCollision(goal.goalRect)) {
        Mix_PlayChannel(-1, gallery->getSound(LEVEL_PASS), 0);
        level++;
    }
    return (player.checkCollision(goal.goalRect));
}

void interpretEvent(SDL_Event e, Player &player, int map[COLUMNS][ROWS])
{
    while (SDL_PollEvent(&e)){
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    Mix_PlayChannel(-1, gallery->getSound(MOVING), 0);
                    if (player.canMove(UP, map))
                        player.move(UP);
                    break;
                case SDLK_DOWN:
                    Mix_PlayChannel(-1, gallery->getSound(MOVING), 0);
                    if (player.canMove(DOWN, map))
                        player.move(DOWN);
                    break;
                case SDLK_LEFT:
                    Mix_PlayChannel(-1, gallery->getSound(MOVING), 0);
                    if (player.canMove(LEFT, map))
                        player.move(LEFT);
                    break;
                case SDLK_RIGHT:
                    Mix_PlayChannel(-1, gallery->getSound(MOVING), 0);
                    if (player.canMove(RIGHT, map))
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

void renderClock(SDL_Renderer *renderer, int frameStart, int deaths, int level) {
    gallery->renderTimeAndDeath(frameStart, deaths, level);
    SDL_RenderPresent(renderer);
}

void renderSplashScreen(Menu &menu, SDL_Renderer *renderer)
{
    menu.renderBackground(renderer);
    menu.renderOption();
    SDL_RenderPresent(renderer);

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

void renderGameplay(SDL_Renderer* renderer) {
    // int top=0, left=0;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    /*
    for (int x = 0; x <= BOARD_WIDTH; x++)
        drawVerticalLine(renderer, left + x*CELL_SIZE, top, BOARD_HEIGHT);
    for (int y = 0; y <= BOARD_HEIGHT; y++)
        drawHorizontalLine(renderer, left, top+y * CELL_SIZE, BOARD_WIDTH);
    */
}

void renderLevel1(SDL_Renderer* renderer, Player &player, Goal &goal) {
    renderGameplay(renderer);
    drawWall(renderer, map.map);
    goal.render(renderer);
    player.render(renderer);
}

void renderLevel2(SDL_Renderer* renderer, Player &player, Goal &goal, SDL_Rect &rect1, SDL_Rect &rect2) {
    renderGameplay(renderer);
    drawWall(renderer, map.map);
    goal.render(renderer);
    SDL_RenderCopy(renderer, gallery->getImage(OBTACLE), NULL, &rect1);
    SDL_RenderCopy(renderer, gallery->getImage(OBTACLE), NULL, &rect2);
    player.render(renderer);
}

void renderLevel3(SDL_Renderer* renderer, Player &player, Enemy &enemy, Goal &goal, Enemy &enemy2, Enemy &enemy3) {
    renderGameplay(renderer);
    drawWall(renderer, map.map);
    goal.render(renderer);
    enemy.render(renderer);
    enemy2.render(renderer);
    enemy3.render(renderer);
    player.render(renderer);
}

void renderLevel4(SDL_Renderer* renderer, Player &player, Enemy &enemy, Goal &goal, Enemy &enemy2, Enemy &enemy3, ChasingEnemy &enemyType2) {
    renderGameplay(renderer);
    drawWall(renderer, map.map);
    goal.render(renderer);
    enemy.render(renderer);
    enemy2.render(renderer);
    enemy3.render(renderer);
    enemyType2.render(renderer);
    player.render(renderer);
}

void renderLevel5(SDL_Renderer* renderer, Player &player, Goal &goal, ChasingEnemy &enemy1, ChasingEnemy &enemy2) {
    renderGameplay(renderer);
    drawWall(renderer, map.map);
    goal.render(renderer);
    enemy1.render(renderer);
    enemy2.render(renderer);
    player.render(renderer);
}

void renderLevel6(SDL_Renderer* renderer, Player &player, Goal &goal, ChasingEnemy &enemy1, ChasingEnemy &enemy2, ChasingEnemy &enemy3) {
    renderGameplay(renderer);
    drawWall(renderer, map.map);
    goal.render(renderer);
    enemy1.render(renderer);
    enemy2.render(renderer);
    enemy3.render(renderer);
    player.render(renderer);
}

void renderLevel7(SDL_Renderer* renderer, Player &player, Goal &goal, ChasingEnemy &enemy1, ChasingEnemy &enemy2, ChasingEnemy &enemy3, BulletEnemy &enemy4) {
    renderGameplay(renderer);
    drawWall(renderer, map.map);
    goal.render(renderer);
    enemy1.render(renderer);
    enemy2.render(renderer);
    enemy3.render(renderer);
    enemy4.render(renderer);
    player.render(renderer);
}

void renderLevel8(SDL_Renderer* renderer, Player &player, Goal &goal, ChasingEnemy &enemy1, ChasingEnemy &enemy2, ChasingEnemy &enemy3, BulletEnemy &enemy4, BulletEnemy &enemy5) {
    renderGameplay(renderer);
    drawWall(renderer, map.map);
    goal.render(renderer);
    enemy1.render(renderer);
    enemy2.render(renderer);
    enemy3.render(renderer);
    enemy4.render(renderer);
    enemy5.render(renderer);
    player.render(renderer);
}

bool playerHitEnemy2(Player &player, SDL_Rect &rect1, SDL_Rect &rect2) {
    return (player.checkCollision(rect1) || player.checkCollision(rect2));
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

bool playerHitEnemy7(Player &player, ChasingEnemy &enemy, ChasingEnemy &enemy2, ChasingEnemy &enemy3, BulletEnemy &enemy4) {
    return (player.checkCollision(enemy.enemyRect) || player.checkCollision(enemy2.enemyRect) || player.checkCollision(enemy3.enemyRect)
            || player.checkCollision(enemy4.enemyRect));
}

bool playerHitEnemy8(Player &player, ChasingEnemy &enemy, ChasingEnemy &enemy2, ChasingEnemy &enemy3, BulletEnemy &enemy4, BulletEnemy &enemy5) {
    return (player.checkCollision(enemy.enemyRect) || player.checkCollision(enemy2.enemyRect) || player.checkCollision(enemy3.enemyRect)
            || player.checkCollision(enemy4.enemyRect) || player.checkCollision(enemy5.enemyRect));
}

void setFirstPosition(Player &player) {
    player.setPosition(120, 240);
    player.deaths++;
    Mix_PlayChannel(-1, gallery->getSound(HIT_ENEMY), 0);
}
