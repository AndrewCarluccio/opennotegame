#include "TweenTransition.h"

string TweenTransition::QUAD = "QUAD";
string TweenTransition::LINEAR = "LINEAR";

TweenTransition::TweenTransition(string func) {
    if (func == QUAD) {
        activeFunc = QUAD;
    }
    else if (func == LINEAR) {
        activeFunc = LINEAR;
    }
    else {
        activeFunc = "";
    }
}

double TweenTransition::getResult(double x) {
    if (activeFunc == QUAD) {
        return x * x;
    }
    else if (activeFunc == LINEAR) {
        return x;
    }
    else {
        return x;
    }
}

void TweenTransition::setFunc(string func) {
    if (func == QUAD) {
        activeFunc = QUAD;
    }
    else if (func == LINEAR) {
        activeFunc = LINEAR;
    }
}