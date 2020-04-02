#ifndef CONTROLS_H
#define CONTROLS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <set>

using namespace std;

class Controls {

public:
  Controls();
  void update(set<SDL_Scancode> pressedKeys);

  bool holdLeft();
  bool holdRight();
  bool pressJump();
  
  bool left = false;
  bool right = false;
  bool jump = false;
  // double jump
  // run
  // idk other stuff
  
private:

};

#endif
