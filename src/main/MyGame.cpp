#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "MyGame.h"

using namespace std;

MyGame::MyGame() : Game(1200, 1000) {
	//instance = this;

	scene = new Scene();
	scene->loadScene("./resources/Scenes/camera_demo.json");

	car = scene->getChild("Car");

	activeScene = scene;

	cam = new Camera(1200, 1000);
	cam->setBounds(1000, 1000, 1000, 1000);
	cam->setZoom(1);

	myPlayer = new Player(scene->getChild("Car"));
	
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
	if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		cam->moveCameraBy(5, 0);
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