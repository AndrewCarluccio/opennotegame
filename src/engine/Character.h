#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include "AnimatedSprite.h"
#include <vector>
#include <string>
#include <fstream>
#include "Sprite.h"
#include "Text.h"

using namespace std;

class Character : public AnimatedSprite{

public:
	Character();
	Character(string id, string path);
	virtual void update(set<SDL_Scancode> pressedKeys);
	virtual void draw(AffineTransform &at);
	virtual void onCollision(DisplayObject* other);

    string firstDialogue = "";
    string midDialogue = "";
    //vector<string> midDialogue;
    string itemDialogue = "";
    string postDialogue = "";

    string itemNeeded = "";
    string itemToGive = "";
    string itemPath = "";

	Text* text;
    
    bool talkedWith = false;
    bool receivedItem = false;

	bool collision = false;
	bool prev_collision = false;

	bool flipper = false;
	bool prev_flipper = false;

    DisplayObject* dialogueGenerator(DisplayObject* item);
	
private:

};

#endif


