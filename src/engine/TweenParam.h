#ifndef TWEENPARAM_H
#define TWEENPARAM_H
#include "TweenableParams.h"

class TweenParam {
public:

    TweenParam(TweenableParams* paramToTween, double startVal, double endVal, double time);
    TweenableParams* getParam();
    double getStartVal();
    double getEndVal();
    double getTweenTime();
    
private:

    TweenableParams* param;
    double startVal;
    double endVal;
    double tweenTime;
};

#endif