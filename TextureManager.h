#ifndef TextureManager__h
#define TextureManager__h
#include <SDL.h>
#include <string>
#include <iostream>
#include <SDL_image.h>
#include <stdlib.h>
#include "SDL_utils.h"


class TextureManager
{
    SDL_Renderer* renderer;


public:
    TextureManager(SDL_Window* window, SDL_Renderer* renderer);

    SDL_Texture* loadTexture( std::string path );
    bool createImage( SDL_Texture* texture );
};


#endif // TextureManager__h
