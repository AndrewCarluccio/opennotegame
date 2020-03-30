#include "Tween.h"
#include "TweenParam.h"
#include "TweenTransition.h"
#include "TweenableParams.h"
#include "TweenEvent.h"
#include <iostream>

#include <string>
// Object representing on Sprite being tweened in some way. Can have multiple
// TweenParam objects.

Tween::Tween(DisplayObject* object){
    this->tweenObject = object;
    this->tweenTransition = new TweenTransition(TweenTransition::LINEAR);
}

Tween::Tween(DisplayObject* object, TweenTransition* transition){
    this->tweenObject = object;
    this->tweenTransition = transition;
}

void Tween::animate(string fieldToAnimate, double startVal, double endVal, double time){
    TweenParam* newParam = new TweenParam(fieldToAnimate, startVal, endVal, time);
    tweenParams.push_back(newParam);
}

//invoked once per frame by the TweenJuggler. Updates this tween / DisplayObject
void Tween::update() {
    time_t curTime = time(nullptr);
    double elapsedTime;
    double percentComplete;

    vector<TweenParam*>::iterator iter = tweenParams.begin();
    while (iter != tweenParams.end()) {
        TweenParam* tp = *iter;
       
        elapsedTime = float(clock() - tp->getStartTime()) / CLOCKS_PER_SEC;
        percentComplete = elapsedTime / tp->getTweenTime();
        if (percentComplete <= 1.0) {
            double percentOfValue = tweenTransition->getResult(percentComplete);
            double newValue = (tp->getEndVal() - tp->getStartVal()) * percentOfValue + tp->getStartVal();
            this->setValue(tp->getParam(), newValue);
            //cout << "timeDiff " << elapsedTime << endl;
            //cout << "name " << this->tweenObject->id << " val " << newValue << endl;
            iter++;
        }
        else {
            iter = tweenParams.erase(iter);
        }
    } 
}

bool Tween::isComplete(){
    return tweenParams.empty();
}

void Tween::setValue(string param, double value){
    if (param == TweenableParams::X) {
        tweenObject->position.x = value;
    }
    else if (param == TweenableParams::Y) {
        tweenObject->position.y = value;
    }
    else if (param == TweenableParams::SCALE_X) {
        tweenObject->scaleX = value;
    }
    else if (param == TweenableParams::SCALE_Y) {
        tweenObject->scaleY = value;
    }
    else if (param == TweenableParams::ALPHA) {
        tweenObject->alpha = value;
    }
    else if (param == TweenableParams::ROTATION) {
        tweenObject->rotation = value;
    }
    else {
        // invalid tweenable param
    }
}