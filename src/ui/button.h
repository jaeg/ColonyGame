#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include "ui_element.h"
#include "../renderer.h"

class Button: public UIElement {
    public:
        virtual ~Button() {};
        Button(int x, int y, int w, int h) : UIElement(x, y, w, h) {
            handler_ptr_ = nullptr;
        };

        void OnHover(GameState* gameState) {
            hover_ = true;
        }

        void OnHoverOff(GameState* gameState) {
            hover_ = false;
        }

        void OnClick(GameState* gameState) {
            printf("Button pressed!\n");
            pressed_ = true;
            if (handler_ptr_ != nullptr) {
                handler_ptr_(gameState);
            }
        };

        void OnRelease(GameState* gameState) {
            pressed_ = false;
            printf("Button Released!\n");
        };
        
        void Draw(Renderer* renderer) {
            if (pressed_) {
                renderer->DrawRectColored(rect,125,0,0);
            } else if (hover_) {
                renderer->DrawRectColored(rect,125,125,125);
            } else {
                renderer->DrawRect(rect);
            }
        };

        bool InBounds(int x, int y) {
            if (x >= rect.x && x < rect.x + rect.w) {
                if (y >= rect.y && y < rect.y + rect.h) {
                    return true;
                }
            }

            return false;
        };

        void SetHandler(void (*handler_ptr)(GameState*)) {
            handler_ptr_ = handler_ptr;
        };
    private:
        bool hover_;
        bool pressed_;
        void (*handler_ptr_)(GameState*); 
};

#endif