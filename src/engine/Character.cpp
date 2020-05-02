#include <iostream>
#include <cstdlib>
#include "Character.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "controls.h"
#include "Character.h"
#include "../main/MyGame.h"
#include "CollisionSystem.h"
#include "Types.h"

using namespace std;

Character::Character(string id, string path) : AnimatedSprite(id, path){
	this->type = "Character";
	text = new Text(firstDialogue);
	text->visible = false;
	//text->position = {598, 792};
	this->addChild(text);
	thinking->visible = false;
	//thinking->position.x = this->position.x;
	//thinking->position.y = this->position.y - 200;
	// force text to be on the screen

}

void Character::update(set<SDL_Scancode> pressedKeys){
	AnimatedSprite::update(pressedKeys);
	/*
	if (playerNearby) {
		thinking->visible = true;
		if (pressedKeys.find(SDL_SCANCODE_RETURN) != pressedKeys.end()) {
			cout << "????" << endl;
			if (text->visible = false) {
				cout << "does this happen" << endl;
				text->visible = true;
			}
			if (text->visible = true) {
				cout << "does THIS happen";
				text->visible = false;
			}
		}
	}
	*/
	if (collision) {
		prev_collision = true;
		collision = false;
	}
	else if (prev_collision && !collision) {
		cout << "left" << endl;
		prev_collision = false;
		collision = false;
		text->visible = false;
	}
	
}

void Character::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

void Character::onCollision(DisplayObject* other){
	collision = true;
    //cout << "display thought bubble" << endl;
    // display thought bubble
	if (!text->visible) {
		//text = new Text(firstDialogue);
		Player* hero = (Player *)other;
		this->dialogueGenerator(hero->curItem);
		text->visible = true;
		//this->addChild(text);
	}	
}

DisplayObject* Character::dialogueGenerator(DisplayObject* item) {
    if (!talkedWith) {
        talkedWith = true;
        cout << firstDialogue << endl; // replace with UI trigger
		text->updateText(firstDialogue);
        return item;
    }

    if (item != NULL) {
        if (item->sprite_type == itemNeeded) {
            receivedItem = true;
            cout << itemDialogue << endl;
			text->updateText(itemDialogue);
            DisplayObject* newItem = new DisplayObject(itemToGive, itemPath);
            newItem->sprite_type = itemToGive;
			newItem->object_type = types::Type::Character;
            return newItem;
        }
    }

    if (receivedItem) {
        cout << postDialogue << endl;
		text->updateText(postDialogue);
        return item;
    }

    else {
        cout << midDialogue << endl;
		text->updateText(midDialogue);
        return item;
    }
}