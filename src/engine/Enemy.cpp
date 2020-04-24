#include <iostream>
#include <cstdlib>
#include "Enemy.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "controls.h"
#include "EnvironmentalObject.h"
#include "../main/MyGame.h"
#include "CollisionSystem.h"
#include <cmath>


using namespace std;

Enemy::Enemy() {
}

Enemy::Enemy(string id, string path) : AnimatedSprite(id, path) {
	this->type = "Enemy";
}


// careful to not do this in a loop, uses a lot of memory
void Enemy::loadAnimations() {
	
}

void Enemy::update(set<SDL_Scancode> pressedKeys){
	AnimatedSprite::update(pressedKeys);
// state 0 = one time state to kick things off
// state 1 = patrolling
// state 2 = lunging
// state 3 = body slamming
// state 4 = shielding
// state 5 = shooting
// state 6 = post-attack movement
// state 7 = stunned



// THIS IS A JANK WAY OF DOING IT
// IM SO SORRY

if (this->sprite_type ==  "cat") {
	if (gd == 1) {
		this->position.x +=1;
	}
	if (this->position.x >= maxPatX) {
		gd = 2;
	}
	if (gd == 2) {
		this->position.x -=1;
	}

	if (this->position.x <= minPatX) {
		gd = 1;
	}
}
// need to do this from enemy side
// but only understand onCollision for player :(
if (this->sprite_type == "matrix") {
	this->state = 0;
}

	if (this->state == 0) {
		setPatrolRange();
	}
	else if (this->state == 1) {
		patrol();
	}
	else if (this->state == 2) {
		lunge();
	}
	else if (this->state == 3) {
		bodySlam();
	}
	else if (this->state == 4) {
		shield();
	}
	else if (this->state == 5) {
		shoot();
	}
	else if (this->state == 6) {
		// do something to move the target
 	}
 	else if (this->state == 7) {
	 	// do something to show they are stunned
 	}



	if (this->state == 0) {
		this->state = 1;
		this->targX = std::rand()%(this->maxPatX-this->minPatX) + this->minPatX;
		this->targY = std::rand()%(this->maxPatY-this->minPatY) + this->minPatY;
		this->vel = 0;
	}
}

void Enemy::onCollision(DisplayObject* other) {
if (other->object_type == types::Type::Platform) {
		Game::instance->collisionSystem.resolveCollision(this, other, this->position.x - oldX, this->position.y - oldY, 0, 0);
		if(_yVel < 0)
			_yVel = 0;
			//this->visible = false;
		int meY = this->getHitbox().y;
		int meH = this->getHitbox().h;
		int otherY = other->getHitbox().y;
		if (meY + meH <= otherY)
			_standing=true;
	}
}


void Enemy::incHealth(int hp){
	health += hp;
	if (health > maxHealth){
		health = maxHealth;
	}
	else if (health > lowHealthThreshold){ 
		lowHealth = false;
	}
}

void Enemy::decHealth(int hp){
	health -= hp;
	if (health <= 0){
//		this->dead();
	}
	else if (health < lowHealthThreshold){ 
		lowHealth = true;
	}
}

void Enemy::dead(){
	// remove from do tree
}

void Enemy::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

void Enemy::setPatrolRange() {
	this->minPatX = this->position.x-20;
	this->maxPatX = this->position.x+20;
	this->minPatY = this->position.y-10;
	this->maxPatY = this->position.y+10;
}

void Enemy::patrol() {
	/*if (isTargetReached()) {
		this->targX = std::rand()%(this->maxPatX-this->minPatX) + this->minPatX;
		this->targY = std::rand()%(this->maxPatY-this->minPatY) + this->minPatY;
		this->vel = 0;
		this->maxVel = 4;		
	}
	else {
		moveToTarget();
	}
	*/
}

void Enemy::moveToTarget() {
	//this->vel = std::min(this->vel+this->acc, this->maxVel);
	double theta = std::atan2(std::abs(this->targY - this->position.y),std::abs(this->targX - this->position.x));
	double xComp = this->vel*std::cos(theta);
	double yComp = this->vel*std::sin(theta);
	if(this->targX - this->position.x < 0) xComp *= -1;
	if(this->targY - this->position.y < 0) yComp *= -1;

}

bool Enemy::isTargetReached() {
	return std::abs(this->position.x-this->targX) <= 6 && std::abs(this->position.y-this->targY) <= 6;
}

void Enemy::lunge() {
	this->vel += maxVel; // make him move fast
	moveToTarget();
	// play animation of lunging 
}

void Enemy::bodySlam() {
	this->vel += maxVel; // make him fast
	lunge();
	this->position.y -= vel; // move him up at high speed
	_yAccCount++;
	if(_yAccCount == _yAcc){
		_yAccCount=0;
		_yVel++;
		if(_yVel < _maxFall) {
			_yVel = _maxFall; // fall quickly down (?)
		}
	}
}

void Enemy::shield() {
	// TO DO

}

void Enemy::shoot() {
	// TO DO
}