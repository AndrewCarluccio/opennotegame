#include "Scene.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include <iostream>

using namespace rapidjson;

Scene::Scene() {
	root = new DisplayObjectContainer();
	foreground = new DisplayObjectContainer();
	midground = new DisplayObjectContainer();
	background = new DisplayObjectContainer();

	root->addChild(background);
	root->addChild(midground);
	root->addChild(foreground);

	parent_ids.push_back("Root");
	parent_ids.push_back("Background");
	parent_ids.push_back("Midground");
	parent_ids.push_back("Foreground");

}

void Scene::loadScene(string sceneFilePath) {
	/*
	PARSE THE JSON HERE
	
	For now, I made two lists of strings, you need to change them to whatever JSON wrapper you are going to use

	FOR NOW I AM ASSUMING PARENTS ALWAYS LISTED BEFORE CHILDREN!
	*/
	FILE* fp = fopen(sceneFilePath, "r");
	// const char* json = f.read();
	char readBuffer[65536];
	FileReadStream json(fp, readBuffer, sizeof(readBuffer));
	
	Document d;
	d.ParseStream(json);
   	assert(d.IsArray()); 

	for(int i = 0; i < d.Size(); i++){
		//TODO: Populate these fileds from the JSON package

		
		string node_id = d[i]["node_id"].GetString();
		string parent_id = d[i]["parent_id"].GetString();
		string type_id = d[i]["type_id"].GetString();
		int loc_x = d[i]["locationX"].GetInt();
		int loc_y = d[i]["locataionY"].GetInt();
		int scale_x = d[i]["scaleX"].GetInt();
		int scale_y = d[i]["scaleY"].GetInt();
		int rotation = d[i]["rotation"].GetInt();
		int alpha = d[i]["alpha"].GetInt();
		string path_to_texture = d[i]["sprite_file_path"].GetString();

		if ((std::find(parent_ids.begin(), parent_ids.end(), parent_id)) != parent_ids.end()) {
			if (type_id == "DisplayObject") {

				DisplayObject* the_obj = new DisplayObject(node_id, path_to_texture);

				the_obj->position.x = loc_x;
				the_obj->position.y = loc_y;
				the_obj->scaleX = scale_x;
				the_obj->scaleY = scale_y;
				the_obj->rotation = rotation;
				the_obj->alpha = alpha;


				if (parent_id == "Root") {
					//add to root
					root->addChild(the_obj);
				}
				else if (parent_id == "Background") {
					//add to bg
					background->addChild(the_obj);
				}
				else if (parent_id == "Midground") {
					//add to mg
					midground->addChild(the_obj);
				}
				else if (parent_id == "Foreground") {
					//add to fg
					foreground->addChild(the_obj);
				}
				else {
					//search display tree for parent
					DisplayObjectContainer* parent = root->getChild(parent_id);
					parent->addChild(the_obj);
				}
			}
			else if (type_id == "DisplayObjectContainer") {
				DisplayObjectContainer* the_obj = new DisplayObject(node_id, path_to_texture);

				the_obj->position.x = loc_x;
				the_obj->position.y = loc_y;
				the_obj->scaleX = scale_x;
				the_obj->scaleY = scale_y;
				the_obj->rotation = rotation;
				the_obj->alpha = alpha;


				if (parent_id == "Root") {
					//add to root
					root->addChild(the_obj);
				}
				else if (parent_id == "Background") {
					//add to bg
					background->addChild(the_obj);
				}
				else if (parent_id == "Midground") {
					//add to mg
					midground->addChild(the_obj);
				}
				else if (parent_id == "Foreground") {
					//add to fg
					foreground->addChild(the_obj);
				}
				else {
					//search display tree for parent
					DisplayObjectContainer* parent = root->getChild(parent_id);
					parent->addChild(the_obj);
				}
			}
			else if (type_id == "Sprite") {
				Sprite* the_obj = new DisplayObject(node_id, path_to_texture);

				the_obj->position.x = loc_x;
				the_obj->position.y = loc_y;
				the_obj->scaleX = scale_x;
				the_obj->scaleY = scale_y;
				the_obj->rotation = rotation;
				the_obj->alpha = alpha;


				if (parent_id == "Root") {
					//add to root
					root->addChild(the_obj);
				}
				else if (parent_id == "Background") {
					//add to bg
					background->addChild(the_obj);
				}
				else if (parent_id == "Midground") {
					//add to mg
					midground->addChild(the_obj);
				}
				else if (parent_id == "Foreground") {
					//add to fg
					foreground->addChild(the_obj);
				}
				else {
					//search display tree for parent
					DisplayObjectContainer* parent = root->getChild(parent_id);
					parent->addChild(the_obj);
				}
			}
			else if (type_id == "AnimatedSprite") {
				AnimatedSprite* the_obj = new DisplayObject(node_id, path_to_texture);

				the_obj->position.x = loc_x;
				the_obj->position.y = loc_y;
				the_obj->scaleX = scale_x;
				the_obj->scaleY = scale_y;
				the_obj->rotation = rotation;
				the_obj->alpha = alpha;


				if (parent_id == "Root") {
					//add to root
					root->addChild(the_obj);
				}
				else if (parent_id == "Background") {
					//add to bg
					background->addChild(the_obj);
				}
				else if (parent_id == "Midground") {
					//add to mg
					midground->addChild(the_obj);
				}
				else if (parent_id == "Foreground") {
					//add to fg
					foreground->addChild(the_obj);
				}
				else {
					//search display tree for parent
					DisplayObjectContainer* parent = root->getChild(parent_id);
					parent->addChild(the_obj);
				}
			}
		}
	}
}

void Scene::update(set<SDL_Scancode> pressedKeys) {
	//background->update(pressedKeys);
	//midground->update(pressedKeys);
	//foreground->update(pressedKeys);

	DisplayObjectContainer::update(pressedKeys);
}

void Scene::draw(AffineTransform& at) {
	DisplayObjectContainer::draw(at);
}

