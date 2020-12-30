#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <stack>
#include <set>
#include <string>
#include "../component/component_manager.h"

#define MAX_ENTITIES 50

class EntityManager {
    public:
        EntityManager();
        int CreateEntity();
        bool EntityExists(int id) {
            return usedIds_.find(id) != usedIds_.end();
        };
        void DestroyEntity(int id);

        template<typename T> 
         T* GetComponentManagerAs(std::string name) {
            return (T*)(componentManagers_.at(name));
        };

        IComponentManager* GetComponentManager(std::string name) {
            return componentManagers_.at(name);
        };
        void AddComponentManager(std::string name, IComponentManager* cm) {
            componentManagers_.insert(std::pair<std::string, IComponentManager*>(name, cm));
        };
    private:
        std::stack<int> entities_;
        std::map<std::string, IComponentManager*> componentManagers_;
        std::set<int> usedIds_; 

};

#endif