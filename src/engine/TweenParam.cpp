#include "TweenParam.h"

TweenParam::TweenParam(string paramToTween, double startVal, double endVal, double tweenTime) {
    this->param = paramToTween;
    this->startVal = startVal;
    this->endVal =  endVal;
    this->tweenTime = tweenTime;
    this->startTime = clock();
}
string TweenParam::getParam(){
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
clock_t TweenParam::getStartTime(){
    return this->startTime;
}