#include "DevToolBar.h"

DevToolBar::DevToolBar(): DisplayObjectContainer() {
	// load resources.txt file to figure out filepaths of sprites
	std::ifstream in("resources.txt");
	std::string file;
	while (std::getline(in, file))
	{
		if(file.size() > 0)
			filenames.push_back(file);
	}
	updateChildren();

}

void DevToolBar::updateChildren() {
	for (int i = 0; i < this->children.size(); i++) {
		delete children[i];
	}

	this->children.clear();

	for (int i = current_pos; i < min(current_pos + 12, (int)filenames.size()); i++) {
		Sprite *sprite = new Sprite("test" + to_string(i), filenames[i]);
		sprite->scaleX = 100.0 / sprite->width;
		sprite->scaleY = 100.0 / sprite->height;
		sprite->position.x = 100 * (i - current_pos);
		this->addChild(sprite);
	}
	
}

void DevToolBar::update(set<SDL_Scancode> pressedKeys) {


	// need these flags to check for single key presses
	if(pressedKeys.find(SDL_SCANCODE_1) == pressedKeys.end()) {
		prevClicked = true;
	}

	if(pressedKeys.find(SDL_SCANCODE_2) == pressedKeys.end()) {
		nextClicked = true;
	}

	if(prevClicked && pressedKeys.find(SDL_SCANCODE_1) != pressedKeys.end()) {
		if(current_pos - 12 >= 0) {
			current_pos -= 12;
			updateChildren();
		}
		prevClicked = false;
	}

	
	if(nextClicked && pressedKeys.find(SDL_SCANCODE_2) != pressedKeys.end()) {
		if (current_pos + 12 < filenames.size()) {
			current_pos += 12;
			updateChildren();
		}
		nextClicked = false;
	}




    DisplayObjectContainer::update(pressedKeys);
}

void DevToolBar::draw(AffineTransform &at) {
    DisplayObjectContainer::draw(at);
}