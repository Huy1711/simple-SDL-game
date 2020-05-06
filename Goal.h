#ifndef goal__h
#define goal__h
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Gallery.h"
#include "Position.h"
#include "Game.h"
using namespace std;

class Game;

class Goal {

    SDL_Renderer* renderer;
    SDL_Texture* goalTex;

public:
    Position position;
    SDL_Rect goalRect;
    int speed = 5;

    Goal(SDL_Renderer* ren, int x, int y);
    ~Goal() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(goalTex);
    }
    void update();
    void setPosition(int x, int y);
    void render(SDL_Renderer* renderer);
    void move(Direction direction);
    bool canMove(Direction direction, int map[20][30]);
    void movingGoal(const Player &player, int map[20][30]);
};

#endif
