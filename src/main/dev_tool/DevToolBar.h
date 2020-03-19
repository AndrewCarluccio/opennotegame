#ifndef DEVTOOL_BAR_H
#define DEVTOOL_BAR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cmath>

#include "../engine/DisplayObjectContainer.h"
#include "../engine/Sprite.h"

using namespace std;

class DevToolBar: public DisplayObjectContainer {
    public:
        DevToolBar();
        virtual void update(set<SDL_Scancode> pressedKeys);
	    virtual void draw(AffineTransform &at);
};

#endif