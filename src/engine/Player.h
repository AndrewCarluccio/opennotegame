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
	virtual void onCollision(DisplayObject* other);
	//void onEnemyCollision(Enemy* enemy);

	/* UI variables */
	int health = 100;
	int maxHealth = 100;
	int lowHealthThreshold = 30;
	bool lowHealth = false;

	/* Jump variables */
	int _jumpVel = -15;
	int jumps = 0; 
	bool doubleJump = false;
	bool megaJump = false;


	/*
	Enemy* curEnemy = NULL;

	//iFrames
	bool iFrames = false;
	int iFrameCount = 0;
	int numIFrames = 0;
	*/


	/* --------------------- TO IMPLEMENT ------------------*/

	// ITEMS
	//current item
	//current weapon
	//shield ?

	// STATES
	//fly
	//shoot
	//shield
	//die

	void incHealth();
	void decHealth();

	//state of limbo
	//transport elsewhere
	//remove item

	//reduced control (i know how to implement)
	//use item
	//interact (w/ another person)

	// ??
	//get emotions to play

	
private:

	Controls c;
	int oldX = 0;
	int oldY = 0;

	/* Falling variables */ 
	bool _gravity = true;
	bool _standing = true;
	int _maxFall = 9;
	int _yAcc = 2; 
	int _yAccCount = 0;
	int _yVel = 0;

	//void initIFrames(int numFrames);
};

#endif

