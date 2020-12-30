#ifndef PLAYERSYSTEM_H
#define PLAYERSYSTEM_H
#include <SDL2/SDL.h>
#include "system.h"
#include "../component/components.h"
#include "../event/event_listener.h"
#include "../event/event.h"

class PlayerSystem: public System, public EventListener {
    public:
        PlayerSystem() {
            playerID_ = 0;
        };
        void Update() {
        };

        void HandleEvent(std::shared_ptr<Event> event) {
            if (event->GetType() == "MouseInputEvent") {
                std::shared_ptr<MouseInputEvent> ie = std::dynamic_pointer_cast<MouseInputEvent>(event);
                if (ie->state == SDL_BUTTON_LEFT) {
                    printf("Left clicked!\n");
                }
            }
            if (event->GetType() == "KeyboardInputEvent") {
                ComponentManager<PositionComponent>* pcm = (ComponentManager<PositionComponent>*) GetComponentManager("PositionComponent");
                ComponentManager<PlayerComponent>* playercm = (ComponentManager<PlayerComponent>*) GetComponentManager("PlayerComponent");

                for (auto c : playercm->GetAll())
                {
                    auto pc = pcm->GetComponentFor(c.first);
                    std::shared_ptr<KeyboardInputEvent> ie = std::dynamic_pointer_cast<KeyboardInputEvent>(event);

                    if ( ie->KeyBoardState[SDL_SCANCODE_W] ) {
                        pc->Y--;
                    }

                    if ( ie->KeyBoardState[SDL_SCANCODE_A] ) {
                        pc->X--;
                    }

                    if ( ie->KeyBoardState[SDL_SCANCODE_S] ) {
                        pc->Y++;
                    }

                    if ( ie->KeyBoardState[SDL_SCANCODE_D] ) {
                        pc->X++;
                    }
                }
            }
        };
    private:
        int playerID_;
};

#endif