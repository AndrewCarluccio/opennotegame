#ifndef DISPLAYOBJECTEVENT_H
#define DISPLAYOBJECTEVENT_H

#include "Event.h"
#include "DisplayObject.h"
#include <string>

class DisplayObjectEvent : public Event {
public:
    const static string DISPLAY_OBJECT_ADDED_EVENT;
    const static string DISPLAY_OBJECT_REMOVED_EVENT;

    DisplayObjectEvent(string eventType, EventDispatcher* disp, DisplayObject* object);
    DisplayObject* getDisplayObject();
    string getType();

private:
    DisplayObject* cur;
    string event_type;
    EventDispatcher* dispatch;
};

#endif