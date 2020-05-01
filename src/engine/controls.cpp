#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "controls.h"
#include <set>

using namespace std;


Controls::Controls() { 
}
	 
void Controls::update(set<SDL_Scancode> pressedKeys) {
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end() 
		|| pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) { // or controller dpad left
		holdLeft = true; 
	}
		
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()   // or controller dpad right
		|| pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) { 
		holdRight = true;
	}

	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end() // or controller key a
		|| pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) { 
		pressJump = true;
	}

	if (pressedKeys.find(SDL_SCANCODE_RETURN) != pressedKeys.end()) { 
		interact = true;
	}

	if (pressedKeys.find(SDL_SCANCODE_LSHIFT) != pressedKeys.end()) { 
		holdShield = true;
	}

	if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) { 
		holdGun = true;
	}

}

