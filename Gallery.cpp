#include "Gallery.h"
#include "SDL_utils.h"
#include <SDL_image.h>

Gallery::Gallery(SDL_Renderer* renderer_)
    : renderer(renderer_)
{
    loadGamePictures();
}

Gallery::~Gallery()
{
    for (SDL_Texture* texture : pictures)
        SDL_DestroyTexture(texture);
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

}

