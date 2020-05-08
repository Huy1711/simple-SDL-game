#include "Menu.h"

Menu::Menu(SDL_Renderer *ren){
    renderer = ren;
    BGText = Gallery::loadTexture("VNU.jpg", renderer);
    font = TTF_OpenFont("foo.ttf", 40);
    screenRect.x = 0;
    screenRect.y = 0;
    screenRect.w = 900;
    screenRect.h = 600;

    menuRect[PLAY].x = 670;
    menuRect[PLAY].y = 450;
    menuRect[PLAY].w = 200;
    menuRect[PLAY].h = 50;

    menuRect[QUIT].x = 670;
    menuRect[QUIT].y = 500;
    menuRect[QUIT].w = 100;
    menuRect[QUIT].h = 50;
}

Menu::~Menu() {
    SDL_DestroyRenderer(renderer);
    for(SDL_Texture* p : menuText)
        SDL_DestroyTexture(p);
    SDL_DestroyTexture(BGText);
    TTF_CloseFont(font);
}

void Menu::renderBackground(SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, BGText, NULL, &screenRect);
}

void Menu::loadQuitOption(){
    SDL_Surface *quitSurface = TTF_RenderText_Solid(font, "Quit", textColor[QUIT]);
    menuText[QUIT] = SDL_CreateTextureFromSurface(renderer, quitSurface);
    SDL_FreeSurface(quitSurface);
}

void Menu::loadPlayOption(){
    SDL_Surface *playSurface = TTF_RenderText_Solid(font, "Play Game!", textColor[PLAY]);
    menuText[PLAY] = SDL_CreateTextureFromSurface(renderer, playSurface);
    SDL_FreeSurface(playSurface);
}

void Menu::renderOption() {
    getMouseEvent();
    loadQuitOption();
    loadPlayOption();
    SDL_RenderCopy(renderer, menuText[QUIT], NULL, &menuRect[QUIT]);
    SDL_RenderCopy(renderer, menuText[PLAY], NULL, &menuRect[PLAY]);
    SDL_DestroyTexture(menuText[QUIT]);
    SDL_DestroyTexture(menuText[PLAY]);
}

bool Menu::mouseIsInside(const int &x, const int &y, const SDL_Rect &rect) {
    if (x>=rect.x && x<=rect.x + rect.w &&
        y>=rect.y && y<=rect.y + rect.h)
        return true;
    return false;
}

void Menu::getMouseEvent() {
    int xm = 0, ym = 0;
    SDL_Event mouseEvent;
    while(SDL_PollEvent(&mouseEvent)) {
        switch(mouseEvent.type) {
            case SDL_QUIT: return;
            case SDL_MOUSEMOTION:
                xm = mouseEvent.motion.x;
                ym = mouseEvent.motion.y;
                for(int i=0; i<OPTION_COUNT; i++) {
                    if(mouseIsInside(xm, ym, menuRect[i])) {
                        if(focus[i]==false) {
                            focus[i]=true;
                            textColor[i] = RED_COLOR;
                        }
                    } else {
                        if(focus[i]==true) {
                            focus[i]=false;
                            textColor[i] = BLACK_COLOR;
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                xm = mouseEvent.button.x;
                ym = mouseEvent.button.y;
                for(int i=0; i<OPTION_COUNT; i++) {
                    if(mouseIsInside(xm, ym, menuRect[i])) {
                        selected[i] = true;
                    }
                }
        }
    }
}
