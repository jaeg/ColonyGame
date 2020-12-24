#ifndef UISYSTEM_H
#define UISYSTEM_H

#include <SDL2/SDL.h>
#include <list>
#include "../renderer.h"
#include "uielement.h"

class GameState;

class UISystem {
    public:
        UISystem(Renderer* renderer) {
            renderer_ = renderer;
        }
        void HandleInput(SDL_Event, GameState* gameState);
        void Draw();
       
        void AddElement(UIElement* element);
    
    private:
        std::list<UIElement*> elements;
        Renderer* renderer_;
};

#endif
