#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include "AnimatedSprite.h"
#include <vector>
#include <string>
#include <fstream>
#include "Sprite.h"
#include "controls.h"
#include "EnvironmentalObject.h"
#include "CollisionSystem.h"



using namespace std;

class Enemy : public AnimatedSprite{

public:
	Enemy();
	Enemy(string id, string path);
	void loadAnimations();
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	virtual void onCollision(DisplayObject* other);


	void setPatrolRange();
	void patrol();
	void lunge();
	void bodySlam();
	void shield();
	void shoot();
	bool isTargetReached();
	void moveToTarget();


	int health = 100;
	int maxHealth = 100;
	int lowHealthThreshold = 30;
	bool lowHealth = false;
	int state = 0; // how to control states

	/* Jump variables */
	int _jumpVel = -15;
	int jumps = 0; 

	void incHealth(int hp);
	void decHealth(int hp);
    void dead();

	int plusX;
	int minusX;

	int ticks = 0;
	int curTicks = 0;
	
private:
	int projMaxPatX;
	int maxPatX;
	int minPatX;
	int minPatY;
	int maxPatY;
	int targX;
	int targY;
	int vel;
	int maxVel;
	int acc = 5;
	double theta;
	double xComp;
	double yComp;

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


