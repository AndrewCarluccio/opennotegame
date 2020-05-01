#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "AnimatedSprite.h"
#include <vector>
#include <string>
#include <fstream>
#include "Sprite.h"
#include "controls.h"
#include "Enemy.h"
#include "EnvironmentalObject.h"
#include "Character.h"
#include "GameState.h"

using namespace std;

class Player : public AnimatedSprite{

public:
	Player();
	Player(string id, string path);
	void loadAnimations();
	virtual void update(set<SDL_Scancode> pressedKeys);
	void updateGodMode(set<SDL_Scancode> pressedKeys);
	void updateDevToolMode(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	virtual void onCollision(DisplayObject* other);
	void onEnvObjCollision(EnvironmentalObject* envObj);
	void onEnemyCollision(Enemy* enemy);
	// determines if player is in god mode
	bool godMode = false;
	// determines if in dev tool mode (don't move around)
	bool devToolMode = false;
	//void initIFrames(int numFrames);

	int ticks = 0;
	int curTicks = 0;
	int count = 0; // using for corollaries 
	bool collectedAll = false;

	/* UI and Player variables */
	// ** MOVED TO GAME STATE **
	// int health = 100;
	// int maxHealth = 100;
	// int lowHealthThreshold = 30;
	// bool lowHealth = false;
	// bool dying = false;
	bool limbo = false;

	bool collision;
	bool _gravity = true;

	/* Jump variables */
	int _jumpVel = -15;
	int jumps = 0;
	bool doubleJump = false;
	bool megaJump = false;
	bool isTouching;

	bool hasPowerUp = false; 
	DisplayObject* curPowerUp = NULL;
	DisplayObject* curItem = NULL;
	DisplayObject* curWeapon = NULL;
	//DisplayObject* curShield;


	Enemy* curEnemy = NULL;
	Character* curCharacter = NULL;
	
	
	/* iFrames 
	bool iFrames = false;
	int iFrameCount = 0;
	int numIFrames = 0;
	*/
	


	/* --------------------- TO IMPLEMENT ------------------*/

	// STATES
	//fly
	//shoot
	//shield
	//die

	void incHealth(int hp);
	void decHealth(int hp);
	void dead();

	//state of limbo
	//transport elsewhere
	//remove item

	//reduced control (i know how to implement)
	//use item
	//interact (w/ another person)

	// ??
	//get emotions to play

	
private:

	GameState *state;
	Controls c;
	EnvironmentalObject e;
	int oldX = 0;
	int oldY = 0;

	/* Falling variables */ 
	bool _standing = true;
	bool _gStanding = true;
	int _maxFall = 9;
	int _yAcc = 2; 
	int _yAccCount = 0;
	int _yVel = 0;

	//void initIFrames(int numFrames);
};

#endif
/*
upon collision

phys:
	black hole -> DEATH
	cat -> state of limbo, dec health
	gravity -> gravity = false, ur flipped the whole room OR decreased movement/inability to jump
	higgs boson -> mega jump

anim:
	glitch -> moves you somewhere else (how to specify somewhere else?)
	lamp -> dec health
	paintbrush -> produces an item, has an animation associated with it
	eraser -> lose item, probs need to show something that shows u lost ur item

linear alg:
	matrix -> lose health
	projection -> lose health
	eigenvectors -> ?
	theorem -> collected (probs separate from item bc u can only hold one item?)
	
game design:
	affine transformations -> lose health UNLESS hits shield
	glitches -> moves you somewhere else, lose item
	TAs -> can interact (less of an env obj, more like character)
	office hours -> inc health
	*/

/*
and this is on enemy collison
if platform -> resolve collision
	if item -> 
		if health item -> health
		if power up ->
			go into particular power up
		if it's an item u actually use ->
			put in your only item slot lol 
			if you give it someone ->
				upon interaction, triggers a check between what is wanted from the interaction and what item you have 
			if you use it yourself ->
				enable when the control is pressed
	if weapon -> equip upon collision
	if another character -> allow interaction
	*/


/* TO DO BY ALPHA BUILD 


Schrodinger's Cat (enemy)
Black Holes (enemy)
Loutron (boss)
Pixar Lamps (enemy)
Glitches (kinda enemy)
Mark (boss)

*/


