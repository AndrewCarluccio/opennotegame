#include "TweenParam.h"

TweenParam(TweenableParams paramToTween, double startVal, double endVal, double time) {
    param = paramToTween;
    startVal = startVal;
    endVal =  endVal;
    tweenTime = time;
}
TweenableParams* getParam(){
    return param;
}
double getStartVal(){
    return startVal;
}
double getEndVal(){
    return endVal;
}
double getTweenTime(){
    return tweenTime;
}