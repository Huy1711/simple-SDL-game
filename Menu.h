#ifndef MENU_H
#define MENU_H

#include <SDL_ttf.h>
#include <SDL_image.h>

class Menu {
    SDL_Renderer* renderer;
    SDL_Texture* playerTex;
    SDL_Rect screen;
    SDL_Surface *menu;
    SDL_Color textColor = {204,255,255};
    TTF_Font *font;
public:
    Menu();
    ~Menu();





};
#endif // MENU_H
