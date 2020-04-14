#include <iostream>
#include <cstdlib>
#include "EnvironmentalObject.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "controls.h"
//#include "Enemy.h"
//#include "Player.h"
#include "../main/MyGame.h"
#include "CollisionSystem.h"

using namespace std;

EnvironmentalObject::EnvironmentalObject(string id, string path) : AnimatedSprite(id, path){
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

// on Collision override