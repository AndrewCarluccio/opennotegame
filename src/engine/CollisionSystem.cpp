#include "CollisionSystem.h"
#include <iostream>

CollisionSystem::CollisionSystem() {

}

CollisionSystem::~CollisionSystem() {

}

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update() {
    for(pair<string, string> p : collision_pairs) {
        for(vector<DisplayObject*>::iterator it = collidables.begin(); it != collidables.end(); ++it) {
            string searching_for = "";
            if((*it)->id == p.first)
                searching_for = p.second;
            else if((*it)->id == p.second)
                searching_for = p.first;
            else
                continue;
            for(vector<DisplayObject*>::iterator it2 = it+1; it2 != collidables.end(); ++it2) {
                if((*it2)->id == searching_for)
                    if(collidesWith(*it, *it2)) {
                        int xDelta1 = (*it)->position.x - (*it)->old_position.x;
                        int yDelta1 = (*it)->position.y - (*it)->old_position.y;
                        int xDelta2 = (*it2)->position.x - (*it2)->old_position.x;
                        int yDelta2 = (*it2)->position.y - (*it2)->old_position.y;
                        resolveCollision(*it, *it2, xDelta1, yDelta1, xDelta2, yDelta2);
                    }
            }
        }
    }
}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e) {
    DisplayObjectEvent *doe = (DisplayObjectEvent*) e;
    DisplayObject *modified = doe->getDisplayObject();

    if(doe->getType() == DisplayObjectEvent::DISPLAY_OBJECT_ADDED_EVENT) {
        collidables.push_back(modified);
        cout << "Object " << modified->id << " added" << endl;
    }   
    else if(doe->getType() == DisplayObjectEvent::DISPLAY_OBJECT_REMOVED_EVENT) {
        for(vector<DisplayObject*>::iterator it = collidables.begin(); it != collidables.end(); ++it) {
            if(*it == modified) {
                collidables.erase(it);
                cout << "Object " << modified->id << " removed" << endl;
                break;
            }
        }
    }
}

//This function asks the collision system to start checking for collisions between all pairs
//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
//against all platform objects that are in the current scene.
void CollisionSystem::watchForCollisions(string type1, string type2) {
    // Currently using object ids instead of object types, this should be changed later because
    // it would be a pain to specify every object name you want to check collisions for
    collision_pairs.push_back({type1, type2});
}

//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
//	SDL_Point* DisplayObject::getGlobalHitbox();
bool CollisionSystem::collidesWith(DisplayObject* obj1, DisplayObject* obj2) {
    SDL_Rect hitbox1 = obj1->getHitbox();
    SDL_Rect hitbox2 = obj2->getHitbox();

    if (hitbox1.x < hitbox2.x + hitbox2.w && hitbox1.x + hitbox1.w > hitbox2.x &&
        hitbox1.y < hitbox2.y + hitbox2.h && hitbox1.y + hitbox1.h > hitbox2.y) {
        cout << "Collision Detected between " << obj1->id << " and " << obj2->id << endl;
        return true;
    }

    return false;
}

//Resolves the collision that occurred between d and other
//xDelta1 and yDelta1 are the amount d moved before causing the collision.
//xDelta2 and yDelta2 are the amount other moved before causing the collision.
void CollisionSystem::resolveCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2) {
    d->position = {d->position.x - xDelta1, d->position.y - yDelta1};
    other->position = {other->position.x - xDelta2, other->position.y - yDelta2};
}