#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <SDL2/SDL.h>

class GameState;

class UIElement {
    public:
        UIElement(int x, int y, int w, int h) {
            init(x,y,w,h);
        }
        virtual ~UIElement() {};
        virtual void OnClick(GameState* gameState) {};
        virtual void OnRelease(GameState* gameState) {};
        virtual void OnHover(GameState* gameState) {};
        virtual void OnHoverOff(GameState* gameState) {};
        virtual void Draw(Renderer* renderer) {
            printf("Draw UI Element Base\n");
        };
        bool InBounds(int x, int y) {
            if (x >= rect.x && x < rect.x + rect.w) {
                if (y >= rect.y && y < rect.y + rect.h) {
                    return true;
                }
            }

            return false;
        };
    
    protected:
        void init(int x, int y, int w, int h) {
            rect.x = x;
            rect.y = y;
            rect.w = w;
            rect.h = h;
        };
        SDL_Rect rect;

};

#endif