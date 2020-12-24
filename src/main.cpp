//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>

#include "game.h"
#include "renderer.h"

int main( int argc, char* args[] )
{
    printf( "Start!\n" );


    //The window we'll be rendering to
    Renderer *renderer = new Renderer();
    renderer->Init();

    Game *game = new Game(renderer);

    //Main loop
    while(!game->Escape) {
        game->PollEvents();
        game->Update();
        game->Draw();
    }  
  
    printf( "End\n" );
    return 0;
}