#ifndef PLAYERSYSTEM_H
#define PLAYERSYSTEM_H
#include <SDL2/SDL.h>
#include "system.h"
#include "../component/components.h"
#include "../event/event_listener.h"
#include "../event/event.h"

class InputEvent: public Event {
    public:
        const Uint8 *KeyBoardState;
        std::string GetType() { return "InputEvent";};
};

class PlayerSystem: public System, public EventListener {
    public:
        PlayerSystem() {
            playerID_ = 0;
        };
        void Update() {
        };

        void HandleEvent(std::shared_ptr<Event> event) {
            printf("%s\n", event->GetType().c_str());
            if (event->GetType() == "InputEvent") {
                ComponentManager<PositionComponent>* pcm = (ComponentManager<PositionComponent>*) GetComponentManager("PositionComponent");
                for (auto c : pcm->GetAll())
                {
                    auto pc = c.second;
                    std::shared_ptr<InputEvent> ie = std::dynamic_pointer_cast<InputEvent>(event);

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