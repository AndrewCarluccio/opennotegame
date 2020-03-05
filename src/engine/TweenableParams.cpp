#include "TweenableParams.h"
// A list of strings representing the parameters of a Sprite that can be Tweened.
TweenableParams::TweenableParams() {
    
}
std::vector<std::string> getParam() {
    return TweenableParams::listOfParams;
}