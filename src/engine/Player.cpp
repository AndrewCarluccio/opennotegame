#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "controls.h"
//#include "Enemy.h"
#include "EnvironmentalObject.h"
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

	oldX = this->position.x;
	oldY = this->position.y;


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
		if you give it someone ->
			upon interaction, triggers a check between what is wanted from the interaction and what item you have 
		if you use it yourself ->
			enable when the control is pressed
	}

	if(c.interact) {
		if first time you talked with them -> first dialogue
		else if you have the item they're looking for -> item dialogue & item exchange 
		else (you havent gotten the correct item yet) -> random dialogue from an array of quips

		i imagine all these dialogues are methods of the character class
	}
	*/

	c.update(pressedKeys);
}

void Player::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

/* Collision Methods */

void Player::onCollision(DisplayObject* other){
	if (other->object_type == types::Type::Platform) {
		Game::instance->collisionSystem.resolveCollision(this, other, this->position.x - oldX, this->position.y - oldY, 0, 0);
		if(_yVel < 0)
			_yVel = 0;
		int meY = this->getHitbox().y;
		int meH = this->getHitbox().h;
		int otherY = other->getHitbox().y;
		if (meY + meH <= otherY)
			_standing=true;
	}

	else if (other->type == "EnvironmentalObject") {
		this->onEnvObjCollision((EnvironmentalObject*) other);
	}

	else if (other->type == "Enemy") { 
		this->onEnemyCollision((Enemy*) other); 
	}

	else if  (other->object_type == types::Type::Character) {
		curCharacter = other; // possibly make a Character class
		// i think a speech bubble should appear near the character to show you can talk to them, this is a UI thing
	}

	else if(other->object_type == types::Type::Item) {
		if (!(other->collision)) {
			curItem = other;
			other->visible = false;
			other->collision = true;
		}
	}

	else if (other->object_type == types::Type::Health) {
		if (!(other->collision)) {
			if (other->sprite_type == "shin") {
				this->incHealth(10);
				other->visible = false;
				other->collision = true;
			}
			else if (other->sprite_type == "buldak") {
				this->incHealth(20);
				other->visible = false;
				other->collision = true;
			}
		}

		if (other->sprite_type == "oh") {
			this->incHealth(15);
		}
	}

	else if (other->object_type == types::Type::PowerUp) {
		if (!(other->collision)) {
			curPowerUp = other;
			other->visible = false;
			other->collision = true;
		}
		// equip power up (ex. if powerup id starts with "jump" -> mega jump or sthn like this)
		// or maybe have that ^ done somewhere else, check curPowerUp->id idrk
	}

	else if (other->object_type == types::Type::Weapon) {
		curWeapon = other;
		// add sprite as child of player but only for shooting animation
		// for simplicity... ig uess we won't have them carry the weapon all the time :")
	}
}

/*

void Player::initIFrames(int numFrames) {
	this->iFrameCount = 0;
	this->numIFrames = numFrames;
	this->iFrames = true;
}
*/

void Player::onEnvObjCollision(EnvironmentalObject* envObj){
	/* PHYSICS ENVIRONMENTAL COLLISIONS */

	// higgs boson collision 
	if (envObj->object_type == types::Type::HiggsBoson) { 
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

	if (envObj->object_type == types::Type::Eraser) {
		Game::instance->collisionSystem.resolveCollision(this, envObj, this->position.x - oldX, this->position.y - oldY, 0, 0);
		hasPowerUp = false;		
	}

	//paint brush
	if (envObj->object_type == types::Type::PaintBrush) { // if in contact with paint brush		
		envObj->position.y += _yVel; // fall with the player
	}

	/* LINEAR ALGEBRA */
	//eigenvectors -> ?
	//theorem -> collected (probs separate from item bc u can only hold one item?)

	// GAME DESIGN: TAs are characters, Office Hours are "health" items
}



void Player::onEnemyCollision(Enemy* enemy){ 
	/* PHYSICS */
	if (enemy->sprite_type == "blackhole") {
		//this->play("blackhole");
		this->dead();
	}

	else if (enemy->sprite_type == "cat") {
		this->decHealth(10);
	}


	/* ANIMATION */
	else if (enemy->sprite_type == "glitch") {
		// move somewhere else
	}

	else if (enemy->sprite_type == "lamp") {
		this->decHealth(10);
	}


	/* LINEAR ALGEBRA */
	else if (enemy->sprite_type == "matrix") {
		this->decHealth(10);
	}

	else if (enemy->sprite_type == "projection") {
		this->decHealth(10);
	}


	/* GAME DESIGN */
	else if (enemy->sprite_type == "affine") {
		this->decHealth(10);
		// if hits shield
	}
	else if (enemy->sprite_type == "adv_glitch") {
		// move somewhere else
		// lose item
	}
	
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
		this->dead();
	}
	else if (health < lowHealthThreshold){ 
		lowHealth = true;
	}
}

void Player::dead(){
	//Game::instance->quitSDL();
	// later replace this with game over scene
}

/* Other */

/*
void Player::emotions(String emotion){
	// show one of the displayobject children of player depending on its id
}
*/