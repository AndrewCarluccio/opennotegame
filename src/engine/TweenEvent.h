#ifndef TWEENEVENT_H
#define TWEENEVENT_H

#include "Tween.h"
#include "Event.h"
#include <string>

class TweenEvent : public Event {
public:
    const static string TWEEN_START_EVENT;
    const static string TWEEN_IN_PROGRESS_EVENT;
    const static string TWEEN_END_EVENT;

    TweenEvent(string eventType, EventDispatcher* disp, Tween* tween);
    Tween* getTween();
    void fireEvent();
    string getType();

private:
    Tween* cur;
    string event_type;
    EventDispatcher* dispatch;
    string e_type;
};

#endif