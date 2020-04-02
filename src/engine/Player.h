#ifndef PLAYER_H
#define PLAYER_H

#include "DisplayObject.h"


class Player {
public:
    Player(DisplayObject* object);
    void update(set<SDL_Scancode> pressedKeys); 
    void draw(AffineTransform& at);

private:
    DisplayObject* myPlayer;
};

#endif