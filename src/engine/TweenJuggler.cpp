#include "TweenJuggler.h"
#include "TweenEvent.h"
// Singleton class that handles all of the tweens in the game and updates them appropriately once per frame.
TweenJuggler* TweenJuggler::instance = NULL;

TweenJuggler::TweenJuggler(EventDispatcher* d){
    if (!instance) {
        instance = this;
    }
    disp = d;
}

TweenJuggler* TweenJuggler::getInstance() {
    return instance;
}

void TweenJuggler::add(Tween* tween) {
    tweens.push_back(tween);
    TweenEvent* ev = new TweenEvent(TweenEvent::TWEEN_START_EVENT, disp, tween);
    ev->fireEvent();
}

void TweenJuggler::nextFrame() {
    vector<Tween*>::iterator iter = tweens.begin();
    while (iter != tweens.end()) {
        Tween* tween = *iter;
        if (tween->isComplete()) {
            TweenEvent* ev = new TweenEvent(TweenEvent::TWEEN_END_EVENT,disp, tween);
            ev->fireEvent();
            iter = tweens.erase(iter);
        }
        else {
            tween->update();
            iter++;
            TweenEvent* ev = new TweenEvent(TweenEvent::TWEEN_IN_PROGRESS_EVENT, disp, tween);
            ev->fireEvent();
        }
    }
}