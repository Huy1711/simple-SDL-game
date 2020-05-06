#ifndef player__h
#define player__h
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Gallery.h"
#include "Position.h"
#include "Game.h"
using namespace std;

class Game;

class Player {

    int size = 30;
    SDL_Renderer* renderer;
    SDL_Texture* playerTex;
    int speed = 30;

public:
    Position position;
    SDL_Rect playerRect;

    Player(SDL_Renderer* ren, int x, int y);
    ~Player() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(playerTex);
    }
    void setPosition(int x, int y);
    void update();
    void render(SDL_Renderer* renderer);
    bool canMove(Direction direction, int map[20][30]);
    void move(Direction direction);
    bool checkCollision(const SDL_Rect &b);
    //void hitWall(SDL_Rect wall);
};

#endif // player__h
