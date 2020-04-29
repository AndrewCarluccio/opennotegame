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
const bool ZOOMED_IN = false;// Set this to false to revert to original camera change the comment below

using namespace std;
MyGame::MyGame() : Game(597, 791) {  // Comment this for zoom in  == true
// MyGame::MyGame() : Game(1340, 791) {	// comment this for zoom out
	
	//yeah, I know. going to replace this with loading from disk durring transition, or maybe only from a particular level at a time
	cout << "loading..." << endl;
	a1_1_path = "./resources/Scenes/area1/level1-1.json";
	a1_2_path = "./resources/Scenes/area1/level1-2.json";
	a1_3_path = "./resources/Scenes/area1/level1-3.json";
	a1_4_path = "./resources/Scenes/area1/level1-4.json";
	a1_5_path = "./resources/Scenes/area1/level1-5.json";
	a1_6_path = "./resources/Scenes/area1/level1-6.json";
	a1_7_path = "./resources/Scenes/area1/level1-7.json";
	a1_8_path = "./resources/Scenes/area1/level1-8.json";
	
	a2_1_path = "./resources/Scenes/area2/level2-1.json";
	a2_2_path = "./resources/Scenes/area2/level2-2.json";
	a2_3_path = "./resources/Scenes/area2/level2-3.json";
	a2_4_path = "./resources/Scenes/area2/level2-4.json";
	a2_5_path = "./resources/Scenes/area2/level2-5.json";
	a2_6_path = "./resources/Scenes/area2/level2-6.json";
	a2_7_path = "./resources/Scenes/area2/level2-7.json";
	a2_8_path = "./resources/Scenes/area2/level2-8.json";

	a3_1_path = "./resources/Scenes/area3/level3-1.json";
	a3_2_path = "./resources/Scenes/area3/level3-2.json";
	a3_3_path = "./resources/Scenes/area3/level3-3.json";
	a3_4_path = "./resources/Scenes/area3/level3-4.json";
	a3_5_path = "./resources/Scenes/area3/level3-5.json";
	a3_6_path = "./resources/Scenes/area3/level3-6.json";
	a3_7_path = "./resources/Scenes/area3/level3-7.json";
	a3_8_path = "./resources/Scenes/area3/level3-8.json";

	a4_1_path = "./resources/Scenes/area4/level4-1.json";
	a4_2_path = "./resources/Scenes/area4/level4-2.json";
	a4_3_path = "./resources/Scenes/area4/level4-3.json";
	a4_4_path = "./resources/Scenes/area4/level4-4.json";
	a4_5_path = "./resources/Scenes/area4/level4-5.json";
	a4_6_path = "./resources/Scenes/area4/level4-6.json";
	a4_7_path = "./resources/Scenes/area4/level4-7.json";
	a4_8_path = "./resources/Scenes/area4/level4-8.json";

	a1_1_name = "area1_1";
	a1_2_name = "area1_2";
	a1_3_name = "area1_3";
	a1_4_name = "area1_4";
	a1_5_name = "area1_5";
	a1_6_name = "area1_6";
	a1_7_name = "area1_7";
	a1_8_name = "area1_8";
	
	a2_1_name = "area2_1";
	a2_2_name = "area2_2";
	a2_3_name = "area2_3";
	a2_4_name = "area2_4";
	a2_5_name = "area2_5";
	a2_6_name = "area2_6";
	a2_7_name = "area2_7";
	a2_8_name = "area2_8";

	a3_1_name = "area3_1";
	a3_2_name = "area3_2";
	a3_3_name = "area3_3";
	a3_4_name = "area3_4";
	a3_5_name = "area3_5";
	a3_6_name = "area3_6";
	a3_7_name = "area3_7";
	a3_8_name = "area3_8";

	a4_1_name = "area4_1";
	a4_2_name = "area4_2";
	a4_3_name = "area4_3";
	a4_4_name = "area4_4";
	a4_5_name = "area4_5";
	a4_6_name = "area4_6";
	a4_7_name = "area4_7";
	a4_8_name = "area4_8";

	scene = new Scene();
	scene->loadScene("./resources/Scenes/camera_demo.json");

	car = scene->getChild("Car");

	activeScene = scene;

	cam = new Camera(1200, 1000);
	cam->setBounds(1000, 1000, 1000, 1000);
	cam->setZoom(1);

	myPlayer = new Player(scene->getChild("Car"));
	
	all_names.push_back(a2_1_name);
	all_names.push_back(a2_2_name);
	all_names.push_back(a2_3_name);
	all_names.push_back(a2_4_name);
	all_names.push_back(a2_5_name);
	all_names.push_back(a2_6_name);
	all_names.push_back(a2_7_name);
	all_names.push_back(a2_8_name);

	all_names.push_back(a3_1_name);
	all_names.push_back(a3_2_name);
	all_names.push_back(a3_3_name);
	all_names.push_back(a3_4_name);
	all_names.push_back(a3_5_name);
	all_names.push_back(a3_6_name);
	all_names.push_back(a3_7_name);
	all_names.push_back(a3_8_name);

	all_names.push_back(a4_1_name);
	all_names.push_back(a4_2_name);
	all_names.push_back(a4_3_name);
	all_names.push_back(a4_4_name);
	all_names.push_back(a4_5_name);
	all_names.push_back(a4_6_name);
	all_names.push_back(a4_7_name);
	all_names.push_back(a4_8_name);

	default_area = new Scene();
	default_area->loadScene("./resources/Scenes/area1/level1-1.json");
	//"./resources/Scenes/cp_ep_demo2.json"
	Game::instance->collisionSystem.updateWithNewScene((DisplayObjectContainer *)default_area->getChild("Root"));

	cout << "loaded!" << endl;

	cam = new Camera(1195, 1583);
	cam->setBounds(10000, 10000, 10000, 10000);
	if(ZOOMED_IN == true){
		cam->setZoom(1.125);
	}
	else{
		cam->setZoom(.5);
	}

	dispatch = new EventDispatcher();
	//TweenListener* carTweenListen = new TweenListener();
	coinExpandTween = new Tween(coin);

	coinTweenListen = new TweenListener();

	coinTweenListen->myTween = coinExpandTween;

	dispatch->addEventListener(coinTweenListen,TweenEvent::TWEEN_END_EVENT);
	tweenJuggler = new TweenJuggler(dispatch);

	Tween* carEntryTween = new Tween(car);
	carEntryTween->animate(TweenableParams::ALPHA, 0, 255, 2);

	tweenJuggler->add(carEntryTween);

	//sfx = new Sound();
	//sfx->playMusic();
}

MyGame::~MyGame() {
}


void MyGame::update(set<SDL_Scancode> pressedKeys) {
	player->old_position.x = player->position.x;
	player->old_position.y = player->position.y;
	player->oldScaleX = player->scaleX;
	player->oldScaleY = player->scaleY;
	player->oldRotation = player->rotation;

	if(ZOOMED_IN == true && player->position.y > 400) { // have the camera follow the player
		cam->moveCameraTo(0, (400 - player->position.y));
	}

	if (pressedKeys.find(SDL_SCANCODE_P) != pressedKeys.end()) {
		cout << player->position.x << " " << player->position.y << endl;
	}
	else if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
		cam->moveCameraBy(-5, 0);
	}

	if (car->position.y < 200) {
		cam->zoom = 2;
	}
	else {
		cam->zoom = 1;
	}
	
	Game::update(pressedKeys);
	activeScene->update(pressedKeys);
	myPlayer->update(pressedKeys);
}

void MyGame::draw(AffineTransform& at) {
	Game::draw(at);
	SDL_RenderClear(Game::renderer);
	activeScene->draw(at,cam);
	SDL_RenderPresent(Game::renderer);
	// myPlayer->draw();
}