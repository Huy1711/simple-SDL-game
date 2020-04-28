#ifndef goal__h
#define goal__h
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "TextureManager.h"
#include "Position.h"
#include "Game.h"
using namespace std;

class Goal {

    SDL_Renderer* renderer;
    SDL_Texture* goalTex;

public:
    Position position;
    SDL_Rect goalRect;

    Goal(SDL_Renderer* ren, int x, int y);
    ~Goal() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(goalTex);
    }
    void update();
    void render(SDL_Renderer* renderer);
    //void move(Direction direction);
};

#endif


