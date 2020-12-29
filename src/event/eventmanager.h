#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <map>
#include <string>

#include "eventlistener.h"
#include "event.h"

class EventManager {
    public:
        void SendEvent(std::shared_ptr<Event> e) {
            std::string type = e->GetType();
            std::multimap<std::string, EventListener*>::iterator it,itlow,itup;
            itlow = registeredListeners_.lower_bound (type);  // itlow points to b
            itup = registeredListeners_.upper_bound (type);   // itup points to e (not d)

            // print range [itlow,itup):
            for (it = itlow; it!=itup; ++it)
                it->second->HandleEvent(e);
        }

        void RegisterListener(std::string eventType, EventListener* listener) {
            registeredListeners_.insert(std::make_pair(eventType, listener));
        }
    private:
        std::multimap<std::string, EventListener*> registeredListeners_;
};

#endif