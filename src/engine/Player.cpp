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
	addAnimation("resources/general_sprites/character/run_right/", "run", 8, 4, true);
	addAnimation("resources/general_sprites/character/run_left/", "run_l", 8, 4, true);
	addAnimation("resources/general_sprites/character/jump/", "jump", 8, 2, false);
	addAnimation("resources/general_sprites/character/", "idle", 1, 1, true);
	//shoot
	//shield
	//fly
}

void Player::update(set<SDL_Scancode> pressedKeys){
	AnimatedSprite::update(pressedKeys);
	oldY = this->position.y;
	oldX = this->position.x;


	if(c.holdRight){
		this->position.x += 4;
		c.holdRight = false;
		if(this->current != getAnimation("run")){
			this->play("run");
		}
	}

	else if (c.holdLeft){
		this->position.x -= 4;
		c.holdLeft = false;
		if(this->current != getAnimation("run_l")){
			this->play("run_l");
		}
	}

	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		if (_standing || (!_standing && doubleJump && jump < 2)) {
				this->_yVel = _jumpVel;
				this->position.y -= 6;
				this->play("jump");
				_standing = false;
				jumps++;
		}
	}

	if(_standing && !c.holdLeft && !c.holdRight) {
		jumps = 0;
		this->play("idle");
	}

	/* Calculate fall velocity */ // does this do anything
	_yAccCount++;
	if(_yAccCount == _yAcc){
		_yAccCount=0;
		_yVel++;
		if(_yVel > _maxFall) _yVel = _maxFall;
	}

	/* Actual falling depending on falling versus whether a jump occurred */
	this->position.y += _yVel;

	c.update(pressedKeys);
}

void Player::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

/* Collision Methods */

//Called automatically by collision system when something collides with the player
//our job is to simply react to that collision.
void Player::onCollision(DisplayObject* other){
	/*
	if(other->type == "AnimatedSprite"){
		MyGame::cs.resolveCollision(this, other, this->position.x - oldX, this->position.y - oldY);	
		_yVel = 0;
		_standing=true;
	}
	
	else if(other->type == "Enemy"){
		if(!this->iFrames){
			this->onEnemyCollision((Enemy*)other);
		}
	}*/
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



