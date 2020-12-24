//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>

#include "game.h"
#include "renderer.h"
#include "input.h"
#include "components/PositionComponent.h"
#include "entity.h"

int mX = 0;
int mY = 0;

void testSomething() {
    Entity entity;
    entity.AddComponent(new PositionComponent());
    if (entity.HasComponent("PositionComponent")) {
        printf("Has component\n");
    }
}

int main( int argc, char* args[] )
{
    printf( "Start!\n" );

    testSomething();

    
    //The window we'll be rendering to
    Renderer *renderer = new Renderer();
    renderer->Init();
    Input *input = new Input();

    Game *game = new Game(renderer);

    //Main loop
    while(!input->Escape) {
        input->PollEvents();
        renderer->StartDraw();
        game->DrawView(0,0,100,100,false);
        renderer->Draw();
    }  
  
    printf( "End\n" );
    return 0;
}