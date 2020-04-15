#include "TextureManager.h"

TextureManager::TextureManager (SDL_Window* window, SDL_Renderer* renderer_)
    : renderer(renderer_)
{
    int width, height;
    SDL_RenderGetLogicalSize(renderer, &width, &height);
    if (width == 0 && height == 0)
        SDL_GetWindowSize(window, &width, &height);

}

SDL_Texture* TextureManager::loadTexture( std::string path, SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        std::cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << std::endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            std::cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

bool TextureManager::createImage( SDL_Texture* texture )
{
    if( texture == NULL )
        return false;
    SDL_RenderCopy( renderer, texture, NULL, NULL );
    return true;
}

