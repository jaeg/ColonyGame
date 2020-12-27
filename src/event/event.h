#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
    public:
        virtual ~Event() {
            printf("Destroyed Event\n");
        };
        virtual std::string GetType() { return "base";};
};

#endif
