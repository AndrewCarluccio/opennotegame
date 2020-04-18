#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "DisplayObjectEvent.h"
#include "EventListener.h"
#include "Event.h"
#include "Types.h"

using namespace std;

class CollisionSystem : public EventListener{

public:

	CollisionSystem();
	~CollisionSystem();

	//checks collisions between pairs of DOs where the corresponding types have been requested
	//to be checked (via a single call to watchForCollisions) below.
	void update();

	//This system watches the game's display tree and is notified whenever a display object is placed onto
	//or taken off of the tree. Thus, the collision system always knows what DOs are in the game at any moment automatically.
	void handleEvent(Event* e);

	// This function takes the root of a new display tree and replaces all objects currently watched by the collision system
	// with the objects in the new tree
	void updateWithNewScene(DisplayObjectContainer* root);

	//This function asks the collision system to start checking for collisions between all pairs
	//of DOs of a given type (e.g., player vs platform). The system will begin to check all player objects
	//against all platform objects that are in the current scene.
	void watchForCollisions(types::Type type1, types::Type type2);

	//returns true iff obj1 hitbox and obj2 hitbox overlap. Uses the following method from DO:
	//	SDL_Point* DisplayObject::getGlobalHitbox();
	bool collidesWith(DisplayObject* obj1, DisplayObject* obj2);

	//Resolves the collision that occurred between d and other
	//xDelta1 and yDelta1 are the amount d moved before causing the collision.
	//xDelta2 and yDelta2 are the amount other moved before causing the collision.
	void resolveCollision(DisplayObject* d, DisplayObject* other, float xDelta1, float yDelta1, float xDelta2, float yDelta2);
	
private:
	bool collidable_pairs[types::COUNT][types::COUNT];
	vector<DisplayObject*> static_collidables;
	vector<DisplayObject*> dynamic_collidables;

	bool xDirectionCollision(DisplayObject *d, DisplayObject *other, int xDelta1, int xDelta2);
	bool yDirectionCollision(DisplayObject *d, DisplayObject *other, int yDelta1, int yDelta2);
	void updateWithNewSceneHelper(DisplayObjectContainer* node);
};

#endif
