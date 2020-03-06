#include "TweenParam.h"

TweenParam::TweenParam(TweenableParams* paramToTween, double startVal, double endVal, double time) {
    this->param = paramToTween;
    this->startVal = startVal;
    this->endVal =  endVal;
    this->tweenTime = time;
}
TweenableParams* TweenParam::getParam(){
    return this->param;
}
double TweenParam::getStartVal(){
    return this->startVal;
}
double TweenParam::getEndVal(){
    return this->endVal;
}
double TweenParam::getTweenTime(){
    return this->tweenTime;
}