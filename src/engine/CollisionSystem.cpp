#include "CollisionSystem.h"
#include <iostream>

CollisionSystem::CollisionSystem() {

}

CollisionSystem::~CollisionSystem() {

}

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update() {


}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e) {

}

//This function asks the collision system to start checking for collisions between all pairs
//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
//against all platform objects that are in the current scene.
void CollisionSystem::watchForCollisions(string type1, string type2) {

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