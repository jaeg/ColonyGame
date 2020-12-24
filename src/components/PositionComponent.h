#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include <string>
#include "component.h"

class PositionComponent: public Component {
    public:
        int x, y;
        virtual std::string GetType() {
            return "PositionComponent";
        };
};

#endif