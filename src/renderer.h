#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "world/tile.h"
#include <string>
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Renderer {
    public:
        Renderer() {
            this->window_ = nullptr;
            this->renderer_ = nullptr;
            printf("Created renderer\n");
        };
        void Init();
        void Draw();
        void StartDraw();
        void Cleanup();
        void DrawSprite(int dX,int dY, int dW, int dH, int sX, int sY, int sW, int sH, SDL_Texture* texture);
        void DrawRect(SDL_Rect rect) {
            SDL_RenderFillRect( renderer_, &rect );
        };

        void DrawRectColored(SDL_Rect rect, int r, int g, int b) {
            SDL_SetRenderDrawColor( renderer_, r, g, b, 255 );
            SDL_RenderFillRect( renderer_, &rect );
            SDL_SetRenderDrawColor( renderer_, 255, 255, 255, 255 );
        };
        SDL_Texture* CreateTexture(SDL_Surface* surface);
        
    private:
        SDL_Window* window_;
        SDL_Renderer* renderer_;

};

#endif