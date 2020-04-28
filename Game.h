#ifndef game_h
#define game_h
#include "SDL.h"
#include <cstring>
#include <iostream>
#include "player.h"
#include "Position.h"
#include "TextureManager.h"
using namespace std;

enum GameStatus {
    GAME_RUNNING = 1,
    GAME_STOP = 2,
    GAME_WON = 4 | GAME_STOP,
    GAME_OVER = 8 | GAME_STOP,
};


class Game {
    GameStatus status=GAME_RUNNING;
    SDL_Renderer* renderer;


public:
    Game();
    ~Game();

    void handleEvents();
    void update();
    void render();

    bool isGameRunning() const { return (status == GAME_RUNNING); }
private:


};

#endif // game_h
