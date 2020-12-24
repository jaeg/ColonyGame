#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <cstdlib>
#include <list>

#include "components/component.h"

class Entity {
    public:
        float x;
        float y;
        int targetX;
        int targetY;
        int direction;
        double velocity;
        virtual void Update(int tick);

        void AddComponent(Component* component) {
            components.push_back(component);
        };

        bool HasComponent(std::string name) {
            for (Component* c : components) {
                if (c->GetType() == name) {
                    return true;
                }
            }
            return false;
        };

        Entity() {   
        };
        virtual ~Entity() {
            printf("Entity Deleted\n");
            Cleanup();
        }
        void Cleanup() {
            //Delete all the components
            for (Component* c : components) {
                delete c;
            }
            components.clear();
        }
    private:
        std::list<Component*> components;
};
#endif