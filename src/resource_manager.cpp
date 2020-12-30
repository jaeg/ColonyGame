#include "resource_manager.h"

SDL_Texture* ResourceManager::GetTexture(std::string name) {
    return textures[name];
}

bool ResourceManager::LoadTexture( std::string name, std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        newTexture = renderer_->CreateTexture(loadedSurface);
        SDL_FreeSurface( loadedSurface );
    }

    if (newTexture == NULL) {
        printf( "Unable to create texture from %s! \n", path.c_str());
        return false;
    }

    textures[name] = newTexture;

    return true;
}