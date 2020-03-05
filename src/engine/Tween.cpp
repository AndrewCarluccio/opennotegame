#include "Tween.h"
#include "TweenTransition.h"
// Object representing on Sprite being tweened in some way. Can have multiple
// TweenParam objects.

Tween::Tween(DisplayObject object){
    
}
Tween::Tween(DisplayObject object, TweenTransition transition){

}
void Tween::animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time){


}
//invoked once per frame by the TweenJuggler. Updates this tween / DisplayObject
void Tween::update() {

}

bool Tween::isComplete(){
    return true;
}
void Tween::setValue(TweenableParams param, double value){

}