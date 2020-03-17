#include "TweenEvent.h"
#include <string>

const string TweenEvent::TWEEN_START_EVENT = "Tween Start";
const string TweenEvent::TWEEN_IN_PROGRESS_EVENT = "Tween In Progress";
const string TweenEvent::TWEEN_END_EVENT = "Tween End Event";

TweenEvent::TweenEvent(string eventType, EventDispatcher* disp, Tween* tween) : Event(eventType,disp){
    cur = tween;
    event_type = eventType;
    dispatch = disp;
    e_type = eventType;
}

Tween* TweenEvent::getTween() {
    return cur;
}

void TweenEvent::fireEvent() {
    dispatch->dispatchEvent(this);
}

string TweenEvent::getType() {
    return e_type;
}