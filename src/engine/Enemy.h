#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include "AnimatedSprite.h"
#include <vector>
#include <string>
#include <fstream>
#include "Sprite.h"
#include "controls.h"
//#include "Player.h"
//#include "EnvironmentalObject.h"

using namespace std;

class Enemy : public AnimatedSprite{

public:
	Enemy();
	Enemy(string id, string path);
	void loadAnimations();
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	//virtual void onCollision(DisplayObject* other);

	int health = 100;
	int maxHealth = 100;
	int lowHealthThreshold = 30;
	bool lowHealth = false;

	/* Jump variables */
	int _jumpVel = -15;
	int jumps = 0; 

	void incHealth(int hp);
	void decHealth(int hp);
    void dead();
	
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
