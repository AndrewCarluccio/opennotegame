#include "TweenEvent.h"
#include <string>

const string TweenEvent::TWEEN_START_EVENT = "Tween Start";
const string TweenEvent::TWEEN_IN_PROGRESS_EVENT = "Tween In Progress";
const string TweenEvent::TWEEN_END_EVENT = "Tween End Event";

TweenEvent::TweenEvent(string eventType, Tween tween) {
    
}

Tween* TweenEvent::getTween() {
    return NULL;
}