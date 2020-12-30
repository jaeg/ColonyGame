#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "renderer.h"

class ResourceManager {
    public:
        ResourceManager(Renderer* renderer) {
            renderer_ = renderer;
        };
        bool LoadTexture( std::string name, std::string path );
        SDL_Texture* GetTexture(std::string name);
    private:
        std::map<std::string, SDL_Texture*> textures;
        Renderer* renderer_;
};

#endif
