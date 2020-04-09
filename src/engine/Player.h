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

  	//void onEnemyCollision(Enemy* enemy);
  	virtual void onCollision(DisplayObject* other);

	/* Health and such */
	int health = 100;
	int maxHealth = 100;

	//iFrames
	bool iFrames = false;
	int iFrameCount = 0;
	int numIFrames = 0;

	/* Current Enemy player is engaging with*/
	//Enemy* curEnemy = NULL;


private:

	int oldX=0, oldY=0;
  	bool flipH = false;

	int _jumpVel = -15;

	/* Falling variables */
	bool _standing = true;
	int _maxFall = 9;
	int _yAcc = 2; //one pixel every two frames
	int _yAccCount = 0;
	int _yVel = 0;

	Controls c;

	void initIFrames(int numFrames);

};

#endif

