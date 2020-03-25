#include "DevTool.h"


using namespace std;

int GRID_SIZE = 25;

DevTool::DevTool() : Game(1200, 1000) {
	bar = new DevToolBar();
	
	cam = new Camera(1200, 1000);
	cam->setBounds(10000, 10000, 10000, 10000);
	cam->setZoom(zoom);

	scene = new Scene();

	scene->loadScene("./resources/Scenes/empty.json");


	CommandLine *cmdLine = new CommandLine(this);

	thread cmdThread(&CommandLine::run, cmdLine);
	cmdThread.detach();

	scene_lock.lock();
	activeScene = scene;
	activeScene->root->position.y = 100;
	selectedLayer = activeScene->foreground;
	scene_lock.unlock();
}

DevTool::~DevTool() {
}

bool mouseWithinBounds(DisplayObject *sprite, int mouseX, int mouseY) {
	return mouseY > sprite->globalPos.y &&
		mouseY < sprite->globalPos.y + sprite->globalH &&
		mouseX > sprite->globalPos.x &&
		mouseX < sprite->globalPos.x + sprite->globalW;


}

void DevTool::update(set<SDL_Scancode> pressedKeys) {
	
	Game::update(pressedKeys);

	// handling mouse
	if(mousePressedDown && initialClick) {
		if(mouseY < 100) {
			int copyIndex = mouseX / 100;
			DisplayObject *toCopy = bar->getChild(copyIndex);
			if (toCopy != NULL) {
				Sprite* newSprite = new AnimatedSprite("sprite" + to_string(spriteCount), toCopy->imgPath);
				spriteCount++;
				// newSprite->scaleX = 100.0 / newSprite->width;
				// newSprite->scaleY = 100.0 / newSprite->height;
				newSprite->position.x = (mouseX) - newSprite->globalW;
				newSprite->position.y = (mouseY) - newSprite->globalH;
				clickedSprite = newSprite;
				selectedLayer->addChild(clickedSprite);
			}
		} else {

			vector<DisplayObject*> sprites (selectedLayer->children);
			while (!sprites.empty()) {
				DisplayObjectContainer *sprite = (DisplayObjectContainer*)(sprites.back());
				sprites.pop_back();
				if (mouseWithinBounds(sprite, mouseX, mouseY)) {
					sprite->parent->moveChildToFront(sprite->id);
					clickedSprite = sprite;
					break;
				} else {
					if(!sprite->children.empty()) {
						sprites.insert(sprites.end(), sprite->children.begin(), sprite->children.end());

					}
				}

			}
		}

		initialClick = false;
	} else if(mousePressedDown) {
		if (clickedSprite != NULL) {
			// cout << mouseX - prevMouseX << endl;
			clickedSprite->position.x += 2 *(mouseMotionX / zoom);
			clickedSprite->position.y += 2 *(mouseMotionY / zoom);
		}
	}

	if(!mousePressedDown && initialRelease) {
		if (clickedSprite != NULL) {
			clickedSprite->position.x = (int)(round(clickedSprite->position.x / (double)GRID_SIZE) * GRID_SIZE);
			clickedSprite->position.y = (int)(round(clickedSprite->position.y / (double)GRID_SIZE) * GRID_SIZE);
		}
		initialRelease = false;
	}

	// sprite scaling with W, A, S, and D keys
	if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) {
			// car->position.x -= 6;
		if (clickedSprite != NULL) {
			clickedSprite->scaleX += 0.01;
		}
	}

	else if (pressedKeys.find(SDL_SCANCODE_A) != pressedKeys.end()) {
		if (clickedSprite != NULL) {
			clickedSprite->scaleX -= 0.01;
		}
	}

	if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end()) {
		if (clickedSprite != NULL) {
			clickedSprite->scaleY += 0.01;
		}
	}
	else if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) {
		if (clickedSprite != NULL) {
			clickedSprite->scaleY -= 0.01;
		}
	}

	// panning around scene using arrow keys
	if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
		cam->moveCameraBy(GRID_SIZE, 0);
	}
	else if (pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end()) {
		cam->moveCameraBy(-GRID_SIZE, 0);
	}
	else if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
		cam->moveCameraBy(0, GRID_SIZE);
	}
	else if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
		cam->moveCameraBy(0, -GRID_SIZE);
	}

	// zooming in and out of scene using V and B
	if (pressedKeys.find(SDL_SCANCODE_V) != pressedKeys.end()) {
		zoom += 0.01;
		zoom = min(zoom, 4.0);
		cam->setZoom(zoom);
	}
	else if (pressedKeys.find(SDL_SCANCODE_B) != pressedKeys.end()) {
		zoom -= 0.01;
		zoom = max(zoom, 0.1);
		cam->setZoom(zoom);
	}

	// delete selected sprite
	if (pressedKeys.find(SDL_SCANCODE_X) != pressedKeys.end()) {
		if (clickedSprite != NULL) {
			selectedLayer->removeChild(clickedSprite->id);
			clickedSprite = NULL;
		}
	}


	bar->update(pressedKeys);
	scene_lock.lock();
	activeScene->update(pressedKeys);
	scene_lock.unlock();
}


void DevTool::draw(AffineTransform& at) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::renderer);
	
	Game::draw(at);
	scene_lock.lock();
	activeScene->draw(at, cam, false);
	scene_lock.unlock();

	SDL_Rect rect = {0, 0, windowWidth, 100};
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rect);
	
	
	bar->draw(at);

	// draw grid
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	for(int i = 100; i <= windowHeight; i+=GRID_SIZE) {
		SDL_RenderDrawLine(renderer, 0, i, windowWidth, i);
	}
	for(int j = 0; j <= windowWidth; j+=GRID_SIZE) {
		SDL_RenderDrawLine(renderer, j, 100, j, windowHeight);
	}
	SDL_RenderPresent(Game::renderer);
}