#include "TransitionPoint.h"

using namespace std;

TransitionPoint::TransitionPoint() : DisplayObjectContainer() {
    this->type = "TransitionPoint";
}

TransitionPoint::TransitionPoint(string id, string filepath) : DisplayObjectContainer(id, filepath){
    this->type = "TransitionPoint";
}

TransitionPoint::TransitionPoint(string id, int red, int green, int blue) : DisplayObjectContainer(id, red, green, blue) {
    this->type = "TransitionPoint";
}

void TransitionPoint::update(set<SDL_Scancode> pressedKeys) {
    DisplayObjectContainer::update(pressedKeys);
}

void TransitionPoint::draw(AffineTransform &at) {
    DisplayObjectContainer::draw(at);
}