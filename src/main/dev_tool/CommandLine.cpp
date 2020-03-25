#include "CommandLine.h"

CommandLine::CommandLine(DevTool *instance) {
    this->instance = instance;
}

void CommandLine::run() {
    while(true) {
		cout << ">>";
		string command;
		cin >> command;
		if (command == "load") {
			load();
		} else if (command == "save") {
			save();
		} else if (command == "id") {
			updateId();
		} else if (command == "layer") {
			updateLayer();
		}
	}
}

void CommandLine::load() {
	cout << "Type the name of a scene file inside ./resources/Scenes, ex. camera_demo.json" << endl;
	string filename;
	cin >> filename;
	instance->scene_lock.lock();
	delete instance->activeScene;
	instance->activeScene = new Scene();
	instance->activeScene->loadScene("./resources/Scenes/" + filename);
	instance->activeScene->root->position.y = 100;
	instance->selectedLayer = instance->activeScene->foreground;
	instance->scene_lock.unlock();
}

void CommandLine::save() {
	cout << "Type the name of the file you want to save the scene as, ex. scene.json" << endl;
	string filename;
	cin >> filename;
	SceneWriter sw(instance->activeScene);
	sw.saveScene("./resources/Scenes/" + filename);
}

void CommandLine::updateId() {
	if (instance->clickedSprite != NULL) {
		cout << "Old id: " << instance->clickedSprite->id << endl;
		cout << "Type the new id of the selected sprite" << endl;
		string newId;
		cin >> newId;
		instance->clickedSprite->id = newId;
	} else {
		cout << "No sprite selected" << endl;
	}
}

void CommandLine::updateLayer() {
	string newLayer;
	cin >> newLayer;
	if (newLayer == "fg") {
		instance->selectedLayer = instance->activeScene->foreground;
	} else if (newLayer == "mg") {
		instance->selectedLayer = instance->activeScene->midground;
	} else if (newLayer == "bg") {
		instance->selectedLayer = instance->activeScene->background;
	} else {
		cout << "invalid syntax. layer [fg mg bg]" << endl;
	}
}