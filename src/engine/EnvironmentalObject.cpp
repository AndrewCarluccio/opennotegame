#include <iostream>
#include <cstdlib>
#include "EnvironmentalObject.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "controls.h"
//#include "Enemy.h"
#include "Player.h"
#include "../main/MyGame.h"
#include "CollisionSystem.h"

using namespace std;

EnvironmentalObject::EnvironmentalObject() {
}

EnvironmentalObject::EnvironmentalObject(string id, string path) : AnimatedSprite(id, path) {
	this->type = "EnvironmentalObject";
}

// careful to not do this in a loop, uses a lot of memory
void EnvironmentalObject::loadAnimations() {
	
}

void EnvironmentalObject::update(set<SDL_Scancode> pressedKeys){
	AnimatedSprite::update(pressedKeys);
}

void EnvironmentalObject::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

void EnvironmentalObject::onCollision(DisplayObject* other) {
	// very specific to the paintbrush envObj
	if (other->object_type == types::Type::Platform) {
		Game::instance->collisionSystem.resolveCollision(this, other, this->position.x - oldX, this->position.y - oldY, 0, 0);
		if (this->object_type == types::Type::PaintBrush) {
		if(_yVel < 0)
		_yVel = 0;
		this->visible = false;
		paintBrushTouched = true;
		int meY = this->getHitbox().y;
		int meH = this->getHitbox().h;
		int otherY = other->getHitbox().y;
		if (meY + meH <= otherY)
			_standing=true;
		}
	}

	if (other->object_type == types::Type::Item) {
		other->visible = false;
		if (paintBrushTouched) {
			other->visible = true;
		}
	}
}