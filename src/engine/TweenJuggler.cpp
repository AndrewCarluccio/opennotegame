#include "TweenJuggler.h"
// Singleton class that handles all of the tweens in the game and updates them
// appropriately once per frame.
TweenJuggler* TweenJuggler::instance = NULL;

TweenJuggler::TweenJuggler(){
    
}

TweenJuggler* TweenJuggler::getInstance() {
    if (!instance) {
        instance = new TweenJuggler;
    }
    return instance;
}