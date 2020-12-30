#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
    public:
        virtual ~Event() {
        };
        virtual std::string GetType() { return "base";};
};


class KeyboardInputEvent: public Event {
    public:
        const Uint8 *KeyBoardState;
        std::string GetType() { return "KeyboardInputEvent";};
};

class MouseInputEvent: public Event {
    public:
        int X;
        int Y;
        Uint8 state;
        std::string GetType() { return "MouseInputEvent";};
};

#endif
