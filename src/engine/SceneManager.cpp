// #include "SceneManager.h"

// using namespace std;

// SceneManager::SceneManager() {

// }

// //Adds a transition trigger to the manager
// //Params: name of the transition, x,y position to trigger the transition and a margin m, a durration durr for the xfade, tree from_tree to transition out of, tree to_tree to transition to
// bool SceneManager::addTransitionPoint(string name, int x, int y, int m, int durr, DisplayObjectContainer* from_tree, DisplayObjectContainer* to_tree) {

// 	for (string n : transition_names) {
// 		if (n == name) {
// 			return false;
// 		}
// 	}
// 	transition_names.push_back(name);

// 	vector<int> trigger_stats;
// 	trigger_stats.push_back(x);
// 	trigger_stats.push_back(y);
// 	trigger_stats.push_back(m);
// 	trigger_stats.push_back(durr);
// 	transition_metadata.push_back(trigger_stats);

// 	vector<DisplayObjectContainer*> pair;
// 	pair.push_back(from_tree);
// 	pair.push_back(to_tree);
// 	transition_pairs.push_back(pair);

// 	return true;
// }

// //Returns list of all transition names
// vector<string> SceneManager::getTransitions() {
// 	return transition_names;
// }

// //Removes a transition trigger from the manager
// //Params: name of transition point to remove
// //Return: success (true) or failure (false)
// bool SceneManager::removeTransitionPoint(string name) {
// 	int index;
// 	for (index = 0; index < transition_names.size(); index++) {
// 		if (transition_names.at(index) == name){
// 			transition_names.erase(transition_names.begin()+index);
// 			transition_metadata.erase(transition_metadata.begin() + index);
// 			transition_pairs.erase(transition_pairs.begin() + index);
// 			return true;
// 		}
// 	}
// 	return false;
// }

// //Calls a scene transition if the provided position is within margin of any loaded transition
// //Return: true if transition triggered, false otherwise
// bool SceneManager::processPosition(int x, int y) {
// 	for (int i = 0; i < transition_names.size(); i++) {
// 		vector<int> meta = transition_metadata.at(i);
// 		if (abs(meta.at(0) - x) <= meta.at(2) && abs(meta.at(1) - y) <= meta.at(2)) {
// 			transitionScenes(meta.at(3), transition_pairs.at(i).at(0), transition_pairs.at(i).at(1));

// 			//TODO---> throw room transition event

// 			return true;
// 		}
// 	}
// 	return false;
// }

// void transitionScenes(int d, DisplayObjectContainer* from_tree, DisplayObjectContainer* to_tree) {


// }