#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "controls.h"
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
	addAnimation("resources/general_sprites/character/jump/", "jump", 8, 2, false);
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
		if(this->current != getAnimation("run")){
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
		if(this->current != getAnimation("run_l")){
			this->play("run_l");
		}
		if (lowHealth) {
			this->position.x -= 4; // limited controls when health is low
		}
		else {
		this->position.x += 10; // move to left
		}

		c.holdLeft = false;
	}

	else if (c.pressJump) {
		if (_standing) {
			_standing = false;
			this->_yVel = _jumpVel; 
			jumps++; // account for possible double jumps
			if (megaJump) {
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

		//if(this->current != getAnimation("jump")){
			//this->play("jump");
		//}
	}

	else if(_standing && !c.holdLeft && !c.holdRight) {
		jumps = 0; 
		//this->play("idle");
		if(this->current != getAnimation("idle")) {
			this->play("idle");
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



	c.update(pressedKeys);
}

void Player::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

/* Collision Methods */

//Called automatically by collision system when something collides with the player
//our job is to simply react to that collision.
void Player::onCollision(DisplayObject* other){
	if(other->type == "AnimatedSprite"){
		//Game::instance->collisionSystem.resolveCollision(this, other, this->position.x - this->old_position.x, this->position.y - oldY, oldX, oldY);	
		_yVel = 0;
		_standing=true;
	}
	/*
	else if(other->type == "Enemy"){
		if(!this->iFrames){
			this->onEnemyCollision((Enemy*)other);
		}
	}
	*/
}

/*void Player::onEnemyCollision(Enemy* enemy){
	this->health -= enemy->damage;
	this->initIFrames(120);
}
*/

void dead() {
	
}

// what is this lol
/*
void Player::initIFrames(int numFrames){
	this->iFrameCount = 0;
	this->numIFrames = numFrames;
	this->iFrames = true;
}
*/


