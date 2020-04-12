#ifndef player__h
#define player__h
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "TextureManager.h"
#include "Position.h"

class Player {
    Position position;
    int size = 10;
    int stepX=0, stepY=0;
    SDL_Renderer* renderer;
    SDL_Texture* playerTex;

public:
    ~Player() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(playerTex);
    }
    void render(SDL_Renderer* renderer);
    bool isInside(int minX, int minY, int maxX, int maxY);
    void move();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
};

#endif // player__h
