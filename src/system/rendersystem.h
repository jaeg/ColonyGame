#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H
#define TILE_SIZE 32

#include "system.h"
#include "../resourcemanager.h"
#include "../renderer.h"
#include "../component/components.h"

class RenderSystem: public System {
    public:
        RenderSystem(Renderer* renderer, ResourceManager* resourceManager) {
            renderer_ = renderer;
            resourceManager_ = resourceManager;
        };
        void Update() {
            ComponentManager<PositionComponent>* spcm = (ComponentManager<PositionComponent>*) GetComponentManager("PositionComponent");
            ComponentManager<AppearanceComponent>* accm = (ComponentManager<AppearanceComponent>*) GetComponentManager("AppearanceComponent");

            for (auto c : accm->GetAll())
            {
                auto ac = c.second;
                auto pc = spcm->GetComponentFor(c.first);
                renderer_->DrawSprite(pc->X*getTileSize(), pc->Y*getTileSize(), getTileSize(), getTileSize(), ac->SpriteX, ac->SpriteY, 16, 16, resourceManager_->GetTexture("characters"));
            }
        };
        int ZoomLevel = 1;
        int getTileSize() {
            if (ZoomLevel <= 0) {
                ZoomLevel = 1;
                printf("Fixed bad zoom level\n");
            }
            int tileSize = TILE_SIZE / ZoomLevel;
            return tileSize;
        };
    private:
        Renderer* renderer_;
        ResourceManager* resourceManager_;
        
};

#endif