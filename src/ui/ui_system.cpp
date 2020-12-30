#include "ui_system.h"

void UISystem::HandleInput(SDL_Event e, GameState* gameState) {
            int x, y;
            SDL_GetMouseState( &x, &y );
            for (UIElement* el : elements) {
                if (el->InBounds(x,y)) {
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        el->OnClick(gameState);
                    } else if (e.type == SDL_MOUSEBUTTONUP) {
                        el->OnRelease(gameState);
                    } else {
                        el->OnHover(gameState);
                    }
                } else {
                    el->OnHoverOff(gameState);
                }
            }
        };
void UISystem::Draw() {
    for (UIElement* el : elements) {
        el->Draw(renderer_);
    }
};

void UISystem::AddElement(UIElement* element) {
    elements.push_back(element);
}