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

  bool holdLeft = false;
  bool holdRight = false;
  bool pressJump = false;
  bool interact = false;
  

private:

};

#endif
