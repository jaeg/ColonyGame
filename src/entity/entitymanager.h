#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <deque>
#include <string>
#include "../component/componentmanager.h"

#define MAX_ENTITIES 50

class EntityManager {
    public:
        EntityManager();
        int CreateEntity();
        bool EntityExists(int id) {
            auto it = std::find(entities_.begin(), entities_.end(), id);
            return it == entities_.end();
        };
        void DestroyEntity(int id);
        IComponentManager* GetComponentManager(std::string name) {
            return componentManagers_.at(name);
        };
        void AddComponentManager(std::string name, IComponentManager* cm) {
            componentManagers_.insert(std::pair<std::string, IComponentManager*>(name, cm));
        };
    private:
        std::deque<int> entities_;
        std::map<std::string, IComponentManager*> componentManagers_;

};

#endif