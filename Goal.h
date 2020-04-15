#ifndef goal__h
#define goal__h
#include <SDL.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "Position.h"

class Goal {
    Position position;
    int size = 10;
    int stepX=0, stepY=0;
    SDL_Renderer* renderer;
    SDL_Texture* playerTex;

public:
    ~Goal() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(playerTex);
    }
    void render(SDL_Renderer* renderer);

    void move();
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
};

#endif // goal__h
