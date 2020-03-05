#include "Tween.h"
// Object representing on Sprite being tweened in some way. Can have multiple
// TweenParam objects.
Tween(){

}
Tween(DisplayObject object){
    
}
Tween(DisplayObject object, TweenTransitions transition){

}
animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time){


}
//invoked once per frame by the TweenJuggler. Updates this tween / DisplayObject
update() {

}

isComplete(){

}
setValue(TweenableParams param, double value){

}

}