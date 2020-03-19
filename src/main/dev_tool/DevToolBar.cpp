#include "DevToolBar.h"

DevToolBar::DevToolBar(): DisplayObjectContainer() {
    vector<string> filenames = {"Jump_5.png", "Idle_2.png","Idle_15.png","Jump_3.png","Idle_5.png", "Jump_23.png", "Idle_2.png","Run_10.png","Jump_3.png","Walk_15.png", "Run_5.png", "Jump_2.png"};
	for (int i = 0; i < filenames.size(); i++) {
		Sprite *sprite = new Sprite("test" + to_string(i), "./resources/character/" + filenames[i]);
		sprite->scaleX = 100.0 / sprite->width;
		sprite->scaleY = 100.0 / sprite->height;
		sprite->position.x = 100 * i;
		this->addChild(sprite);
	}

}

void DevToolBar::update(set<SDL_Scancode> pressedKeys) {
    DisplayObjectContainer::update(pressedKeys);
}

void DevToolBar::draw(AffineTransform &at) {
    DisplayObjectContainer::draw(at);
}