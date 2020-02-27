#include "Scene.h"

#include "../plugins/rapidjson/document.h"
#include "../plugins/rapidjson/writer.h"
#include "../plugins/rapidjson/stringbuffer.h"
#include "../plugins/rapidjson/filereadstream.h"
#include <iostream>

#include <queue>
#include <Windows.h>

using namespace rapidjson;
using namespace std;

Scene::Scene() {
	root = new DisplayObjectContainer();

	parent_ids.push_back("Root");
	parent_ids.push_back("Background");
	parent_ids.push_back("Midground");
	parent_ids.push_back("Foreground");

}

DisplayObject* createDisplayObject(const Value& displayObjectInfo) {
	string node_id = displayObjectInfo["node_id"].GetString();
    string type_id = displayObjectInfo["type_id"].GetString();
    int loc_x = displayObjectInfo["locationX"].GetInt();
    int loc_y = displayObjectInfo["locationY"].GetInt();
    float scale_x = displayObjectInfo["scaleX"].GetFloat();
    float scale_y = displayObjectInfo["scaleY"].GetFloat();
    float rotation = displayObjectInfo["rotation"].GetFloat();
    int alpha = displayObjectInfo["alpha"].GetInt();
    string path_to_texture = displayObjectInfo["sprite_file_path"].GetString();

	DisplayObject* the_obj = new DisplayObject(node_id, path_to_texture);
	the_obj->position.x = loc_x;
	the_obj->position.y = loc_y;
	the_obj->scaleX = scale_x;
	the_obj->scaleY = scale_y;
	the_obj->rotation = rotation;
	the_obj->alpha = alpha;
	
	return the_obj;

}

DisplayObjectContainer* createDisplayObjectContainer(const Value& displayObjectContainerInfo) {
	string node_id = displayObjectContainerInfo["node_id"].GetString();
    string type_id = displayObjectContainerInfo["type_id"].GetString();
    int loc_x = displayObjectContainerInfo["locationX"].GetInt();
    int loc_y = displayObjectContainerInfo["locationY"].GetInt();
	float scale_x = displayObjectContainerInfo["scaleX"].GetFloat();
	float scale_y = displayObjectContainerInfo["scaleY"].GetFloat();
    float rotation = displayObjectContainerInfo["rotation"].GetFloat();
    int alpha = displayObjectContainerInfo["alpha"].GetInt();
    string path_to_texture = displayObjectContainerInfo["sprite_file_path"].GetString();

	DisplayObjectContainer* the_obj = new DisplayObjectContainer(node_id, path_to_texture);
	the_obj->position.x = loc_x;
	the_obj->position.y = loc_y;
	the_obj->scaleX = scale_x;
	the_obj->scaleY = scale_y;
	the_obj->rotation = rotation;
	the_obj->alpha = alpha;
	
	return the_obj;

}

Sprite* createSprite(const Value& spriteInfo) {
	string node_id = spriteInfo["node_id"].GetString();
    string type_id = spriteInfo["type_id"].GetString();
    int loc_x = spriteInfo["locationX"].GetInt();
    int loc_y = spriteInfo["locationY"].GetInt();
	float scale_x = spriteInfo["scaleX"].GetFloat();
	float scale_y = spriteInfo["scaleY"].GetFloat();
    float rotation = spriteInfo["rotation"].GetFloat();
    int alpha = spriteInfo["alpha"].GetInt();
    string path_to_texture = spriteInfo["sprite_file_path"].GetString();
	
	Sprite* the_obj = new Sprite(node_id, path_to_texture);

	the_obj->position.x = loc_x;
	the_obj->position.y = loc_y;
	the_obj->scaleX = scale_x;
	the_obj->scaleY = scale_y;
	the_obj->rotation = rotation;
	the_obj->alpha = alpha;
	
	return the_obj;
}

AnimatedSprite* createAnimatedSprite(const Value& animatedSpriteInfo) {
	string node_id = animatedSpriteInfo["node_id"].GetString();
    string type_id = animatedSpriteInfo["type_id"].GetString();
    int loc_x = animatedSpriteInfo["locationX"].GetInt();
    int loc_y = animatedSpriteInfo["locationY"].GetInt();
	float scale_x = animatedSpriteInfo["scaleX"].GetFloat();
	float scale_y = animatedSpriteInfo["scaleY"].GetFloat();
    float rotation = animatedSpriteInfo["rotation"].GetFloat();
    int alpha = animatedSpriteInfo["alpha"].GetInt();
	
	
	AnimatedSprite* the_obj = new AnimatedSprite(node_id);

	the_obj->position.x = loc_x;
	the_obj->position.y = loc_y;
	the_obj->scaleX = scale_x;
	the_obj->scaleY = scale_y;
	the_obj->rotation = rotation;
	the_obj->alpha = alpha;
	
	return the_obj;
}


// Recursion happens here
void createObject(const Value& attribute, DisplayObjectContainer* node) {

    string type_id = attribute["type_id"].GetString();

	DisplayObject* newChild;
	if (type_id == "DisplayObject") {
		newChild = (createDisplayObject(attribute));
	}
	else if (type_id == "DisplayObjectContainer") {
		newChild = createDisplayObjectContainer(attribute);
	}
	else if (type_id == "Sprite") {
		newChild = createSprite(attribute);
	}
	else if (type_id == "AnimatedSprite") {
		newChild = createAnimatedSprite(attribute);
	}

	node->addChild(newChild);
    
    const rapidjson::Value& children = attribute["children"];
	// iterates throught the child nodes
    for (rapidjson::Value::ConstValueIterator itr = children.Begin(); itr != children.End(); ++itr) {
        const rapidjson::Value& child = *itr;
        assert(child.IsObject());
		createObject(child, static_cast<DisplayObjectContainer*>(newChild));
    }
    
}

void Scene::loadScene(string sceneFilePath) {
	//sceneFilePath = "example_Kenny.json";
	FILE* fp = fopen(sceneFilePath.c_str(), "r");
	char readBuffer[65536];
	FileReadStream json(fp, readBuffer, sizeof(readBuffer));
	Document d;
	d.ParseStream(json);
    // cout << "IS OBJECT" << d.IsObject();
	root = createDisplayObjectContainer(d);
    createObject(d, root);

	queue<DisplayObject*> objQueue;
	objQueue.push(root);

	background = static_cast<DisplayObjectContainer*>(root->getChild("Background"));
	midground = static_cast<DisplayObjectContainer*>(root->getChild("Midground"));
	foreground = static_cast<DisplayObjectContainer*>(root->getChild("Foreground"));

}

DisplayObject* Scene::getChild(string id) {
	return root->getChild(id);
}

void Scene::update(set<SDL_Scancode> pressedKeys) {
	//background->update(pressedKeys);
	//midground->update(pressedKeys);
	//foreground->update(pressedKeys);

	DisplayObjectContainer::update(pressedKeys);
	root->update(pressedKeys);
}

void Scene::draw(AffineTransform& at) {
	DisplayObjectContainer::draw(at);
	root->draw(at);
}

void Scene::draw(AffineTransform& at, Camera* cam) {
	DisplayObjectContainer::draw(at, cam);
	root->draw(at, cam);
}

void Scene::draw(AffineTransform& at, Camera* cam, bool paralax) {
	DisplayObjectContainer::draw(at, cam);
	if (paralax) {
		cam->scrollRate = foregroundScrollRate;
		foreground->draw(at, cam);

		cam->scrollRate = midgroundScrollRate;
		midground->draw(at, cam);

		cam->backgroundScrollRate;
		background->draw(at, cam);

		cam->scrollRate = 1.0;
	}
	else {
		root->draw(at, cam);
	}
	
}

