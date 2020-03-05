#ifndef TWEENEVENT_H
#define TWEENEVENT_H

#include "Tween.h"
#include <string>

class TweenEvent {
public:
    const static string TWEEN_START_EVENT;
    const static string TWEEN_IN_PROGRESS_EVENT;
    const static string TWEEN_END_EVENT;

    TweenEvent(string eventType, Tween tween);
    Tween* getTween();
};

#endif