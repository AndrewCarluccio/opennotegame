#include "DisplayObjectContainer.h"
#include "AffineTransform.h"
#include <vector>
#include <string>


using namespace std;


DisplayObjectContainer::DisplayObjectContainer() : DisplayObject() {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::DisplayObjectContainer(string id, string filepath) : DisplayObject(id, filepath) {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::DisplayObjectContainer(string id, int red, int green, int blue) : DisplayObject(id, red, green, blue) {
    this->type = "DisplayObjectContainer";
}

DisplayObjectContainer::~DisplayObjectContainer() {
    for (int i = 0; i < children.size(); i++ ) {
        delete children[i];
    }
}

void DisplayObjectContainer::addChild(DisplayObject* child) {
    children.push_back(child);
    child->parent = this; // make sure to include reverse reference also
    DisplayObjectContainer* root = (DisplayObjectContainer*)getRoot();
    root->dispatchEvent(new DisplayObjectEvent(DisplayObjectEvent::DISPLAY_OBJECT_ADDED_EVENT, root, child));
}

void DisplayObjectContainer::removeImmediateChild(DisplayObject* child) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i] == child) {
            DisplayObjectContainer* root = (DisplayObjectContainer*)getRoot();
            root->dispatchEvent(new DisplayObjectEvent(DisplayObjectEvent::DISPLAY_OBJECT_REMOVED_EVENT, root, child));
            delete child;
            children.erase(children.begin() + i);
        }
    }
}

void DisplayObjectContainer::removeImmediateChild(string id) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->id == id) {
            DisplayObjectContainer* root = (DisplayObjectContainer*)getRoot();
            root->dispatchEvent(new DisplayObjectEvent(DisplayObjectEvent::DISPLAY_OBJECT_REMOVED_EVENT, root, children[i]));
            // delete the child
            delete children[i];
            children.erase(children.begin() + i);
            break;
        }
    }
}

void DisplayObjectContainer::removeChild(string id) {
    vector<DisplayObject *> objects (children);
    while (!objects.empty()) {
        DisplayObject *object = objects.back();
        objects.pop_back();
        if (object->id == id) {
            object->parent->removeImmediateChild(id);
        } else {
            DisplayObjectContainer *obj = dynamic_cast<DisplayObjectContainer*>(object);
            if(obj != NULL && !obj->children.empty()) {
                objects.insert(objects.end(), obj->children.begin(), obj->children.end());
            }
        }
    }

}

void DisplayObjectContainer::moveChildToFront(string id) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->id == id) {
            DisplayObject* child = children[i];
            children.erase(children.begin() + i);
            children.push_back(child);
            break;
        }
    }
}

void DisplayObjectContainer::removeChild(int index) {
    if (index < children.size()) {
        delete children[index];
        children.erase(children.begin() + index);
    }
}

void DisplayObjectContainer::removeThis() {
    if (this->parent != NULL) {
        ((DisplayObjectContainer*)this->parent)->removeImmediateChild(this);
    }
}

int DisplayObjectContainer::numChildren() {
    return this->children.size();
}

DisplayObject* DisplayObjectContainer::getChild(int index) {
    if (index < 0 || index >= numChildren()) {
        return NULL;
    }
    else return children[index];
}

DisplayObject* DisplayObjectContainer::getChild(string id) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->id.compare(id) == 0) {
            return children[i];
        }
        DisplayObjectContainer* child = static_cast<DisplayObjectContainer*>(children[i]);
        DisplayObject* foundChild = child->getChild(id);
        if (foundChild != NULL) {
            return foundChild;
        }
    }
    return NULL;
}

void DisplayObjectContainer::update(set<SDL_Scancode> pressedKeys) {
    DisplayObject::update(pressedKeys);
    for (int i = 0; i < children.size(); i++) {
        children[i]->update(pressedKeys);
    }
}

void DisplayObjectContainer::draw(AffineTransform &at) {
    DisplayObject::draw(at);
    applyTransformations(at);
    // undo the parent's pivot
    at.translate(pivot.x, pivot.y);
    for (int i = 0; i < children.size(); i++) {
        children[i]->draw(at);
    }
    // redo the parent's pivot
    at.translate(-pivot.x, -pivot.y);
    reverseTransformations(at);
}

