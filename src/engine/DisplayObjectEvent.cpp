#include "DisplayObjectEvent.h"
#include <string>

const string DisplayObjectEvent::DISPLAY_OBJECT_ADDED_EVENT = "Display Object Added";
const string DisplayObjectEvent::DISPLAY_OBJECT_REMOVED_EVENT = "Display Object Removed";

DisplayObjectEvent::DisplayObjectEvent(string eventType, EventDispatcher* disp, DisplayObject* object) : Event(eventType,disp){
    event_type = eventType;
    dispatch = disp;
    cur = object;
}

DisplayObject* DisplayObjectEvent::getDisplayObject() {
    return cur;
}

string DisplayObjectEvent::getType() {
    return event_type;
}