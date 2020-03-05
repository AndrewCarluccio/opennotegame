#ifndef TWEENJUGGLER_H
#define TWEENJUGGLER_H

class TweenJuggler {
public:
    TweenJuggler::TweenJuggler();
    TweenJuggler::add(Tween tween);
    TweenJuggler::nextFrame(); //invoked every frame by Game, calls update() on every Tween and cleans up old /
// complete Tweens
    static TweenJuggler* TweenJuggler::getInstance();
private:
    static TweenJuggler* instance;


}

#endif