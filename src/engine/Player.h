#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "AnimatedSprite.h"
#include <vector>
#include <string>
#include <fstream>
#include "Sprite.h"
#include "controls.h"

using namespace std;

class Player : public AnimatedSprite{

public:

	Player();
	Player(string id, string path);
	void loadAnimations();
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);

	int health = 100;
	int maxHealth = 100;

	// jump vars
	int jumps = 0;
	bool doubleJump = false;

	//current item
	//current weapon
	//shield ?

	// states
	//fly
	//shoot
	//shield

	// collision
  	virtual void onCollision(DisplayObject* other);
	
	// enemy

	//void onEnemyCollision(Enemy* enemy);
	//die
	//decrease health
	//state of limbo
	//transport elsewhere
	//remove item

	// environment

	//increase health
	//gravity flip
	//reduced control
	//mega jump

	//Enemy* curEnemy = NULL;

	/*
	//iFrames
	bool iFrames = false;
	int iFrameCount = 0;
	int numIFrames = 0;
	*/

private:

	Controls c;
	int oldX=0, oldY=0;
  	//bool flipH = false;

	int _jumpVel = -15;

	/* Falling variables */ 
	bool _gravity = true;
	bool _standing = true;
	// are these even being used?
	int _maxFall = 9;
	int _yAcc = 2; //one pixel every two frames
	int _yAccCount = 0;
	int _yVel = 0;

	//void initIFrames(int numFrames);
};

#endif

