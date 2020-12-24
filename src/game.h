#ifndef GAME_H
#define GAME_H

#include "world/level.h"
#include "renderer.h"
#include "resourcemanager.h"

class Game {
    public:
        Game(Renderer* renderer) {
            currentLevel_ = new Level(100,100);
            renderer_ = renderer;
            resourceManager_ = new ResourceManager(renderer_);

            //Load resources
            resourceManager_->LoadTexture("tileset","assets/tiny_galaxy_world.png");
        };
        void Draw();
        void DrawView(int aX, int aY, int width, int height, bool centered);
    private:
        Renderer* renderer_;
        ResourceManager* resourceManager_;
        Level* currentLevel_;
};

#endif