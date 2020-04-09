#include "CollisionSystem.h"
#include <iostream>
#include <algorithm>

CollisionSystem::CollisionSystem() {

}

CollisionSystem::~CollisionSystem() {

}

//checks collisions between pairs of DOs where the corresponding types have been requested
//to be checked (via a single call to watchForCollisions) below.
void CollisionSystem::update() {
    // Sweep and Prune Algorithm 
    //   referenced from: (https://github.com/mattleibow/jitterphysics/wiki/Sweep-and-Prune)
    int num_collidables = static_collidables.size() + dynamic_collidables.size();
    if(num_collidables) {
        vector<DisplayObject*> combined_collidables(num_collidables);
        // Eventually skip this step to save memory
        merge(static_collidables.begin(), static_collidables.end(), 
            dynamic_collidables.begin(), dynamic_collidables.end(), 
            combined_collidables.begin(), DisplayObject::compareByPosition);

        vector<DisplayObject*> active_list{combined_collidables[0]};

        for(int i = 1; i < combined_collidables.size(); i++) {
            for(int j = 0; j < active_list.size(); j++) {
                DisplayObject* potential = combined_collidables[i];
                DisplayObject* active = active_list[j];
                if(potential->getHitbox().x > (active->getHitbox().x + active->getHitbox().w))
                    active_list.erase(active_list.begin() + j);
                // Potential Collision
                else if (collidable_pairs[potential->object_type][active->object_type] && collidesWith(potential, active)) {
                    potential->onCollision(active);
                    active->onCollision(potential);
                }
            }
            active_list.push_back(combined_collidables[i]);
        }
    }

    sort(dynamic_collidables.begin(), dynamic_collidables.end(), DisplayObject::compareByPosition);
}

//This system watches the game's display tree and is notified whenever a display object is placed onto
//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
void CollisionSystem::handleEvent(Event* e) {
    DisplayObjectEvent *doe = (DisplayObjectEvent*) e;
    DisplayObject *modified = doe->getDisplayObject();

    if(modified->collidable) {

        // Object added to display tree
        if(doe->getType() == DisplayObjectEvent::DISPLAY_OBJECT_ADDED_EVENT) {
            if(modified->isDynamic) {
                dynamic_collidables.push_back(modified);
                sort(dynamic_collidables.begin(), dynamic_collidables.end(), DisplayObject::compareByPosition);
            }
            else {
                static_collidables.push_back(modified);
                sort(static_collidables.begin(), static_collidables.end(), DisplayObject::compareByPosition);
            }
            cout << "Object " << modified->id << " added" << endl;
        }

        // Object removed from display tree   
        else if(doe->getType() == DisplayObjectEvent::DISPLAY_OBJECT_REMOVED_EVENT) {
            vector<DisplayObject*>::iterator it;
            if(modified->isDynamic) {
                for(it = dynamic_collidables.begin(); it != dynamic_collidables.end(); ++it) {
                    if(*it == modified) {
                        dynamic_collidables.erase(it);
                        break;
                    }
                }
            }
            else {
                for(it = static_collidables.begin(); it != static_collidables.end(); ++it) {
                    if(*it == modified) {
                        static_collidables.erase(it);
                        break;
                    }
                }
            }
        }
    }
}

//This function asks the collision system to start checking for collisions between all pairs
//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
//against all platform objects that are in the current scene.
void CollisionSystem::watchForCollisions(types::Type type1, types::Type type2) {
    collidable_pairs[type1][type2] = true;
    collidable_pairs[type2][type1] = true;
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
//Resolved using binary search to place objects as close as they can to one another
void CollisionSystem::resolveCollision(DisplayObject* d, DisplayObject* other, int xDelta1, int yDelta1, int xDelta2, int yDelta2) {
    int directionMagnitude1 = sqrt(xDelta1*xDelta1 + yDelta1*yDelta1);
    int directionMagnitude2 = sqrt(xDelta2*xDelta2 + yDelta2*yDelta2);
    float normX1 = 0, normY1 = 0, normX2 = 0, normY2 = 0;

    if(directionMagnitude1) {
        normX1 = (float)xDelta1 / directionMagnitude1;
        normY1 = (float)yDelta1 / directionMagnitude1;
    }
    if(directionMagnitude2) {
        normX2 = (float)xDelta2 / directionMagnitude2, 
        normY2 = (float)yDelta2 / directionMagnitude2;
    }

    while (directionMagnitude1 >= 1 ||  directionMagnitude2 >= 1) {
        if(collidesWith(d, other)) {
            d->position = {d->position.x - (int)(directionMagnitude1 * normX1), d->position.y - (int)(directionMagnitude1 * normY1)};
            other->position = {other->position.x - (int)(directionMagnitude2 * normX2), other->position.y - (int)(directionMagnitude2 * normY2)};
        }
        else {
            d->position = {d->position.x + (int)(directionMagnitude1 * normX1), d->position.y + (int)(directionMagnitude1 * normY1)};
            other->position = {other->position.x + (int)(directionMagnitude2 * normX2), other->position.y + (int)(directionMagnitude2 * normY2)};
        }
        directionMagnitude1 /= 4;
        directionMagnitude2 /= 4;
    }

    // Collision caused by rotation of one object into another
    if(!xDelta1 && !xDelta2 && !yDelta1 && !yDelta2) {
        if(d->rotation - d->oldRotation)
            d->rotation = d->oldRotation;
        if(other->rotation - other->oldRotation)
            other->rotation = other->oldRotation;
        if(d->scaleX - d->oldScaleX)
            d->scaleX = d->oldScaleX;
        if(other->scaleX - other->oldScaleX)
            other->scaleX = other->oldScaleX;
        if(d->scaleY - d->oldScaleY)
            d->scaleY = d->oldScaleY;
        if(other->scaleY - other->oldScaleY)
            other->scaleY = other->oldScaleY;
    }
}