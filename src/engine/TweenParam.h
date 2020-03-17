#ifndef TWEENPARAM_H
#define TWEENPARAM_H
#include "TweenableParams.h"
#include <ctime>  
using namespace std;

class TweenParam {

public:
    TweenParam(string paramToTween, double startVal, double endVal, double time);
    string getParam();
    double getStartVal();
    double getEndVal();
    double getTweenTime();
    clock_t getStartTime();
    
private:
    string param;
    double startVal;
    double endVal;
    double tweenTime;
    clock_t startTime;
};

#endif