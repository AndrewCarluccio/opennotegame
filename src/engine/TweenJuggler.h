#ifndef TWEENJUGGLER_H
#define TWEENJUGGLER_H

#include "Tween.h"

using namespace std;

class TweenJuggler {

public:
    TweenJuggler();

    void add(Tween* tween);
    void nextFrame(); //invoked every frame by Game, calls update() on every Tween and cleans up old / complete Tweens
    static TweenJuggler* getInstance();

private:
    static TweenJuggler* instance;
    vector<Tween*> tweens;
};

#endif