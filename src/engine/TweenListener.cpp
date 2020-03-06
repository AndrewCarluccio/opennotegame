#include "TweenListener.h"

void TweenListener::handleEvent(Event* event) {
    if (event->getType() == TweenEvent::TWEEN_END_EVENT) {
        TweenEvent* te = static_cast<TweenEvent*>(event);
        Tween* tw = te->getTween();
        if (tw == myTween) {
            occured = true;
            TweenEvent* ev = (TweenEvent*)event;
        }
    }
}