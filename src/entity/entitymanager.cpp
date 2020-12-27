#include "entitymanager.h"


int EntityManager::CreateEntity() {
    //Don't exceed the max number of entities.
    if (entities_.size() == 0) {
        return -1;
    }

    int i = entities_.front();
    entities_.pop_front();

    return i;   
};

void EntityManager::DestroyEntity(int id) {
    auto it = std::find(entities_.begin(), entities_.end(), id);
    if  (it == entities_.end()) {
        entities_.push_front(id); 

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
    for (int i = 0; i < MAX_ENTITIES; i++) {
        entities_.push_back(i);
    }
};