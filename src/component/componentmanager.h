#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H
#include <map>

class IComponentManager {
    public:
    virtual ~IComponentManager() {};
    virtual void DeleteComponentFor(int entityId){};
    
    template<typename T> 
    T* GetAs() {
        return (T*) this;
    };
    
};

template <typename T>
class ComponentManager: public IComponentManager {
    public:
        ComponentManager() {
            
        };

        void AddComponentTo(int entityId, std::shared_ptr<T> component) {
            auto it = components_.find(entityId); 
            if (it != components_.end())
                it->second = component;
            else
                components_.insert(std::pair<int, std::shared_ptr<T>>(entityId, component));
        };

        std::shared_ptr<T> GetComponentFor(int entityId) {
            auto it = components_.find(entityId); 
            if (it != components_.end())
                return components_.at(entityId);
            else
                return nullptr;
        };

        bool HasComponentFor(int entityId) {
            return components_.find(entityId) != components_.end();
        };

        void DeleteComponentFor(int entityId) {
            if (components_.find(entityId) != components_.end()) {
                components_.erase(entityId);
            }
        }

        std::map<int, std::shared_ptr<T>> GetAll() {
            return components_;
        };
    private:
        std::map<int, std::shared_ptr<T>> components_;
};

#endif