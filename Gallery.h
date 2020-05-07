#ifndef GALLERY_H
#define GALLERY_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "SDL_utils.h"
using namespace std;

enum PictureID {
    GROUND=0, TOP_WALL, BOTTOM_WALL, LEFT_WALL, RIGHT_WALL,
    TOP_RIGHT_CORNER, TOP_LEFT_CORNER, BOT_RIGHT_CORNER, BOT_LEFT_CORNER,
    U_TOP, U_BOTTOM, U_LEFT, U_RIGHT,
    LR_PARALLEL, TB_PARALLEL,
    FULL, OBTACLE, PIC_COUNT
};

enum SoundID {
    MOVING = 0, HIT_ENEMY, LEVEL_PASS, SOUND_COUNT
};

const SDL_Color BOARD_COLOR = {0, 0, 0};
const SDL_Color LINE_COLOR = {128, 128, 128};

class Gallery
{
    SDL_Texture* pictures[PIC_COUNT];
    Mix_Chunk* sounds[SOUND_COUNT];


public:
    string textOut;
    string strValue;
    unsigned int timeValue;
    SDL_Color textColor = {204,255,255};
    TTF_Font *font;
    SDL_Texture *textTexture;
    SDL_Rect textRect;
    SDL_Surface *time;

    SDL_Texture *deathCountText;
    SDL_Rect deathCountRect;

    SDL_Texture *levelText;
    SDL_Rect levelRect;

    SDL_Renderer* renderer;
    Gallery(SDL_Renderer* renderer_);
    ~Gallery();
//    void setText(const std::string& text) {textOut = text;}
    void loadGameText(int frameStart);
    static SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
    void loadGameSounds();
    void loadGamePictures();
    void renderTimeAndDeath(int frameStart, int deaths, int level);
    void loadDeathCount(int deaths);
    void loadLevelCount(int level);
    SDL_Texture* getImage(PictureID id) const { return pictures[id]; }
    Mix_Chunk* getSound(SoundID id) const { return sounds[id]; }
};

#endif // GALLERY_H
