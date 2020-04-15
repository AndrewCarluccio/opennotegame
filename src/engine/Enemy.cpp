#include <iostream>
#include <cstdlib>
#include "Enemy.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "controls.h"
#include "EnvironmentalObject.h"
#include "Player.h"
#include "../main/MyGame.h"
#include "CollisionSystem.h"

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
}

void Enemy::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

/*
void Enemy::onCollision(DisplayObject* other) {
if (other->object_type == types::Type::Platform) {
		Game::instance->collisionSystem.resolveCollision(this, other, this->position.x - oldX, this->position.y - oldY, 0, 0);
		if(_yVel < 0)
			_yVel = 0;
			this->visible = false;
		int meY = this->getHitbox().y;
		int meH = this->getHitbox().h;
		int otherY = other->getHitbox().y;
		if (meY + meH <= otherY)
			_standing=true;
	}
}
*/

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