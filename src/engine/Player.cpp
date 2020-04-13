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

	// 1195, 1583
	if (this->position.x  < 0) {
		this->position.x = 0;
	}
	else if (this->position.x + ((this->width) * (this->scaleX)) > 1195) {
		this->position.x = 1195 - ((this->width) * (this->scaleX));
	}

	if (this->position.y < 0) {
		this->position.y = 0;
	}
	else if (this->position.y + ((this->height) * (this->scaleY)) > 1583) {
		this->position.y = 1583 - ((this->height) * (this->scaleY));
		this->play("idle");
		_standing = true;
	}

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

	else if (c.pressJump) {
		if (_standing) {
			this->_yVel = _jumpVel;
			this->position.y -= 6;
			_standing = false;
			jumps++;
			//if(this->current != getAnimation("jump")){
				//this->play("jump");
		//}
		_standing = true;
		c.pressJump= false;
		}
	}

	else if(_standing && !c.holdLeft && !c.holdRight) {
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
//Resolves the collision that occurred between d and other
//xDelta1 and yDelta1 are the amount d moved before causing the collision.
//xDelta2 and yDelta2 are the amount other moved before causing the collision.
//Resolved using binary search to place objects as close as they can to one another
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


