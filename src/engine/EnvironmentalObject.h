#ifndef ENVIRONMENTALOBJECT_H
#define ENVIRONMENTALOBJECT_H

#include <iostream>
#include "AnimatedSprite.h"
#include <vector>
#include <string>
#include <fstream>
#include "Sprite.h"
#include "controls.h"
//#include "Player.h"
//#include "Enemy.h"

using namespace std;

class EnvironmentalObject : public AnimatedSprite{

public:
	EnvironmentalObject();
	EnvironmentalObject(string id, string path);
	void loadAnimations();
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	virtual void onCollision(DisplayObject* other);

	/* Jump variables */
	//int _jumpVel = -15;
	//int jumps = 0; 
	//bool doubleJump = false;
	//bool megaJump = false;

	bool paintBrushTouched;
private:

	int oldX = 0;
	int oldY = 0;

	/* Falling variables */ 
	bool _gravity = true;
	bool _standing = true;
	int _maxFall = 9;
	int _yAcc = 2; 
	int _yAccCount = 0;
	int _yVel = 0;

	

};

#endif
