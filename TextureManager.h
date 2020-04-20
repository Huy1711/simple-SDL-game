#ifndef TextureManager__h
#define TextureManager__h
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "SDL_utils.h"
#include "Game.h"


class TextureManager
{
    SDL_Renderer* renderer;


public:
    TextureManager(SDL_Window* window, SDL_Renderer* renderer);
    ~TextureManager() { SDL_DestroyRenderer(renderer); }
    static SDL_Texture* loadTexture( std::string path, SDL_Renderer* renderer );
    bool createImage( SDL_Texture* texture );
};


#endif // TextureManager__h
