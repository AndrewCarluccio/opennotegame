#ifndef TWEEN_H
#define TWEEN_H

#include "DisplayObject.h"
#include "TweenTransition.h"
#include "TweenableParams.h"
#include "TweenParam.h"

#include <vector>
#include <string>

class Tween {
public:
    Tween(DisplayObject* object);
    Tween(DisplayObject* object, TweenTransition* transition);
    void animate(string fieldToAnimate, double startVal, double endVal, double time);
    void update(); //invoked once per frame by the TweenJuggler. Updates this tween / DisplayObject
    bool isComplete();
    void setValue(string param, double value);

private:
    DisplayObject* tweenObject;
    TweenTransition* tweenTransition;
    vector<TweenParam*> tweenParams;
};

#endif