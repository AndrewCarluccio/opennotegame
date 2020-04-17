#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "MyGame.h"
#include "../engine/Player.h"
#include "../engine/controls.h"
#include "../engine/CollisionSystem.h"
#include "../engine/Character.h"
#include "../engine/Enemy.h"
#include "../engine/EnvironmentalObject.h"


using namespace std;

MyGame::MyGame() : Game(597, 791) {

	//yeah, I know. going to replace this with loading from disk durring transition, or maybe only from a particular level at a time
	cout << "loading..." << endl;

	area1_1 = new Scene();
	/*
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
	*/

	area1_1->loadScene("./resources/Scenes/area2/level2-3.json");
	/*
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
	*/

	cout << "loaded!" << endl;

	cam = new Camera(1195, 1583);
	cam->setBounds(10000, 10000, 10000, 10000);
	cam->setZoom(0.5);

	dispatch = new EventDispatcher();
	tweenJuggler = new TweenJuggler(dispatch);
	scene_manager = new SceneManager(tweenJuggler,dispatch);

	scene_manager->active_scene = area1_1;

	player = (Player*)scene_manager->active_scene->getChild("player");
	player->loadAnimations();

	/*
	scene_manager->addTransitionPoint("transition to 1.2", 995, -25, 50, 2, area1_1, area1_2);
	scene_manager->addTransitionPoint("transition to 1.3", 165, 45, 50, 2, area1_2, area1_3);
	scene_manager->addTransitionPoint("transition to 1.4", 475, 1275, 50, 2, area1_3, area1_4);
	scene_manager->addTransitionPoint("transition to 1.5", 1005, 950, 50, 2, area1_4, area1_5);
	scene_manager->addTransitionPoint("transition to 1.6", 1010, 1430, 50, 2, area1_5, area1_6);

	scene_manager->addTransitionPoint("transition to 1.7", 765, 330, 50, 2, area1_6, area1_7);
	scene_manager->addTransitionPoint("transition to 1.8", 910, 710, 50, 2, area1_7, area1_8);
	scene_manager->addTransitionPoint("transition to 2.1", 625, -30, 50, 2, area1_8, area2_1);
	scene_manager->addTransitionPoint("transition to 2.2", -50, 1280, 50, 2, area2_1, area2_2);
	scene_manager->addTransitionPoint("transition to 2.3", -20, 1280, 50, 2, area2_2, area2_3);
	scene_manager->addTransitionPoint("transition to 2.4", 995, -50, 50, 2, area2_3, area2_4);
	scene_manager->addTransitionPoint("transition to 2.5", 995, -50, 50, 2, area2_4, area2_5);
	scene_manager->addTransitionPoint("transition to 2.6", 20, 35, 50, 2, area2_5, area2_6);
	scene_manager->addTransitionPoint("transition to 2.7", 995, -50, 50, 2, area2_6, area2_7);
	scene_manager->addTransitionPoint("transition to 2.8", 1015, 1275, 50, 2, area2_7, area2_8);

	scene_manager->addTransitionPoint("transition to 1.7", 800, 50, 50, 2, area1_6, area1_7);
	scene_manager->addTransitionPoint("transition to 1.8", 910, 85, 50, 2, area1_7, area1_8);
	scene_manager->addTransitionPoint("transition to 2.1", 900, 0, 50, 2, area1_8, area2_1);
	scene_manager->addTransitionPoint("transition to 2.2", -25, 1330, 50, 2, area2_1, area2_2);
	scene_manager->addTransitionPoint("transition to 2.3", 30, 1350, 50, 2, area2_2, area2_3);
	scene_manager->addTransitionPoint("transition to 2.4", 500, 275, 50, 2, area2_3, area2_4);
	scene_manager->addTransitionPoint("transition to 2.5", 75, 1185, 50, 2, area2_4, area2_5);
	scene_manager->addTransitionPoint("transition to 2.6", 70, 110, 50, 2, area2_5, area2_6);
	scene_manager->addTransitionPoint("transition to 2.7", 875, 1075, 50, 2, area2_6, area2_7);
	scene_manager->addTransitionPoint("transition to 2.8", 1040, 1325, 50, 2, area2_7, area2_8);
	*/

	//UserInterface = new UI();
	//UserInterface->loadInterface("./resources/UI/interface.json");

	//scene_manager->active_scene->addChild(UserInterface);	

	//cs->watchForCollisions("player", "sprite18");

	Game::instance->collisionSystem.watchForCollisions(types::Type::Platform, types::Type::Player);
	Game::instance->collisionSystem.watchForCollisions(types::Type::Platform, types::Type::Enemy);
	Game::instance->collisionSystem.watchForCollisions(types::Type::Player, types::Type::Enemy);
	Game::instance->collisionSystem.watchForCollisions(types::Type::Player, types::Type::Health);
	//Game::instance->collisionSystem.watchForCollisions(types::Type::Player, types::Type::EnvironmentalObject);
	Game::instance->collisionSystem.watchForCollisions(types::Type::Player, types::Type::Character);
	Game::instance->collisionSystem.watchForCollisions(types::Type::Player, types::Type::HiggsBoson);
	Game::instance->collisionSystem.watchForCollisions(types::Type::Player, types::Type::Eraser);
	Game::instance->collisionSystem.watchForCollisions(types::Type::Player, types::Type::PaintBrush);
	Game::instance->collisionSystem.watchForCollisions(types::Type::Platform, types::Type::PaintBrush);
	Game::instance->collisionSystem.watchForCollisions(types::Type::Item, types::Type::PaintBrush);
}

MyGame::~MyGame() {
}


void MyGame::update(set<SDL_Scancode> pressedKeys) {
	player->old_position.x = player->position.x;
	player->old_position.y = player->position.y;
	player->oldScaleX = player->scaleX;
	player->oldScaleY = player->scaleY;
	player->oldRotation = player->rotation;


	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
		cout << player->position.x << " " << player->position.y << endl;
	}
	/*
	else if (pressedKeys.find(SDL_SCANCODE_H) != pressedKeys.end()) {
		UserInterface->setHealth(UserInterface->getHealth()-10); //we will poll player for this eventually
	}
	*/
	
	
	player = (Player*)scene_manager->active_scene->getChild("player"); //need to update this pointer if scene changes
	scene_manager->processPosition(player->position.x, player->position.y);

	tweenJuggler->nextFrame();
	Game::update(pressedKeys);
	scene_manager->active_scene->update(pressedKeys);
	Game::instance->collisionSystem.update();

}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	scene_manager->active_scene->draw(at,cam,true);
	//UserInterface->draw(at);
	SDL_RenderPresent(Game::renderer);
}
