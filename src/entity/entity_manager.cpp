#include "entity_manager.h"


int EntityManager::CreateEntity() {
    //Don't exceed the max number of entities.
    if (entities_.size() == 0) {
        return -1;
    }

    int i = entities_.top();
    entities_.pop();
    usedIds_.insert(i);

    return i;   
};

void EntityManager::DestroyEntity(int id) {
    if  (usedIds_.find(id) != usedIds_.end()) {
        entities_.push(id); 
        usedIds_.erase(id);
        for (auto it : componentManagers_)
            {
                auto cm = it.second;
                cm->DeleteComponentFor(id);
            }
    } else {
        printf("Entity already destroyed\n");
    }
};

EntityManager::EntityManager() {
    //Populate the available ids
    for (int i = MAX_ENTITIES; i > 0; i--) {
        entities_.push(i);
    }
};