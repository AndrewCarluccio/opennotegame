#include "EventDispatcher.h"


	EventDispatcher::EventDispatcher() {
        listeners = new unordered_map<string, vector<EventListener*>*>();

    }

	EventDispatcher::~EventDispatcher() {
        unordered_map<string, vector<EventListener*>*>::iterator it = listeners->begin();
        while (it != listeners->end()) {
            vector<EventListener*>::iterator it2 = it->second->begin();
            while (it2 != it->second->end()) {
                // delete *it2; // FIGURE OUT WHY THIS BREAKS THINGS
                it2++;
            }
            it++;
        }

        delete listeners;

    }
	
	void EventDispatcher::addEventListener(EventListener* l, string eventType) {
        if (listeners->find(eventType) == listeners->end() ) {
            (*listeners)[eventType] = new vector<EventListener*>();
        }
        (*listeners)[eventType] -> push_back(l);
    }

	void EventDispatcher::removeEventListener(EventListener* l, string eventType) {
        if (listeners->find(eventType) != listeners->end()) {
            vector<EventListener*> *eventList = listeners->at(eventType);
            for (vector<EventListener*>::iterator it = eventList->begin(); it != eventList->end(); ++it) {
                if (*it == l) {
                    eventList->erase(it);
                }
            }
        }

    }
	bool EventDispatcher::hasEventListener(EventListener* l, string eventType) {
        if (listeners->find(eventType) != listeners->end()) {
            vector<EventListener*> *eventList = listeners->at(eventType);
            for (vector<EventListener*>::iterator it = eventList->begin(); it != eventList->end(); ++it) {
                if (*it == l) {
                    return true;
                }
            }
            
        }
        return false;

    }
	void EventDispatcher::dispatchEvent(Event *e) {
        if (listeners -> find(e -> getType()) != listeners->end()) {
            vector<EventListener*> *eventList = listeners->at(e->getType());
            for (EventListener* el : *eventList) {
                el -> handleEvent(e);
            }
        }

    }