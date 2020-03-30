#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "MyGame.h"


using namespace std;

MyGame::MyGame() : Game(597, 791) {

	//yeah, I know. going to replace this with loading from disk durring transition, or maybe only from a particular level at a time
	cout << "loading..." << endl;

	area1_1 = new Scene();
	area1_2 = new Scene();
	area1_3 = new Scene();
	area1_4 = new Scene();
	area1_5 = new Scene();
	area1_6 = new Scene();
	area1_7 = new Scene();
	area1_8 = new Scene();

	area2_1 = new Scene();
	area2_2 = new Scene();
	area2_3 = new Scene();
	area2_4 = new Scene();
	area2_5 = new Scene();
	area2_6 = new Scene();
	area2_7 = new Scene();
	area2_8 = new Scene();

	area1_1->loadScene("./resources/Scenes/area1/level1-1.json");
	area1_2->loadScene("./resources/Scenes/area1/level1-2.json");
	area1_3->loadScene("./resources/Scenes/area1/level1-3.json");
	area1_4->loadScene("./resources/Scenes/area1/level1-4.json");
	area1_5->loadScene("./resources/Scenes/area1/level1-5.json");
	area1_6->loadScene("./resources/Scenes/area1/level1-6.json");
	area1_7->loadScene("./resources/Scenes/area1/level1-7.json");
	area1_8->loadScene("./resources/Scenes/area1/level1-8.json");
	area2_1->loadScene("./resources/Scenes/area2/level2-1.json");
	area2_2->loadScene("./resources/Scenes/area2/level2-2.json");
	area2_3->loadScene("./resources/Scenes/area2/level2-3.json");
	area2_4->loadScene("./resources/Scenes/area2/level2-4.json");
	area2_5->loadScene("./resources/Scenes/area2/level2-5.json");
	area2_6->loadScene("./resources/Scenes/area2/level2-6.json");
	area2_7->loadScene("./resources/Scenes/area2/level2-7.json");
	area2_8->loadScene("./resources/Scenes/area2/level2-8.json");

	cout << "loaded!" << endl;

	cam = new Camera(1195, 1583);
	cam->setBounds(10000, 10000, 10000, 10000);
	cam->setZoom(0.5);

	

	dispatch = new EventDispatcher();
	tweenJuggler = new TweenJuggler(dispatch);
	scene_manager = new SceneManager(tweenJuggler,dispatch);

	scene_manager->active_scene = area1_1;

	player = scene_manager->active_scene->getChild("player");

	scene_manager->addTransitionPoint("transition to 1.2", 995, -50, 50, 5, area1_1, area1_2);
	
}

MyGame::~MyGame() {
}


void MyGame::update(set<SDL_Scancode> pressedKeys) {
	if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		player->position.y -= 10;
		//car->position.x -= 6;
		//cam->moveCameraBy(5, 0);
	}
	else if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		player->position.x -= 10;
		//car->position.x += 6;
		//cam->moveCameraBy(-5, 0);
	}
	else if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		player->position.y += 10;
		//car->position.x += 6;
		//cam->moveCameraBy(-5, 0);
	}
	else if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		player->position.x += 10;
		//car->position.x += 6;
		//cam->moveCameraBy(-5, 0);
	}
	else if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
		cout << player->position.x << " " << player->position.y << endl;
	}

	scene_manager->processPosition(player->position.x, player->position.y);

	tweenJuggler->nextFrame();
	Game::update(pressedKeys);
	scene_manager->active_scene->update(pressedKeys);
}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	scene_manager->active_scene->draw(at,cam,true);
	//activeScene->draw(at);
	SDL_RenderPresent(Game::renderer);
}