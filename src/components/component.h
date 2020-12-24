#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

class Component {
    public:
        Component() {
            printf("Created\n");
        };
        virtual ~Component() {
            printf("Component Deleted\n");
        }
        virtual std::string GetType() {
            return "Base";
        };
    
};

#endif