#ifndef TWEENPARAM_H
#define TWEENPARAM_H
#include "TweenableParams.h"

class TweenParam {

public:
    TweenParam(string paramToTween, double startVal, double endVal, double time);
    string getParam();
    double getStartVal();
    double getEndVal();
    double getTweenTime();
    
private:
    string param;
    double startVal;
    double endVal;
    double tweenTime;
};

#endif