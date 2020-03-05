#ifndef TWEENEVENT_H
#define TWEENEVENT_H

class TweenEvents {
public:
    final static strings denoting the various events (e.g., TWEEN_COMPLETE_EVENT)
    TweenEvent(String eventType, Tween tween);
    Tween getTween();
}

#endif