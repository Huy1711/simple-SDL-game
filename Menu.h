#ifndef MENU_H
#define MENU_H

#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Gallery.h"

enum MenuOption {
    PLAY = 0, QUIT, OPTION_COUNT
};

const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color RED_COLOR = {150, 0, 0};

class Menu {
    SDL_Renderer* renderer;
    SDL_Texture* BGText;
    SDL_Texture* menuText[OPTION_COUNT];
    SDL_Rect screenRect;
    SDL_Rect menuRect[OPTION_COUNT];
    SDL_Color textColor[OPTION_COUNT] = {BLACK_COLOR, BLACK_COLOR};
    TTF_Font *font;
    bool focus[OPTION_COUNT] = {false, false};

public:
    bool selected[OPTION_COUNT] = {false, false};
    Menu(SDL_Renderer *ren);
    ~Menu();
    void getMouseEvent();
    void renderBackground(SDL_Renderer *renderer);
    void loadQuitOption();
    void loadPlayOption();
    void renderOption();
    bool mouseIsInside(const int &x, const int &y, const SDL_Rect &rect);

};
#endif // MENU_H
