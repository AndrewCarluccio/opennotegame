#include "TweenJuggler.h"
// Singleton class that handles all of the tweens in the game and updates them appropriately once per frame.
TweenJuggler* TweenJuggler::instance = NULL;

TweenJuggler::TweenJuggler(){
    if (!instance) {
        instance = this;
    }
}

TweenJuggler* TweenJuggler::getInstance() {
    return instance;
}

void TweenJuggler::add(Tween* tween) {
    tweens.push_back(tween);
}

void TweenJuggler::nextFrame() {
    vector<Tween*>::iterator iter = tweens.begin;
    while (iter != tweens.end) {
        Tween* tween = *iter;
        if (tween->isComplete()) {
            tweens.erase(iter);
        }
        else {
            tween->update();
            iter++;
        }
    }
}