#ifndef SYSTEM_H
#define SYSTEM_H

#include <map>
#include <string>
#include "../component/componentmanager.h"

class System {
    public: 
        virtual ~System() {};
        virtual void Initialize() {};
        //Override to provide system functionality.
        virtual void Update() {};

        IComponentManager* GetComponentManager(std::string name) {
            auto it = componentManagers_.find(name); 
            if (it != componentManagers_.end())
                return componentManagers_.at(name);
            else
                return nullptr;
        };

        //Register the components that this system will care about.
        void RegisterComponentManager(std::string name, IComponentManager* cm) {
            auto it = componentManagers_.find(name); 
            if (it != componentManagers_.end())
                it->second = cm;
            else
                componentManagers_.insert(std::pair<std::string, IComponentManager*>(name, cm));
        };
    private:
        std::map<std::string, IComponentManager*> componentManagers_;
};

#endif