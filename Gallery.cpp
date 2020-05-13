#include "Gallery.h"
#include "SDL_utils.h"
#include <SDL_image.h>

Gallery::Gallery(SDL_Renderer* renderer_)
    : renderer(renderer_)
{
    loadGamePictures();
    loadGameSounds();
    font = TTF_OpenFont("foo.ttf", 24);
    textRect.x = 400;
    textRect.y = 0;
    textRect.w = 50;
    textRect.h = 30;

    deathCountRect.x = 700;
    deathCountRect.y = 0;
    deathCountRect.w = 70;
    deathCountRect.h = 30;

    levelRect.x = 90;
    levelRect.y = 0;
    levelRect.w = 60;
    levelRect.h = 30;

}

Gallery::~Gallery()
{
    for (SDL_Texture* texture : pictures)
        SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(font);
    for (Mix_Chunk* mix : sounds)
        Mix_FreeChunk(mix);

}

SDL_Texture* Gallery::loadTexture(std::string path, SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        logSDLError(std::cout, "Unable to load image " + path + " SDL_image Error: " + IMG_GetError());
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            logSDLError(std::cout, "Unable to create texture from " + path + " SDL Error: " + SDL_GetError());
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void Gallery::loadGamePictures()
{
    pictures[TOP_WALL] = loadTexture("WallPic\\top.jpg", renderer);
    pictures[BOTTOM_WALL] = loadTexture("WallPic\\bottom.jpg", renderer);
    pictures[LEFT_WALL] = loadTexture("WallPic\\left.jpg", renderer);
    pictures[RIGHT_WALL] = loadTexture("WallPic\\right.jpg", renderer);
    pictures[TOP_RIGHT_CORNER] = loadTexture("WallPic\\TRcorner.jpg", renderer);
    pictures[TOP_LEFT_CORNER] = loadTexture("WallPic\\TLcorner.jpg", renderer);
    pictures[BOT_RIGHT_CORNER] = loadTexture("WallPic\\BRcorner.jpg", renderer);
    pictures[BOT_LEFT_CORNER] = loadTexture("WallPic\\BLcorner.jpg", renderer);
    pictures[U_TOP] = loadTexture("WallPic\\Utop.jpg", renderer);
    pictures[U_BOTTOM] = loadTexture("WallPic\\Ubottom.jpg", renderer);
    pictures[U_LEFT] = loadTexture("WallPic\\Uleft.jpg", renderer);
    pictures[U_RIGHT] = loadTexture("WallPic\\Uright.jpg", renderer);
    pictures[LR_PARALLEL] = loadTexture("WallPic\\lrParallel.jpg", renderer);
    pictures[TB_PARALLEL] = loadTexture("WallPic\\tbParallel.jpg", renderer);
    pictures[FULL] = loadTexture("WallPic\\full.jpg", renderer);
    pictures[OBTACLE] = loadTexture("hus.jpg", renderer);

}

void Gallery::loadGameSounds() {
    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4*1024) == -1) return;

    sounds[MOVING] = Mix_LoadWAV("move.wav");
    sounds[HIT_ENEMY] = Mix_LoadWAV("enemyHit.wav");
    sounds[LEVEL_PASS] = Mix_LoadWAV("warp.wav");
}

void Gallery::loadGameText(int frameStart){
    textOut = "";
    strValue = "";
    timeValue = SDL_GetTicks()/1000 - frameStart/1000;
    int minute = timeValue/60;
    int second = timeValue - minute*60;
    strValue += to_string(minute);
    strValue += ":";
    strValue += to_string(second);
    textOut += strValue;

    SDL_Surface *time = TTF_RenderText_Solid(font, textOut.c_str(), textColor);
    textTexture = SDL_CreateTextureFromSurface(renderer, time);
    SDL_FreeSurface(time);

}

void Gallery::loadDeathCount(int deaths){
    textOut = "Fails: ";
    strValue = "";
    strValue += to_string(deaths);
    textOut += strValue;
    SDL_Surface *deathCountSurface = TTF_RenderText_Solid(font, textOut.c_str(), textColor);
    deathCountText = SDL_CreateTextureFromSurface(renderer, deathCountSurface);
    SDL_FreeSurface(deathCountSurface);
}

void Gallery::loadLevelCount(int level){
    textOut = "Level ";
    strValue = "";
    strValue += to_string(level);
    textOut += strValue;
    SDL_Surface *levelSurface = TTF_RenderText_Solid(font, textOut.c_str(), textColor);
    levelText = SDL_CreateTextureFromSurface(renderer, levelSurface);
    SDL_FreeSurface(levelSurface);
}


void Gallery::renderTimeAndDeath(int frameStart, int deaths, int level) {
    loadGameText(frameStart);
    loadDeathCount(deaths);
    loadLevelCount(level);
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderCopy(renderer, deathCountText, NULL, &deathCountRect);
    SDL_RenderCopy(renderer, levelText, NULL, &levelRect);
    SDL_DestroyTexture(textTexture);
    SDL_DestroyTexture(deathCountText);
    SDL_DestroyTexture(levelText);
}
