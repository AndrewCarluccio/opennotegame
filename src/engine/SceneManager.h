#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "DisplayObjectContainer.h"
#include <vector>

using namespace std;

class SceneManager{

public:
	SceneManager();

	//Adds a transition trigger to the manager
	//Params: name of the transition, x,y position to trigger the transition and a margin m, a durration d for the xfade, tree from_tree to transition out of, tree to_tree to transition to
	//Return: success (true) or failure (false)
	bool addTransitionPoint(string name, int x, int y, int m, int durr, DisplayObjectContainer* from_tree, DisplayObjectContainer* to_tree);
	
	//Returns list of all transition names
	vector<string> getTransitions();

	//Removes a transition trigger from the manager
	//Params: name of transition point to remove
	//Return: success (true) or failure (false)
	bool removeTransitionPoint(string name);

	//Calls a scene transition if the provided position is within margin of any loaded transition
	//Return: true if transition triggered, false otherwise
	bool processPosition(int x, int y);


private:
	vector<string> transition_names;
	vector<vector<int>> transition_metadata;
	vector<vector<DisplayObjectContainer*>> transition_pairs;
};

#endif