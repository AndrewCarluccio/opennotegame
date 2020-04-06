#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "controls.h"


using namespace std;


Player::Player(string id, string path) : AnimatedSprite(id, path){

	this->type = "Player";
	
}

// careful to not do this in a loop, uses a lot of memory
void Player::loadAnimations() {
	addAnimation("resources/general_sprites/character/run/", "run", 8, 2, true);
	addAnimation("resources/general_sprites/character/jump/", "jump", 8, 2, false);
	addAnimation("resources/general_sprites/character/", "idle", 1, 1, true);
	// play("jump");
}

//Called automatically by collision system when something collides with the player
//our job is to simply react to that collision.

/*
void Player::onCollision(DisplayObject* other){
	if(other->type == "Platform"){
		Game::instance->collisionSystem.resolveCollision(this, other, this->x - oldX, this->y - oldY);	
		_yVel = 0;
		_standing=true;
	}
	else if(other->type == "Enemy"){
		if(!this->iFrames){
			this->onEnemyCollision((Enemy*)other);
		}
	}

}
*/



void Player::update(set<SDL_Scancode> pressedKeys){
	AnimatedSprite::update(pressedKeys);
	oldY = this->position.y;
	oldX = this->position.x;

	//Movement arrow keys
	//Controls is a class we wrote that just checks the SDL Scancode values and game controller values in one check
	/*if(c.holdRight()){
		this->position.x += 4;
		this->flipH = false;
		if(_standing){
			this->play("run");
		}
	}
	else if (c.holdLeft()){
		this->position.x -= 4;
		this->flipH = true;
		if(_standing){
			this->play("run");
		}
	}
	*/

  	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		this->position.x -= 6;
		//cam->moveCameraBy(5, 0);
	}
	if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		this->position.x += 6;
		//cam->moveCameraBy(-5, 0);
	}

	if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		this->_yVel = _jumpVel;
		this->position.y -= 6;
		_standing = false;
		//cam->moveCameraBy(-5, 0);
	}


	
	
	//play idle animation if player is just standing still on ground
	if(_standing && !c.holdLeft() && !c.holdRight()) {
		// play("idle");
	
	}
	

	/* handle iFrames if player was hit by enemy recently */
	if(this->iFrames){
		this->visible = this->iFrameCount%2 == 0;
		this->iFrameCount++;
		if(this->iFrameCount == this->numIFrames){
			this->iFrames = false;
			this->visible = true;
		}
	}

	/* Calculate fall velocity */
	_yAccCount++;
	if(_yAccCount == _yAcc){
		_yAccCount=0;
		_yVel++;
		if(_yVel > _maxFall) _yVel = _maxFall;
	}


	/* Jumping */
	if(_standing && c.pressJump()){
	//	this->_yVel = _jumpVel;
	//	_standing = false;
		// cout << "should jump" << endl;
	}

	/* Actual falling depending on falling versus whether a jump occurred */
	this->position.y += _yVel;


	c.update(pressedKeys);

}

/*void Player::onEnemyCollision(Enemy* enemy){
	this->health -= enemy->damage;
	this->initIFrames(120);
}
*/

void Player::initIFrames(int numFrames){
	this->iFrameCount = 0;
	this->numIFrames = numFrames;
	this->iFrames = true;
}

void Player::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

