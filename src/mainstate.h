#ifndef MAINSTATE_H
#define MAINSTATE_H

#include "gamestate.h"
#include "renderer.h"

#include "ui/uisystem.h"
#include "ui/button.h"

extern void TestButtonHandler(GameState* state);

class MainState: public GameState {
    public:
        MainState(Renderer* renderer) {
            currentLevel_ = new Level(100,100);
            renderer_ = renderer;
            resourceManager_ = new ResourceManager(renderer_);
            uiSystem_ = new UISystem(renderer_);

            //Load resources
            resourceManager_->LoadTexture("tileset","assets/tiny_galaxy_world.png");

            //UI
            Button* btn = new Button(60,0,50,50);
            btn->SetHandler(&TestButtonHandler);
            uiSystem_->AddElement(btn);
        }
        void Draw() {
            DrawView(0,0,100,100,false);
            uiSystem_->Draw();
        };

        void DrawView(int aX, int aY, int width, int height, bool centered) {
            int left = aX - width/2;
            int right = aX + width/2;
            int up = aY - height/2;
            int down = aY + height/2;

            if (centered == false) {
                left = aX;
                right = aX + width - 1;
                up = aY;
                down = aY + height;
            }

            for (int x = left; x <= right; x++) {
                for (int y = up; y <= down; y++) {
                    Tile tile = currentLevel_->GetTile(x,y);
                    if (tile.type == -1) {
                        renderer_->DrawSprite(x*16, y*16, 16, 16, 0, 0, 16, 16, resourceManager_->GetTexture("tileset"));
                    } else if (tile.type == 1) {
                        renderer_->DrawSprite(x*16, y*16, 16, 16, 0, 16, 16, 16, resourceManager_->GetTexture("tileset"));
                    } else if (tile.type == 2) {
                        renderer_->DrawSprite(x*16, y*16, 16, 16, 0, 32, 16, 16, resourceManager_->GetTexture("tileset"));
                    } else {
                        renderer_->DrawSprite(x*16, y*16, 16, 16, 0, 48, 16, 16, resourceManager_->GetTexture("tileset"));
                    }
                }
            }
        }

        void Update() {

        };

        void HandleInput(SDL_Event e) {
            if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONUP) {
                //Forward the event to the ui system.
                uiSystem_->HandleInput(e,this);
            };
        };
    private:
        ResourceManager* resourceManager_;
        UISystem* uiSystem_;
        Renderer* renderer_;
        Level* currentLevel_;
};

#endif