#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H
#define TILE_SIZE 32

#include "system.h"
#include "../resourcemanager.h"
#include "../renderer.h"
#include "../component/components.h"
#include "../event/eventlistener.h"
#include "../event/event.h"

class RenderSystem: public System, public EventListener {
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
        void HandleEvent(std::shared_ptr<Event> event) {
            if (event->GetType() == "InputEvent") {
                ComponentManager<PositionComponent>* pcm = (ComponentManager<PositionComponent>*) GetComponentManager("PositionComponent");
                for (auto c : pcm->GetAll())
                {
                    auto pc = c.second;
                    std::shared_ptr<InputEvent> ie = std::dynamic_pointer_cast<InputEvent>(event);

                    if ( ie->KeyBoardState[SDL_SCANCODE_1] ) {
                        ZoomLevel = 1;
                    }

                    if ( ie->KeyBoardState[SDL_SCANCODE_2] ) {
                        ZoomLevel = 2;
                    }
                    
                    if ( ie->KeyBoardState[SDL_SCANCODE_3] ) {
                        ZoomLevel = 3;
                    }

                }
            }
        };
    private:
        Renderer* renderer_;
        ResourceManager* resourceManager_;
        
};

#endif