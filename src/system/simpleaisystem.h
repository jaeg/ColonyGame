#ifndef SIMPLEAISYSTEM_H
#define SIMPLEAISYSTEM_H
#include <SDL2/SDL.h>
#include <stdio.h>

#include "system.h"
#include "../component/components.h"
#include "../event/eventlistener.h"
#include "../event/event.h"
#include "../world/level.h"

class SimpleAISystem: public System, public EventListener {
    public:
        SimpleAISystem(Level *level) {
            level_ = level;
        };
        void Update() {
            ComponentManager<PositionComponent>* spcm = (ComponentManager<PositionComponent>*) GetComponentManager("PositionComponent");
            ComponentManager<WanderAIComponent>* wanderAIcm = (ComponentManager<WanderAIComponent>*) GetComponentManager("WanderAIComponent");

            for (auto c : wanderAIcm->GetAll())
            {
                auto pc = spcm->GetComponentFor(c.first);
                int direction = rand() % 5;
                int oldX = pc->X;
                int oldY = pc->Y;

                if (direction == 0) {
                    pc->X++;
                } else if (direction == 1) {
                    pc->X--;
                } else if (direction == 2) {
                    pc->Y++;
                } else if (direction == 3){
                    pc->Y--;
                }

                if ( pc->X < 0 || pc->X > level_->GetWidth()) {
                    pc->X = oldX;
                }

                if ( pc->Y < 0 || pc->Y > level_->GetHeight()) {
                    pc->Y = oldY;
                }
            }
        };

        void HandleEvent(std::shared_ptr<Event> event) {
        };
    private:
    Level* level_;
};

#endif