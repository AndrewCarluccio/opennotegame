#include "Scene.h"

#include "../plugins/rapidjson/document.h"
#include "../plugins/rapidjson/writer.h"
#include "../plugins/rapidjson/stringbuffer.h"
#include "../plugins/rapidjson/filereadstream.h"
#include <iostream>

#include <queue>
//#include <Windows.h>

using namespace rapidjson;

Scene::Scene() {
	root = new DisplayObjectContainer();
}

void setDisplayObjectProperties(const Value &displayObjectInfo, DisplayObject *the_obj) {
	string node_id = displayObjectInfo["node_id"].GetString();
	string type_id = displayObjectInfo["type_id"].GetString();
	string spriteType;
	if (displayObjectInfo.HasMember("sprite_type")) {
		spriteType = displayObjectInfo["sprite_type"].GetString();
	} else {
		spriteType = "default";
	}
	int loc_x = displayObjectInfo["locationX"].GetInt();
	int loc_y = displayObjectInfo["locationY"].GetInt();
	float scale_x = displayObjectInfo["scaleX"].GetFloat();
	float scale_y = displayObjectInfo["scaleY"].GetFloat();
	float rotation = displayObjectInfo["rotation"].GetFloat();
	int alpha = displayObjectInfo["alpha"].GetInt();
	string path_to_texture = displayObjectInfo["sprite_file_path"].GetString();

	bool collidable;
	if (displayObjectInfo.HasMember("collidable")) {
		collidable = displayObjectInfo["collidable"].GetBool();
	} else {
		collidable = true;
	}

	bool isDynamic;
	if (displayObjectInfo.HasMember("isDynamic")) {
		isDynamic = displayObjectInfo["isDynamic"].GetBool();
	} else {
		isDynamic = false;
	}
	float hitboxScaleX;
	if (displayObjectInfo.HasMember("hitboxScaleX")) {
		hitboxScaleX = displayObjectInfo["hitboxScaleX"].GetFloat();
	} else {
		hitboxScaleX = 1.0;
	}
	float hitboxScaleY;
	if (displayObjectInfo.HasMember("hitboxScaleY")) {
		hitboxScaleY = displayObjectInfo["hitboxScaleY"].GetFloat();
	} else {
		hitboxScaleY = 1.0;
	}

	types::Type object_type;
	if (displayObjectInfo.HasMember("object_type")) {
		object_type = static_cast<types::Type>(displayObjectInfo["object_type"].GetInt());
		the_obj->object_type = object_type;
	} else {
		if (path_to_texture.find("platform") != string::npos) {
			object_type = types::Type::Platform;
			the_obj->object_type = object_type;
		}	
	}

	the_obj->sprite_type = spriteType;
	the_obj->position.x = loc_x;
	the_obj->position.y = loc_y;
	the_obj->old_position.x = loc_x;
	the_obj->old_position.y = loc_y;
	the_obj->scaleX = scale_x;
	the_obj->scaleY = scale_y;
	the_obj->rotation = rotation;
	the_obj->alpha = alpha;
	the_obj->collidable = collidable;
	the_obj->isDynamic = isDynamic;
	the_obj->hitboxScaleX = hitboxScaleX;
	the_obj->hitboxScaleY = hitboxScaleY;


}

DisplayObject* createDisplayObject(const Value& displayObjectInfo) {
	string node_id = displayObjectInfo["node_id"].GetString();
	string path_to_texture = displayObjectInfo["sprite_file_path"].GetString();

	DisplayObject* the_obj = new DisplayObject(node_id, path_to_texture);

	setDisplayObjectProperties(displayObjectInfo, the_obj);

	return the_obj;

}

DisplayObjectContainer* createDisplayObjectContainer(const Value& displayObjectInfo) {
	string node_id = displayObjectInfo["node_id"].GetString();
	string path_to_texture = displayObjectInfo["sprite_file_path"].GetString();

	DisplayObjectContainer* the_obj = new DisplayObjectContainer(node_id, path_to_texture);

	setDisplayObjectProperties(displayObjectInfo, the_obj);

	return the_obj;

}

DisplayObjectContainer* createLayer(const Value& layerInfo) {
	return createDisplayObjectContainer(layerInfo);

}


Sprite* createSprite(const Value& spriteInfo) {
	string node_id = spriteInfo["node_id"].GetString();
	string path_to_texture = spriteInfo["sprite_file_path"].GetString();

	Sprite* the_obj = new Sprite(node_id, path_to_texture);

	setDisplayObjectProperties(spriteInfo, the_obj);

	return the_obj;
}

AnimatedSprite* createAnimatedSprite(const Value& animatedSpriteInfo) {
	string node_id = animatedSpriteInfo["node_id"].GetString();
	string path_to_texture = animatedSpriteInfo["sprite_file_path"].GetString();

	AnimatedSprite* the_obj = new AnimatedSprite(node_id, path_to_texture);

	setDisplayObjectProperties(animatedSpriteInfo, the_obj);

	return the_obj;
}

Player* createPlayer(const Value& playerInfo) {
	string node_id = playerInfo["node_id"].GetString();
	string path_to_texture = playerInfo["sprite_file_path"].GetString();

	Player* the_obj = new Player(node_id, path_to_texture);

	setDisplayObjectProperties(playerInfo, the_obj);

	return the_obj;
}

EnvironmentalObject* createEnvironmentalObject(const Value& EnvironmentalObjectInfo) {
	string node_id = EnvironmentalObjectInfo["node_id"].GetString();
	string path_to_texture = EnvironmentalObjectInfo["sprite_file_path"].GetString();

	EnvironmentalObject* the_obj = new EnvironmentalObject(node_id, path_to_texture);

	setDisplayObjectProperties(EnvironmentalObjectInfo, the_obj);

	return the_obj;
}

Enemy* createEnemy(const Value& EnemyInfo) {
	string node_id = EnemyInfo["node_id"].GetString();
	string path_to_texture = EnemyInfo["sprite_file_path"].GetString();

	Enemy* the_obj = new Enemy(node_id, path_to_texture);

	setDisplayObjectProperties(EnemyInfo, the_obj);

	return the_obj;
}

Character* createCharacter(const Value& CharacterInfo) {
	string node_id = CharacterInfo["node_id"].GetString();
	string path_to_texture = CharacterInfo["sprite_file_path"].GetString();

	string first_dialogue = CharacterInfo["first_dialogue"].GetString();
	string mid_dialogue = CharacterInfo["mid_dialogue"].GetString();
	string item_dialogue = CharacterInfo["item_dialogue"].GetString();
	string post_dialogue = CharacterInfo["post_dialogue"].GetString();
	string item_needed = CharacterInfo["item_needed"].GetString();
	string item_to_give = CharacterInfo["item_to_give"].GetString();
	string item_path = CharacterInfo["item_path"].GetString();
	

	Character* the_obj = new Character(node_id, path_to_texture);

	setDisplayObjectProperties(CharacterInfo, the_obj);

	
	the_obj->firstDialogue = first_dialogue;
	the_obj->midDialogue = mid_dialogue;
	the_obj->itemDialogue = item_dialogue;
	the_obj->postDialogue = post_dialogue;
	the_obj->itemNeeded = item_needed;
	the_obj->itemToGive = item_to_give;
	the_obj->itemPath = item_path;

	return the_obj;
}

// Recursion happens here
void createObject(const Value& attribute, DisplayObjectContainer* node) {

	string type_id = attribute["type_id"].GetString();
	string node_id = attribute["node_id"].GetString();

	DisplayObject* newChild;
	if (node_id == "player") {
		newChild = createPlayer(attribute);

	}
	else if (type_id == "DisplayObject") {
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
	else if (type_id == "Layer") {
		newChild = createLayer(attribute);
	}
	else if (type_id == "EnvironmentalObject") {
		newChild = createEnvironmentalObject(attribute);
	}
	else if (type_id == "Enemy") {
		newChild = createEnemy(attribute);
	}
	else if (type_id == "Character") {
		newChild = createCharacter(attribute);
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
	if (fp != NULL) {
	FileReadStream json(fp, readBuffer, sizeof(readBuffer));
	Document d;
	d.ParseStream(json);
	// cout << "IS OBJECT" << d.IsObject();
	root = createDisplayObjectContainer(d);
	root->addEventListener(&Game::instance->collisionSystem, DisplayObjectEvent::DISPLAY_OBJECT_ADDED_EVENT);
	root->addEventListener(&Game::instance->collisionSystem, DisplayObjectEvent::DISPLAY_OBJECT_REMOVED_EVENT);
	createObject(d, root);

	queue<DisplayObject*> objQueue;
	objQueue.push(root);

	background = static_cast<DisplayObjectContainer*>(root->getChild("Background"));
	midground = static_cast<DisplayObjectContainer*>(root->getChild("Midground"));
	foreground = static_cast<DisplayObjectContainer*>(root->getChild("Foreground"));
	} else {
		cout << "Could not find scene at " << sceneFilePath << endl;
	}
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

void Scene::draw(AffineTransform& at, Camera* cam, bool paralax) {
	DisplayObjectContainer::draw(at);

	float foregroundScrollRate = foreground->scrollRate;
	float midgroundScrollRate = midground->scrollRate;
	float backgroundScrollRate = background->scrollRate;

	 if (paralax) {

		cam->scrollRate = backgroundScrollRate;
		cam->applyCamera(at);
		background->draw(at);
		cam->undoCamera(at);

	 	cam->scrollRate = midgroundScrollRate;
		cam->applyCamera(at);
	 	midground->draw(at);
		cam->undoCamera(at);

		cam->scrollRate = foregroundScrollRate;
		cam->applyCamera(at);
		foreground->draw(at);
		cam->undoCamera(at);

	 	cam->scrollRate = 1.0;
	 }
	 else {

		cam->applyCamera(at);
		root->draw(at);
		cam->undoCamera(at);
	 }
}

