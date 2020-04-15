#ifndef game_h
#define game_h
#include "SDL.h"
#include <iostream>

enum GameStatus {
    GAME_RUNNING = 1,
    GAME_STOP = 2,
    GAME_WON = 4 | GAME_STOP,
    GAME_OVER = 8 | GAME_STOP,
};

class Game {
    GameStatus status;
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    Game();
    ~Game();

    void handleEvents();
    void update();
    void render();

    bool isGameRunning() const { return status == GAME_RUNNING; }
private:


};


#endif // game_h
