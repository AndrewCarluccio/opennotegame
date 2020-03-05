#include "TweenParam.h"

TweenParam::TweenParam(TweenableParams* paramToTween, double startVal, double endVal, double time) {
    param = paramToTween;
    startVal = startVal;
    endVal =  endVal;
    tweenTime = time;
}
TweenableParams* TweenParam::getParam(){
    return param;
}
double TweenParam::getStartVal(){
    return startVal;
}
double TweenParam::getEndVal(){
    return endVal;
}
double TweenParam::getTweenTime(){
    return tweenTime;
}