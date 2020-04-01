#ifndef SDL_UTILS__H
#define SDL_UTILS__H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
             int SCREEN_HEIGHT, int SCREEN_WIDTH, const std::string &WINDOW_TITLE);

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

#endif // SDL_UTILS__H
