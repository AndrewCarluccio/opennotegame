#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "controls.h"
#include <set>

using namespace std;


Controls::Controls() { 
}
     
void Controls::update(set<SDL_Scancode> pressedKeys) {
    if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) { // or controller dpad left
    	holdLeft = true; 
    }
        
    if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {  // or controller dpad right
      holdRight = true;
    }

    if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) { // or controller key a
      pressJump = true;
    }
}
/*
bool Controls::holdLeft() {
  return left;
}
  
bool Controls::holdRight() {
  return right;
}
  
bool Controls::pressJump() {
  return jump;
     
}
*/