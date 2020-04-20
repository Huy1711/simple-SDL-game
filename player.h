#ifndef player__h
#define player__h
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "TextureManager.h"
#include "Position.h"
using namespace std;

class Game;

class Player {

    int size = 30;
    SDL_Renderer* renderer;
    SDL_Texture* playerTex;
    SDL_Rect playerRect;

public:
    Position position;

    Player(SDL_Renderer* ren, int x, int y);
    ~Player() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(playerTex);
    }
    void update();
    void render(SDL_Renderer* renderer);
    void move(Direction direction);
    bool checkCollision( SDL_Rect b );
};

#endif // player__h

