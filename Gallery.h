#ifndef GALLERY_H
#define GALLERY_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <SDL_mixer.h>
#include "SDL_utils.h"
#include "Game.h"

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

class Gallery
{
    SDL_Texture* pictures[PIC_COUNT];
    Mix_Chunk* sounds[SOUND_COUNT];

public:
    SDL_Renderer* renderer;
    Gallery(SDL_Renderer* renderer_);
    ~Gallery();
    static SDL_Texture* loadTexture(std::string path, SDL_Renderer* renderer);
    void loadGameSounds();
    void loadGamePictures();
    SDL_Texture* getImage(PictureID id) const { return pictures[id]; }
    Mix_Chunk* getSound(SoundID id) const { return sounds[id]; }
};

#endif // GALLERY_H
