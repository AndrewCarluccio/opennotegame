#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "controls.h"
#include <set>

using namespace std;


Controls::Controls() { 
}
     
void Controls::update(set<SDL_Scancode> pressedKeys) {
  for (SDL_Scancode key : pressedKeys) {
    if (key == SDL_SCANCODE_LEFT || key == SDL_SCANCODE_A) { // or controller dpad left
    	left = true; 
	break;
    }
        
    if (key == SDL_SCANCODE_RIGHT || key == SDL_SCANCODE_D) { // or controller dpad right
      right = true;
      break;
    }

    if (key == SDL_SCANCODE_UP || key == SDL_SCANCODE_SPACE) { // or controller key a
      jump = true;
      break;
    }
  }
}

bool Controls::holdLeft() {
  return left;
}
  
bool Controls::holdRight() {
  return right;
}
  
bool Controls::pressJump() {
  return jump;
     
}
