#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include <stack>

#include "event.h"

// A simple EventListener base class that uses a stack to handle events.

class EventListener {
    public:
        virtual ~EventListener() {};
        void GiveEvent(std::shared_ptr<Event> event) {
            events_.push(event);
        };

        //By default push even to internal event stack.
        virtual void HandleEvent(std::shared_ptr<Event> event) {
            printf("Base Handler");
            events_.push(event);
        };

        std::shared_ptr<Event> GetTopEvent() {
            std::shared_ptr<Event> e = events_.top();
            events_.pop();
            return e;
        };
    private:
        std::stack<std::shared_ptr<Event>> events_;

};

#endif
