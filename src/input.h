#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>

class Input {
    public:
        bool Escape = false;
        void PollEvents() {
            SDL_Event e;

            while (SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT){
                    Escape = true;
                }
                if (e.type == SDL_KEYDOWN){
                    const Uint8 *state = SDL_GetKeyboardState(NULL); 
                    
                    if ( state[SDL_SCANCODE_ESCAPE] ) {
                        Escape = true;
                    }
                    
                }
            }
        }
};

#endif