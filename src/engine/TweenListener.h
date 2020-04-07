#ifndef TWEEN_LISTENER_H
#define TWEEN_LISTENER_H

#include <iostream>
#include "EventListener.h"
#include "Event.h"
#include "TweenEvent.h"

using namespace std;

class TweenListener : public EventListener {
public:
    virtual void handleEvent(Event* event);
    bool occured = false;
    Tween* myTween = NULL;
};

#endif