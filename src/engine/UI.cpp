#include "UI.h"

#include <iostream>
#include <queue>
//#include <Windows.h>

using namespace std;

UI::UI() : Scene() {
	//Scene::root = new DisplayObjectContainer();
}

void UI::setHealth(int h) {
	health = h;


	if (health < 10) {
		health_meter->alpha = 0;
		health_meter = this->getChild("pencil_10");
		health_meter->alpha = 255;
	}
	else if (health < 20) {
		health_meter->alpha = 0;
		health_meter = this->getChild("pencil_20");
		health_meter->alpha = 255;
	}
	else if (health < 30) {
		health_meter->alpha = 0;
		health_meter = this->getChild("pencil_30");
		health_meter->alpha = 255;
	}
	else if (health < 40) {
		health_meter->alpha = 0;
		health_meter = this->getChild("pencil_40");
		health_meter->alpha = 255;
	}
	else if (health < 50) {
		health_meter->alpha = 0;
		health_meter = this->getChild("pencil_50");
		health_meter->alpha = 255;
	}
	else if (health < 60) {
		health_meter->alpha = 0;
		health_meter = this->getChild("pencil_60");
		health_meter->alpha = 255;
	}
	else if (health < 70) {
		health_meter->alpha = 0;
		health_meter = this->getChild("pencil_70");
		health_meter->alpha = 255;
	}
	else if (health < 80) {
		health_meter->alpha = 0;
		health_meter = this->getChild("pencil_80");
		health_meter->alpha = 255;
	}
	else if (health < 90) {
		health_meter->alpha = 0;
		health_meter = this->getChild("pencil_90");
		health_meter->alpha = 255;
	}
	else if (health < 100) {
		health_meter->alpha = 0;
		health_meter = this->getChild("pencil_100");
		health_meter->alpha = 255;
	}

}

int UI::getHealth() {
	return health;
}

void UI::loadInterface(string sceneFilePath) {
	Scene::loadScene(sceneFilePath);
	health_meter = this->getChild("pencil_100");
}

DisplayObject* UI::getChild(string id) {
	return Scene::root->getChild(id);
}

void UI::update(set<SDL_Scancode> pressedKeys) {
	Scene::update(pressedKeys);
	//root->update(pressedKeys);
}

void UI::draw(AffineTransform& at) {
	Scene::draw(at);
	//root->draw(at);
}

void UI::draw(AffineTransform& at, Camera* cam, bool paralax) {
	Scene::draw(at,cam,paralax);
}

