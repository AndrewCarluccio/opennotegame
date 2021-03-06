#include "CollisionSystem.h"
#include <iostream>
#include <algorithm>
#define epsilon 0.25

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

        sort(dynamic_collidables.begin(), dynamic_collidables.end(), DisplayObject::compareByPosition);
        sort(static_collidables.begin(), static_collidables.end(), DisplayObject::compareByPosition);

        std::merge(static_collidables.begin(), static_collidables.end(), 
            dynamic_collidables.begin(), dynamic_collidables.end(), 
            combined_collidables.begin(), DisplayObject::compareByPosition);
        
        vector<DisplayObject*> active_list{combined_collidables[0]};

        for(int i = 1; i < combined_collidables.size(); i++) {
            for(int j = 0; j < active_list.size(); j++) {
                DisplayObject* potential = combined_collidables[i];
                DisplayObject* active = active_list[j];
                if(potential->getHitbox().y > (active->getHitbox().y + active->getHitbox().h))
                    active_list.erase(active_list.begin() + j--);
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
                        cout << "Object " << modified->id << " removed" << endl;
                        break;
                    }
                }
            }
            else {
                for(it = static_collidables.begin(); it != static_collidables.end(); ++it) {
                    if(*it == modified) {
                        static_collidables.erase(it);
                        cout << "Object " << modified->id << " removed" << endl;
                        break;
                    }
                }
            }
        }
    }
}

// This function takes the root of a new display tree and replaces all objects currently watched by the collision system
// with the objects in the new tree
void CollisionSystem::updateWithNewScene(DisplayObjectContainer *root) {
    // Empty the contents from the previous display tree
    static_collidables.clear();
    dynamic_collidables.clear();

    cout << "Collision System: Current scene's objects removed" << endl;

    // Iterate through display tree and populate static/dynamic lists
    updateWithNewSceneHelper(root);

    cout << "Collision System: New scene's objects added" << endl;

    // Sort lists
    sort(dynamic_collidables.begin(), dynamic_collidables.end(), DisplayObject::compareByPosition);
    sort(static_collidables.begin(), static_collidables.end(), DisplayObject::compareByPosition);
}

void CollisionSystem::updateWithNewSceneHelper(DisplayObjectContainer* node) {
    if(node == NULL)
        return;

    if (node->collidable) {
        if (node->isDynamic)
            dynamic_collidables.push_back(node);
        else
            static_collidables.push_back(node);
        cout << "Object " << node->id << " added" << endl;
    }

    for (DisplayObject *c : node->children)
        updateWithNewSceneHelper(static_cast<DisplayObjectContainer*>(c));
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

    return hitbox1.x < hitbox2.x + hitbox2.w && hitbox1.x + hitbox1.w > hitbox2.x &&
           hitbox1.y < hitbox2.y + hitbox2.h && hitbox1.y + hitbox1.h > hitbox2.y;
}

inline float myCeil(float x) {
    return (x < 0) ? floor(x) : ceil(x);
}

//Resolves the collision that occurred between d and other
//xDelta1 and yDelta1 are the amount d moved before causing the collision.
//xDelta2 and yDelta2 are the amount other moved before causing the collision.
//Resolved using binary search to place objects as close as they can to one another
void CollisionSystem::resolveCollision(DisplayObject* d, DisplayObject* other, float xDelta1, float yDelta1, float xDelta2, float yDelta2) {
    bool xCollision = xDirectionCollision(d, other, xDelta1, xDelta2);
    bool yCollision = yDirectionCollision(d, other, yDelta1, yDelta2);

    if(xCollision && !yCollision)
        yDelta1 = yDelta2 = 0;
    if(!xCollision && yCollision)
        xDelta1 = xDelta2 = 0;

    while (true) {
        if (collidesWith(d, other)) {
            if(xCollision) {
                d->position.x -= myCeil(xDelta1);
                other->position.x -= myCeil(xDelta2);
            }
            if (yCollision) {
                d->position.y -= myCeil(yDelta1);
                other->position.y -= myCeil(yDelta2);
            }
            if (abs(xDelta1) < epsilon && abs(xDelta2) < epsilon &&
                abs(yDelta1) < epsilon && abs(yDelta2) < epsilon)
                break;
        }
        else
        {
            if(xCollision) {
                d->position.x += myCeil(xDelta1);
                other->position.x += myCeil(xDelta2);
            }
            if(yCollision) {
                d->position.y += myCeil(yDelta1);
                other->position.y += myCeil(yDelta2);
            }
        }
        xDelta1 /= 2;
        xDelta2 /= 2;
        yDelta1 /= 2;
        yDelta2 /= 2;
    }

    // Collision caused by rotation of one object into another
    if (!xDelta1 && !xDelta2 && !yDelta1 && !yDelta2)  {
        if (d->rotation - d->oldRotation)
            d->rotation = d->oldRotation;
        if (other->rotation - other->oldRotation)
            other->rotation = other->oldRotation;
        if (d->scaleX - d->oldScaleX)
            d->scaleX = d->oldScaleX;
        if (other->scaleX - other->oldScaleX)
            other->scaleX = other->oldScaleX;
        if (d->scaleY - d->oldScaleY)
            d->scaleY = d->oldScaleY;
        if (other->scaleY - other->oldScaleY)
            other->scaleY = other->oldScaleY;
    }
}

bool CollisionSystem::xDirectionCollision(DisplayObject *d, DisplayObject *other, int xDelta1, int xDelta2) {
    bool xCollision = false;

    d->position.x -= xDelta1;
    other->position.x -= xDelta2;

    if(!collidesWith(d, other))
        xCollision = true;

    d->position.x += xDelta1;
    other->position.x += xDelta2;

    return xCollision;
}

bool CollisionSystem::yDirectionCollision(DisplayObject *d, DisplayObject *other, int yDelta1, int yDelta2) {
    bool yCollision = false;

    d->position.y -= yDelta1;
    other->position.y -= yDelta2;

    if (!collidesWith(d, other))
        yCollision = true;

    d->position.y += yDelta1;
    other->position.y += yDelta2;

    return yCollision;
}