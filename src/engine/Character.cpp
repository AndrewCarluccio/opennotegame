#include <iostream>
#include <cstdlib>
#include "Character.h"
#include "AnimatedSprite.h"
#include "Sprite.h"
#include "controls.h"
#include "Character.h"
#include "../main/MyGame.h"
#include "CollisionSystem.h"

using namespace std;

Character::Character(string id, string path) : AnimatedSprite(id, path){
	this->type = "Character";
}

void Character::update(set<SDL_Scancode> pressedKeys){
	AnimatedSprite::update(pressedKeys);
}

void Character::draw(AffineTransform &at){
	AnimatedSprite::draw(at);
}

void Character::onCollision(DisplayObject* other){
    cout << "display thought bubble" << endl;
    // display thought bubble
}

DisplayObject* Character::dialogueGenerator(DisplayObject* item) {
    if (!talkedWith) {
        talkedWith = true;
        cout << firstDialogue << endl; // replace with UI trigger
        return item;
    }

    if (item != NULL) {
        if (item->sprite_type == itemNeeded) {
            receivedItem = true;
            cout << itemDialogue << endl;
            DisplayObject* newItem = new DisplayObject(itemToGive, itemPath);
            newItem->sprite_type = itemToGive;
            return newItem;
        }
    }

    if (receivedItem) {
        cout << postDialogue << endl;
        return item;
    }

    else {
        cout << midDialogue << endl;
        return item;
    }
}