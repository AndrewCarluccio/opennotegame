#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "controls.h"
#include "Enemy.h"
#include "EnvironmentalObject.h"
#include "../main/MyGame.h"
#include "CollisionSystem.h"
#include "TransitionPoint.h"
#include <random>
#include <vector>


using namespace std;

Player::Player(string id, string path) : AnimatedSprite(id, path){
	this->type = "Player";
	loadAnimations();
	state = &Game::instance->gameState;
}

// careful to not do this in a loop, uses a lot of memory
void Player::loadAnimations() {
	addAnimation("resources/general_sprites/character/run_right/", "run", 8, 6, true);
	addAnimation("resources/general_sprites/character/run_left/", "run_l", 8, 6, true);
	addAnimation("resources/general_sprites/character/jump/", "jump", 8, 10, false);
	addAnimation("resources/general_sprites/character/jump_left/", "jump_l", 8, 10, false);
	addAnimation("resources/general_sprites/character/", "idle", 1, 1, true);
	addAnimation("resources/general_sprites/character/blackhole/", "bh", 4, 8, false);
	addAnimation("resources/general_sprites/character/shield/", "shieldidle", 1, 1, false);
	addAnimation("resources/general_sprites/character/gun/", "gunidle", 1, 1, false);
}

void Player::updateDevToolMode(set<SDL_Scancode> pressedKeys) {
// execute this update method instead if in dev tool mode, no movement
	AnimatedSprite::update(pressedKeys);
	this->play("idle");
}


void Player::updateGodMode(set<SDL_Scancode> pressedKeys) {
	AnimatedSprite::update(pressedKeys);
	this->play("idle");
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) { 
		position.x -= 10; 
	}
		
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {  
		position.x += 10; 
	}

	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) { 
		position.y -= 10; 
	}

	if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) { 
		position.y += 10; 
	}
}

void Player::update(set<SDL_Scancode> pressedKeys){
	if (devToolMode) {
		updateDevToolMode(pressedKeys);
		return;
	}
	if (godMode) {
		updateGodMode(pressedKeys);
		return;
	}
	AnimatedSprite::update(pressedKeys);

	if (ticks == curTicks + 60) {
		// dying = false;
		state->setDying(false);
		limbo = false;
		alpha = 250;
	}

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
	if(!state->isDead()) {
	// if (!dying) {
	if(c.holdRight) {
		this->facingRight = true;
		if(this->current != getAnimation("run") && this->current != getAnimation("jump")){
			this->play("run");
		}
		if(state->isLowHealth()) {
		// if (lowHealth) {
			this->position.x += 4; // limited controls when health is low
		}
		else {
			this->position.x += 10; // move to the right
		}

		c.holdRight = false;
	}

	else if (c.holdLeft){
		this->facingRight = false;
		if (_gravity) {
			if(this->current != getAnimation("run") && this->current != getAnimation("jump")){
				this->play("run");
			}
		}
		else if (!_gravity) { // work around to get the upside down animation
			if(this->current != getAnimation("run_l") && this->current != getAnimation("jump_l")) {
				this->play("run_l");
			}
		}
		if(state->isLowHealth()) {
		// if (lowHealth) {
			this->position.x -= 4; // limited controls when health is low
		}
		else {
			this->position.x -= 10; // move to left
		}
		c.holdLeft = false;
	}

	else if((_standing && !c.holdLeft && !c.holdRight) || (_gStanding && !c.holdLeft && !c.holdRight)) {
		jumps = 0; 
		if (c.holdShield) {
			if(this->current != getAnimation("shieldidle")) {
				this->play("shieldidle");
			}
		c.holdShield = false;
		}

		else if (c.holdGun) {
			if(this->current != getAnimation("gunidle")) {
				this->play("gunidle");
			}
			c.holdGun = false;
		}

		else if (this->current != getAnimation("idle")) {
			this->play("idle");
		}
	}

	else if(!_standing) {
		//play falling?
	}

	if (c.pressJump) {
			if (_standing || _gStanding) { // idle to jump
				_standing = false;  // false bc now ur jumping 
				_gStanding = false;
				this->_yVel = _jumpVel; // height you can jump
				jumps++; // account for possible double jumps
				this->play("jump");
				if (!_gravity) {
					if (!this->facingRight) {
						this->play("jump_l");
					}
					else if (this->facingRight) {
						this->play("jump");
					}
				}
				if (megaJump) { // power up
				this->_yVel = (_jumpVel * 1.5); 
				}
				if(state->isLowHealth()) {
				// if (lowHealth) {
					if (_yVel < -10.0) {
						_yVel = -10.0;
					}
				}
			}
			if (!_standing || !_gStanding) { // if jumping bc not on ground
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
		this->facingDown = true;

	}
	else {
		this->position.y -= _yVel;
		this->facingDown = false;

		//this->facingDown = false;
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
		check what kind of item it is 
	}
	*/

	if(c.interact) {
		if (curCharacter != NULL) {
			curItem = curCharacter->dialogueGenerator(curItem);
			if (curItem != NULL) {
				cout << "The player's current item is " + curItem->sprite_type << endl;
			}
			else {
				cout << "get an item fool" << endl;
			}
		}
		cout << "ENTER was pressed" << endl;
		c.interact = false;
	}
	}

	c.update(pressedKeys);

	ticks++;
}

void Player::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

/* Collision Methods */

void Player::onCollision(DisplayObject* other){
	if (!state->isDead() && !limbo && !transparency) {
		if (other->object_type == types::Type::Platform) {
			Game::instance->collisionSystem.resolveCollision(this, other, this->position.x - oldX, this->position.y - oldY, 0, 0);
			if(_yVel < 0)
				_yVel = 0;
			int meY = this->getHitbox().y;
			int meH = this->getHitbox().h;
			int otherY = other->getHitbox().y;
			if (meY + meH <= otherY)
				_standing=true;
				_gStanding = true;
		}

		else if (other->type == "EnvironmentalObject") {
			this->onEnvObjCollision((EnvironmentalObject*) other);
		}

		else if (other->type == "Enemy") { 
			curEnemy = (Enemy*) other;
			this->onEnemyCollision((Enemy*) other); 
		}

		else if  (other->object_type == types::Type::Character) {
			curCharacter = (Character*) other; 
			// i think a speech bubble should appear near the character to show you can talk to them, this is a UI thing
		}

		else if(other->object_type == types::Type::Item) {
			if (other->sprite_type == "sprite") { // CHANGE SPRITE ID 
				if (!(other->collision)) {
					other->visible = false;
					other->collision = true;		
					}
				}
			else if (other->sprite_type == "corollary") { // CHANGE SPRITE ID 
				if (!(other->collision)) {
					other->visible = false;
					other->collision = true;
					count ++;		
					}
				if (count == 10) {
					collectedAll = true;
				}
			}
		
			else if (other->sprite_type == "box") {
				Game::instance->collisionSystem.resolveCollision(this, other, this->position.x - oldX, this->position.y - oldY, 0, 0);	
			}
		}

		else if (other->object_type == types::Type::Health) {
			if (!(other->collision)) {
				if (other->sprite_type == "shin") {
					this->incHealth(10);
					other->visible = false;
					other->collision = true;
					cout << other->sprite_type << "increased health" << endl;
				}
				else if (other->sprite_type == "buldak") {
					this->incHealth(20);
					other->visible = false;
					other->collision = true;
				}
			}

			if (other->sprite_type == "oh") {
				this->incHealth(15);
				other->visible = false;
				other->collision = true;
			}
		}

		else if (other->object_type == types::Type::PowerUp) {
			if (other->sprite_type == "eigenvector") {
				if (!(other->collision)) {
					curPowerUp = other;
					this->scaleX = scaleX * 0.5;
					this->scaleY = scaleY * 0.5;
					other->visible = false;
					other->collision = true;	
				}
			}
			if (other->sprite_type == "boost") {
				other->visible = false;
				this->hasPowerUp = true;
				if (this->hasPowerUp) {
					this->megaJump = true;
				}
				else if (!this->hasPowerUp) {
					this->megaJump = false;
				}
			}

			if (other->sprite_type == "transparency") {
				if (!(other->collision)) {
					other->visible = false;
					if (!this->hasPowerUp) {
						this->hasPowerUp = true;
						this->transparency = true;
						this->alpha = alpha / 2;
					}
					other->collision = true;
				}
			}
		}

		else if (other->object_type == types::Type::Weapon) {
			curWeapon = other;
			// add sprite as child of player but only for shooting animation
			// for simplicity... ig uess we won't have them carry the weapon all the time :")
		}
	}

	if (other->object_type == types::Type::TransitionPoint) {
			//toss a transition event later
			other->collision = true;
			other->collidable = false;
			cout << "Detected Collision with Transition Point" << endl;
			transparency, megaJump, doubleJump = false;
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
	if (envObj->sprite_type == "higgsboson") { 
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
	
	// eraser
	if (envObj->sprite_type == "eraser") {
		Game::instance->collisionSystem.resolveCollision(this, envObj, this->position.x - oldX, this->position.y - oldY, 0, 0);
		this->hasPowerUp = false;	
		this->megaJump = false;
	}

	// paint brush
	if (envObj->sprite_type == "paintbrush") { // if in contact with paint brush		
		envObj->position.y += _yVel; // fall with the player
	}

	// cloud platform
	if (envObj->object_type == types::Type::CloudPlatform) {
		// this is so player can stand on cloud
		envObj->_collision = true;
		Game::instance->collisionSystem.resolveCollision(this, envObj, this->position.x - oldX, this->position.y - oldY, 0, 0); 


	/*	if (Game::instance->collisionSystem.collidesWith(this, envObj)) { // are colliding
			this->isTouching = true; // true
		}
		else if (!Game::instance->collisionSystem.collidesWith(this, envObj)) // not colliding
			this->isTouching = false; // set to false
			if (!isTouching) {  // if false, turn off visibility 
				envObj->visible = false; // THIS IS A TEMPORARY SOLUTION. SHOULD REMOVE THE PLATFORM, NOT JUST MAKE IT INVISIBLEs
			}
			else {
				envObj->visible = true; 
			}
			*/
	
	}




	/* LINEAR ALGEBRA */
	//eigenvectors -> ?
	//theorem -> collected (probs separate from item bc u can only hold one item?)

	// GAME DESIGN: TAs are characters, Office Hours are "health" items
}



void Player::onEnemyCollision(Enemy* enemy){ 
	if (enemy->sprite_type == "coffee") {
		// dying = true;
		state->setDying(true);
		alpha = 75;
		this->play("idle");
		curTicks = ticks;
		this->dead();
	}

	/* PHYSICS */
	else if (enemy->sprite_type == "blackhole") {
		// dying = true;
		state->setDying(true);
		
		this->play("bh");
		curTicks = ticks;
		this->dead();
	}

	else if (enemy->sprite_type == "cat") {
		this->decHealth(10);
		limbo = true;
		alpha = 25;
		curTicks = ticks;
		enemy->state = 0;
		
	}


	/* ANIMATION */
	else if (enemy->sprite_type == "glitch") {
		this->position.x = rand() % 1196;
		this->position.y = rand() % 1584;
	}

	else if (enemy->sprite_type == "lamp") {
		this->decHealth(10);
		limbo = true;
		alpha = 25;
		curTicks = ticks;
	}


	/* LINEAR ALGEBRA */
	else if (enemy->sprite_type == "matrix") { 
		this->decHealth(10);
		if (!(enemy->collision)) {
			enemy->scaleX = enemy->scaleX * 1.1;
			enemy->scaleY = enemy->scaleY * 1.1;
			enemy->collision = true;	
		}
	}

		else if (enemy->sprite_type == "at") { 
		//this->decHealth(10);
		if (!(enemy->collision)) {
			enemy->scaleX = enemy->scaleX * 1.1;
			enemy->scaleY = enemy->scaleY * 1.1;
			this->scaleX = this->scaleX * 0.8;
			this->scaleY = this->scaleY * 0.8;
			enemy->collision = true;	
		}
	}

	else if (enemy->sprite_type == "projection") {
		this->decHealth(10);
		limbo = true;
		alpha = 25;
		curTicks = ticks;
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
	state->changeHealth(hp);

}

void Player::decHealth(int hp){
	state->changeHealth(-hp);
}

void Player::dead(){
	cout << "game over" << endl;
	// later replace this with game over scene
}

/* Other */

/*
void Player::emotions(String emotion){
	// show one of the displayobject children of player depending on its id
}
*/