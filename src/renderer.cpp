#include "renderer.h"
#include <iostream>

void Renderer::Init() {
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window_ = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window_ == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
           else
        {
            printf("Created Window\n");
            renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
            }
        }
    }
}

void Renderer::StartDraw() {
    // clear the screen
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderClear(renderer_);
} 

void Renderer::Draw() {
    // flip the backbuffer
    // this means that everything that we prepared behind the screens is actually shown
    SDL_RenderPresent(renderer_);
    SDL_Delay(100);
}

void Renderer::Cleanup() {
    //Destroy window
    SDL_DestroyWindow( window_ );

    //Quit SDL subsystems
    SDL_Quit();

}

 void Renderer::DrawSprite(int dX,int dY, int dW, int dH, int sX, int sY, int sW, int sH, SDL_Texture* texture) {
    SDL_Rect rect = SDL_Rect(); // the rectangle
    rect.x = dX;
    rect.y = dY;
    rect.h = dH;
    rect.w = dW;

    SDL_Rect sourceRect = SDL_Rect();
    sourceRect.x = sX;
    sourceRect.y = sY;
    sourceRect.h = sH;
    sourceRect.w = sW;
    SDL_RenderCopy(renderer_, texture, &sourceRect, &rect);
 }

SDL_Texture* Renderer::CreateTexture(SDL_Surface* surface) {
    SDL_Texture* newTexture = NULL;
    newTexture = SDL_CreateTextureFromSurface( renderer_, surface );
    if( newTexture == NULL )
    {
        printf( "Unable to create texture! SDL Error: %s\n", SDL_GetError() );
    }

    return newTexture;
}