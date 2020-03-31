#include "SceneManager.h"

using namespace std;

SceneManager::SceneManager(TweenJuggler* jug, EventDispatcher* disp) {
	juggler = jug;
	dispatch = disp;

	dispatch->addEventListener(listen, TweenEvent::TWEEN_START_EVENT);
	dispatch->addEventListener(listen, TweenEvent::TWEEN_END_EVENT);
}

//Adds a transition trigger to the manager
//Params: name of the transition, x,y position to trigger the transition and a margin m, a durration durr for the xfade, tree from_tree to transition out of, tree to_tree to transition to
bool SceneManager::addTransitionPoint(string name, int x, int y, int m, int durr, Scene* from_tree, Scene* to_tree) {

	for (string n : transition_names) {
		if (n == name) {
			return false;
		}
	}
	transition_names.push_back(name);

	vector<int> trigger_stats;
	trigger_stats.push_back(x);
	trigger_stats.push_back(y);
	trigger_stats.push_back(m);
	trigger_stats.push_back(durr);
	transition_metadata.push_back(trigger_stats);

	vector<Scene*> pair;
	pair.push_back(from_tree);
	pair.push_back(to_tree);
	transition_pairs.push_back(pair);

	return true;
}

//Returns list of all transition names
vector<string> SceneManager::getTransitions() {
	return transition_names;
}

//Removes a transition trigger from the manager
//Params: name of transition point to remove
//Return: success (true) or failure (false)
bool SceneManager::removeTransitionPoint(string name) {
	int index;
	for (index = 0; index < transition_names.size(); index++) {
		if (transition_names.at(index) == name){
			transition_names.erase(transition_names.begin()+index);
			transition_metadata.erase(transition_metadata.begin() + index);
			transition_pairs.erase(transition_pairs.begin() + index);
			return true;
		}
	}
	return false;
}

//Calls a scene transition if the provided position is within margin of any loaded transition
//Return: true if transition triggered, false otherwise
bool SceneManager::processPosition(int x, int y) {
	if (listen->started) {
		cout << "Began fade" << endl;
		if (listen->ended && !primed) {
			cout << "Ended first fade" << endl;
			//swap active scene pointer, reset listeners, start fade up, prime for fade up complete condition
			active_scene = transition_scene;
			active_scene->alpha = 0;
			listen->reset();
			transitionIn(d / 2, active_scene);
			primed = true;
			cout << "Swapped pointer" << endl;
		}
		else if(listen->ended && primed) {
			cout << "Ended final fade" << endl;
			//after we fade back up, reset listeners and primer
			listen->reset();
			primed = false;
		}
	}
	else {
		for (int i = 0; i < transition_names.size(); i++) {
			vector<int> meta = transition_metadata.at(i);
			if ((abs(meta.at(0) - x) <= meta.at(2)) && (abs(meta.at(1) - y) <= meta.at(2))) {
				if (active_scene == transition_pairs.at(i).at(0)) {
					transition_scene = transition_pairs.at(i).at(1);
					d = meta.at(3);
					transitionOut(d / 2, active_scene);
					cout << "Fired transition!" << endl;
					return true;
				}
			}
		}
	}

	
	return false;


}

void SceneManager::transitionOut(int d, Scene* from_tree) {
	//Set up tweens and listeners
	Tween* tree = new Tween(from_tree->foreground);
	SDL_Point pv;
	pv.x = from_tree->foreground->width / 2.0;
	pv.x = from_tree->foreground->height / 2.0;
	from_tree->foreground->pivot = pv;
	listen->myTween = tree;
	//listen_end->myTween = tree;
	

	//Add the fade down event to the tree
	//tree->animate(TweenableParams::ALPHA, 1, 0, d);
	tree->animate(TweenableParams::SCALE_X, 1, 0, d);
	tree->animate(TweenableParams::SCALE_Y, 1, 0, d);
	//tree->animate(TweenableParams::ROTATION, 0, 100, 2);
	juggler->add(tree);
	
}


void SceneManager::transitionIn(int d, Scene* to_tree) {
	//Set up tweens and listeners
	Tween* tree = new Tween(to_tree->foreground);
	listen->myTween = tree;
	SDL_Point pv;
	pv.x = to_tree->foreground->width / 2.0;
	pv.x = to_tree->foreground->height / 2.0;
	to_tree->foreground->pivot = pv;

	//Add the fade up event to the tree
	//tree->animate(TweenableParams::ALPHA, 0, 1, d);
	tree->animate(TweenableParams::SCALE_X, 0, 1, d);
	tree->animate(TweenableParams::SCALE_Y, 0, 1, d);
	juggler->add(tree);

}