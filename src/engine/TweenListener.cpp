#include "TweenListener.h"

void TweenListener::handleEvent(Event* event) {
    if (event->getType() == TweenEvent::TWEEN_START_EVENT) {
        TweenEvent* te = static_cast<TweenEvent*>(event);
        Tween* tw = te->getTween();
        if (tw == myTween) {
            started = true;
            TweenEvent* ev = (TweenEvent*)event;
        }
    }
	else if (event->getType() == TweenEvent::TWEEN_END_EVENT) {
		TweenEvent* te = static_cast<TweenEvent*>(event);
		Tween* tw = te->getTween();
		if (tw == myTween) {
			ended = true;
			TweenEvent* ev = (TweenEvent*)event;
		}
	}
}

void TweenListener::reset() {
	started = false;
	ended = false;
}