#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
    public:
        virtual ~Event() {
        };
        virtual std::string GetType() { return "base";};
};


class InputEvent: public Event {
    public:
        const Uint8 *KeyBoardState;
        std::string GetType() { return "InputEvent";};
};

#endif
