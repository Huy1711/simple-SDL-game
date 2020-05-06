#ifndef game_h
#define game_h
#include "SDL.h"
#include <cstring>
#include <iostream>
#include "player.h"
#include "Position.h"
#include "Gallery.h"

using namespace std;

class Game {
    SDL_Renderer* renderer;

public:
    Game();
    ~Game();

    void update();
    void render();

private:


};

#endif // game_h
