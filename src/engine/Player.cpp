#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "controls.h"
//#include "Enemy.h"
//#include "EnvironmentalObject.h"
#include "../main/MyGame.h"
#include "CollisionSystem.h"

using namespace std;

Player::Player(string id, string path) : AnimatedSprite(id, path){
	this->type = "Player";
}

// careful to not do this in a loop, uses a lot of memory
void Player::loadAnimations() {
	addAnimation("resources/general_sprites/character/run_right/", "run", 8, 6, true);
	addAnimation("resources/general_sprites/character/run_left/", "run_l", 8, 6, true);
	addAnimation("resources/general_sprites/character/jump/", "jump", 8, 10, false);
	addAnimation("resources/general_sprites/character/", "idle", 1, 1, true);
	//shoot
	//shield
	//fly
}

void Player::update(set<SDL_Scancode> pressedKeys){
	AnimatedSprite::update(pressedKeys);

	/* (1195, 1583) is the window size. These if-statements keep the player within the scope of the camera */
	if (this->position.x  < 0) {
		this->position.x = 0;
	}
	else if (this->position.x + ((this->width) * (this->scaleX)) > 1195) {
		this->position.x = 1195 - ((this->width) * (this->scaleX));
	}

	if (this->position.y < 0) {
		this->position.y = 0;
	}
	else if (this->position.y + ((this->height) * (this->scaleY)) > 1555) {
		this->position.y = 1555 - ((this->height) * (this->scaleY));
		// if falling this->play("idle");
		_standing = true;
	}


	/* Player controls */
	if(c.holdRight) {
		if(this->current != getAnimation("run") && this->current != getAnimation("jump")){
			this->play("run");
		}
		if (lowHealth) {
			this->position.x += 4; // limited controls when health is low
		}
		else {
		this->position.x += 10; // move to the right
		}

		c.holdRight = false;
	}

	else if (c.holdLeft){
		if(this->current != getAnimation("run_l") && this->current != getAnimation("jump")){
			this->play("run_l");
		}
		if (lowHealth) {
			this->position.x -= 4; // limited controls when health is low
		}
		else {
		this->position.x -= 10; // move to left
		}

		c.holdLeft = false;
	}

	else if(_standing && !c.holdLeft && !c.holdRight) {
		jumps = 0; 
		//this->play("idle");
		if(this->current != getAnimation("idle")) {
			this->play("idle");
		}
	}

	else if(!_standing) {
		//play falling?
	}

	if (c.pressJump) {
		if (_standing) {
			_standing = false;
			this->_yVel = _jumpVel; 
			jumps++; // account for possible double jumps
			this->play("jump");
			if (megaJump) { // power up
				this->_yVel = (_jumpVel * 2); 
			}
			if (lowHealth) {
				if (_yVel < -10.0) {
					_yVel = -10.0;
				}
			}
		}

		if (!_standing) {
		c.pressJump = false; // only want player to jump when standing
		}
	}

	/* Calculate fall velocity. Given to us. */ 
	_yAccCount++;
	if(_yAccCount == _yAcc){
		_yAccCount=0;
		_yVel++;
		if(_yVel > _maxFall) _yVel = _maxFall;
	}



	/* Checks for gravity and flips player if necessary. */
	if (_gravity) {
		this->position.y += _yVel;
	}
	else {
		this->position.y -= _yVel;
	}

	/* Non-Movement Related Controls */
	/*
	if(c.shoot) {
		this->play("shoot");
	}

	if(c.shield) {
		this->play("shield");
	}

	if(c.useItem) {

	}

	if(c.interact) {
		// must detect which interactable object is in the player's proximity... 
		// or maybe to make it easier it has to be something the player is colliding with?
		// that's going to be awkward to go right up to another stick figure tho lmao

		//probably prompts dialogue of that character
		// if player doesn't have item -> this dialogue/thought bubble
		// else -> this dialogue/thought bubble
	}
	*/

	c.update(pressedKeys);
}

void Player::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

/* Collision Methods */

void Player::onCollision(DisplayObject* other){
	Game::instance->collisionSystem.resolveCollision(this, other, 
	  this->position.x - this->old_position.x, this->position.y - this->old_position.y,
	  other->position.x - other->old_position.x, other->position.y - other->old_position.y);
	
	if (other->object_type == types::Type::Platform) {
		_yVel = 0;
		_standing=true;
	}

	/* PHYSICS ENVIRONMENTAL COLLISIONS */

	// higgs boson collision 
	if (other->object_type == 4) { 
		_yVel = _jumpVel * 1.5; // shoots player up after touching higgs boson
		_standing = false;
		if (!_standing) {
			this->play("jump"); // plays the jumping animation
		}	
		else {
			_standing = true;
		}
	}	


	/* ANIMATIONS ENVIRONMENTAL COLLISIONS */

	// eraser (this needs to be edited, my brain tiny)
	// thought process: somewhere there is a collision w/powerup that sets powerup to true, then if satemetns inside of the
	//player controls (mega jump or msth) but if interact wiht eraser then powerup is false and then controls are
	//just nromal since the if statements takes care of "if hasPowerUp"
	if (other->object_type == 5) {
		hasPowerUp = false;
	}

	//paint brush
	if (other->object_type == 7) { // if in contact with paint brush
		other->position.y += _yVel; // it will fall and be deleted (?) NOT in update method so idk if it will gradually fall or just
		// move y position quickly.
		delete other; // can u just do this 
	}

	else if(other->type == "EnvironmentalObject") {
		//this->onEnvObjCollision((EnvironmentalObject*) other);
	}

	else if(other->type == "Enemy"){ 
		//this->onEnemyCollision((Enemy*) other); 
	}

	else if(other->object_type == types::Type::Character){
		this->onCharacterCollision(other); // replace this w Character class?
	}

/*
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
*/
}

/*

void Player::initIFrames(int numFrames) {
	this->iFrameCount = 0;
	this->numIFrames = numFrames;
	this->iFrames = true;
}
*/

/* these methods don't work rn so uh. okay.
void Player::onEnvObjCollision(EnvironmentalObject* envObj){
	

	// higgs boson collision 
	if (envObj->object_type == 4) { 
		_yVel = _jumpVel * 1.5; // shoots player up after touching higgs boson
		_standing = false;
		if (!_standing) {
			this->play("jump"); // plays the jumping animation
		}	
		else {
			_standing = true;
		}
	}	


	

	// eraser (this needs to be edited, my brain tiny)
	// thought process: somewhere there is a collision w/powerup that sets powerup to true, then if satemetns inside of the
	//player controls (mega jump or msth) but if interact wiht eraser then powerup is false and then controls are
	//just nromal since the if statements takes care of "if hasPowerUp"
	if (envObj->object_type == 5) {
		hasPowerUp = false;
	}

	//paint brush
	if (envObj->object_type == 7) { // if in contact with paint brush
		envObj->position.y += _yVel; // it will fall and be deleted (?) NOT in update method so idk if it will gradually fall or just
		// move y position quickly.
		delete envObj; // can u just do this 
	}
}
*/

/*
void Player::onEnemyCollision(Enemy* enemy){ // replaace w enemy class later
	if(enemy->object_type == types::Type::Cat) {
		this->decHealth(10);
		// remove from collision system for a few seconds >3>
	}
	*/
/*
phys:
	black hole -> DEATH

anim:
	glitch -> moves you somewhere else (how to specify somewhere else?)
	lamp -> dec health

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
//}

void Player::onCharacterCollision(DisplayObject* character) {
	// stuff
}

/* On Collision Supporting Methods */

void Player::incHealth(int hp){
	health += hp;
	if (health > maxHealth){
		health = maxHealth;
	}
	else if (health > lowHealthThreshold){ 
		lowHealth = false;
	}
}

void Player::decHealth(int hp){
	health -= hp;
	if (health <= 0){
//		this->dead();
	}
	else if (health < lowHealthThreshold){ 
		lowHealth = true;
	}
}

/* Other */

/*
void Player::emotions(String emotion){
	// show one of the displayobject children of player depending on its id
}
*/