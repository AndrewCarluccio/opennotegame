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


DisplayObjectContainer* createLayer(const Value& layerInfo) {
	string node_id = layerInfo["node_id"].GetString();
	string type_id = layerInfo["type_id"].GetString();
	int loc_x = layerInfo["locationX"].GetInt();
	int loc_y = layerInfo["locationY"].GetInt();
	float scale_x = layerInfo["scaleX"].GetFloat();
	float scale_y = layerInfo["scaleY"].GetFloat();
	float rotation = layerInfo["rotation"].GetFloat();
	int alpha = layerInfo["alpha"].GetInt();
	string path_to_texture = layerInfo["sprite_file_path"].GetString();
	float scroll_rate = layerInfo["scroll_rate"].GetFloat();
	bool collidable = layerInfo["collidable"].GetBool();
	bool isDynamic = layerInfo["isDynamic"].GetBool();
	float hitboxScaleX = layerInfo["hitboxScaleX"].GetFloat();
	float hitboxScaleY = layerInfo["hitboxScaleY"].GetFloat();
	types::Type object_type = static_cast<types::Type>(layerInfo["object_type"].GetInt());

	/*
	if (node_id == "Background") {
		backgroundScrollRate = scroll_rate;
	}
	else if (node_id == "Midground") {
		midgroundScrollRate = scroll_rate;
	}
	else if (node_id == "Foreground") {
		foregroundScrollRate = scroll_rate;
	}
	*/

	DisplayObjectContainer* the_obj = new DisplayObjectContainer(node_id, path_to_texture);

	the_obj->position.x = loc_x;
	the_obj->position.y = loc_y;
	the_obj->old_position.x = loc_x;
	the_obj->old_position.y = loc_y;
	the_obj->scaleX = scale_x;
	the_obj->scaleY = scale_y;
	the_obj->rotation = rotation;
	the_obj->alpha = alpha;
	the_obj->scrollRate = scroll_rate;
	the_obj->collidable = collidable;
	the_obj->isDynamic = isDynamic;
	the_obj->hitboxScaleX = hitboxScaleX;
	the_obj->hitboxScaleY = hitboxScaleY;
	the_obj->object_type = object_type;

	return the_obj;

}

DisplayObject* createDisplayObject(const Value& displayObjectInfo) {
	string node_id = displayObjectInfo["node_id"].GetString();
	string type_id = displayObjectInfo["type_id"].GetString();
	string spriteType = displayObjectInfo["sprite_type"].GetString();
	int loc_x = displayObjectInfo["locationX"].GetInt();
	int loc_y = displayObjectInfo["locationY"].GetInt();
	float scale_x = displayObjectInfo["scaleX"].GetFloat();
	float scale_y = displayObjectInfo["scaleY"].GetFloat();
	float rotation = displayObjectInfo["rotation"].GetFloat();
	int alpha = displayObjectInfo["alpha"].GetInt();
	string path_to_texture = displayObjectInfo["sprite_file_path"].GetString();
	bool collidable = displayObjectInfo["collidable"].GetBool();
	bool isDynamic = displayObjectInfo["isDynamic"].GetBool();
	float hitboxScaleX = displayObjectInfo["hitboxScaleX"].GetFloat();
	float hitboxScaleY = displayObjectInfo["hitboxScaleY"].GetFloat();
	types::Type object_type = static_cast<types::Type>(displayObjectInfo["object_type"].GetInt());

	DisplayObject* the_obj = new DisplayObject(node_id, path_to_texture);

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
	the_obj->object_type = object_type;

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
	bool collidable = displayObjectContainerInfo["collidable"].GetBool();
	bool isDynamic = displayObjectContainerInfo["isDynamic"].GetBool();
	float hitboxScaleX = displayObjectContainerInfo["hitboxScaleX"].GetFloat();
	float hitboxScaleY = displayObjectContainerInfo["hitboxScaleY"].GetFloat();
	types::Type object_type = static_cast<types::Type>(displayObjectContainerInfo["object_type"].GetInt());

	DisplayObjectContainer* the_obj = new DisplayObjectContainer(node_id, path_to_texture);

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
	the_obj->object_type = object_type;

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
	bool collidable = spriteInfo["collidable"].GetBool();
	bool isDynamic = spriteInfo["isDynamic"].GetBool();
	float hitboxScaleX = spriteInfo["hitboxScaleX"].GetFloat();
	float hitboxScaleY = spriteInfo["hitboxScaleY"].GetFloat();
	types::Type object_type = static_cast<types::Type>(spriteInfo["object_type"].GetInt());

	Sprite* the_obj = new Sprite(node_id, path_to_texture);

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
	the_obj->object_type = object_type;

	return the_obj;
}

AnimatedSprite* createAnimatedSprite(const Value& animatedSpriteInfo) {
	string node_id = animatedSpriteInfo["node_id"].GetString();
	string type_id = animatedSpriteInfo["type_id"].GetString();
	string spriteType = animatedSpriteInfo["sprite_type"].GetString();
	int loc_x = animatedSpriteInfo["locationX"].GetInt();
	int loc_y = animatedSpriteInfo["locationY"].GetInt();
	float scale_x = animatedSpriteInfo["scaleX"].GetFloat();
	float scale_y = animatedSpriteInfo["scaleY"].GetFloat();
	float rotation = animatedSpriteInfo["rotation"].GetFloat();
	int alpha = animatedSpriteInfo["alpha"].GetInt();
	string path_to_texture = animatedSpriteInfo["sprite_file_path"].GetString();
	bool collidable = animatedSpriteInfo["collidable"].GetBool();
	bool isDynamic = animatedSpriteInfo["isDynamic"].GetBool();
	float hitboxScaleX = animatedSpriteInfo["hitboxScaleX"].GetFloat();
	float hitboxScaleY = animatedSpriteInfo["hitboxScaleY"].GetFloat();
	types::Type object_type = static_cast<types::Type>(animatedSpriteInfo["object_type"].GetInt());

	AnimatedSprite* the_obj = new AnimatedSprite(node_id, path_to_texture);

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
	the_obj->object_type = object_type;

	return the_obj;
}

Player* createPlayer(const Value& playerInfo) {
	string node_id = playerInfo["node_id"].GetString();
	string type_id = playerInfo["type_id"].GetString();
	int loc_x = playerInfo["locationX"].GetInt();
	int loc_y = playerInfo["locationY"].GetInt();
	float scale_x = playerInfo["scaleX"].GetFloat();
	float scale_y = playerInfo["scaleY"].GetFloat();
	float rotation = playerInfo["rotation"].GetFloat();
	int alpha = playerInfo["alpha"].GetInt();
	string path_to_texture = playerInfo["sprite_file_path"].GetString();
	bool collidable = playerInfo["collidable"].GetBool();
	bool isDynamic = playerInfo["isDynamic"].GetBool();
	float hitboxScaleX = playerInfo["hitboxScaleX"].GetFloat();
	float hitboxScaleY = playerInfo["hitboxScaleY"].GetFloat();
	types::Type object_type = static_cast<types::Type>(playerInfo["object_type"].GetInt());

	Player* the_obj = new Player(node_id, path_to_texture);

	the_obj->position.x = loc_x;
	the_obj->position.y = loc_y;
	the_obj->scaleX = scale_x;
	the_obj->scaleY = scale_y;
	the_obj->rotation = rotation;
	the_obj->alpha = alpha;
	the_obj->collidable = collidable;
	the_obj->isDynamic = isDynamic;
	the_obj->hitboxScaleX = hitboxScaleX;
	the_obj->hitboxScaleY = hitboxScaleY;
	the_obj->object_type = object_type;

	return the_obj;
}

EnvironmentalObject* createEnvironmentalObject(const Value& EnvironmentalObjectInfo) {
	string node_id = EnvironmentalObjectInfo["node_id"].GetString();
	string type_id = EnvironmentalObjectInfo["type_id"].GetString();
	string spriteType = EnvironmentalObjectInfo["sprite_type"].GetString();
	int loc_x = EnvironmentalObjectInfo["locationX"].GetInt();
	int loc_y = EnvironmentalObjectInfo["locationY"].GetInt();
	float scale_x = EnvironmentalObjectInfo["scaleX"].GetFloat();
	float scale_y = EnvironmentalObjectInfo["scaleY"].GetFloat();
	float rotation = EnvironmentalObjectInfo["rotation"].GetFloat();
	int alpha = EnvironmentalObjectInfo["alpha"].GetInt();
	string path_to_texture = EnvironmentalObjectInfo["sprite_file_path"].GetString();
	bool collidable = EnvironmentalObjectInfo["collidable"].GetBool();
	bool isDynamic = EnvironmentalObjectInfo["isDynamic"].GetBool();
	float hitboxScaleX = EnvironmentalObjectInfo["hitboxScaleX"].GetFloat();
	float hitboxScaleY = EnvironmentalObjectInfo["hitboxScaleY"].GetFloat();
	types::Type object_type = static_cast<types::Type>(EnvironmentalObjectInfo["object_type"].GetInt());

	EnvironmentalObject* the_obj = new EnvironmentalObject(node_id, path_to_texture);

	the_obj->sprite_type = spriteType;
	the_obj->position.x = loc_x;
	the_obj->position.y = loc_y;
	the_obj->scaleX = scale_x;
	the_obj->scaleY = scale_y;
	the_obj->rotation = rotation;
	the_obj->alpha = alpha;
	the_obj->collidable = collidable;
	the_obj->isDynamic = isDynamic;
	the_obj->hitboxScaleX = hitboxScaleX;
	the_obj->hitboxScaleY = hitboxScaleY;
	the_obj->object_type = object_type;

	return the_obj;
}

Enemy* createEnemy(const Value& EnemyInfo) {
	string node_id = EnemyInfo["node_id"].GetString();
	string type_id = EnemyInfo["type_id"].GetString();
	string spriteType = EnemyInfo["sprite_type"].GetString();
	int loc_x = EnemyInfo["locationX"].GetInt();
	int loc_y = EnemyInfo["locationY"].GetInt();
	float scale_x = EnemyInfo["scaleX"].GetFloat();
	float scale_y = EnemyInfo["scaleY"].GetFloat();
	float rotation = EnemyInfo["rotation"].GetFloat();
	int alpha = EnemyInfo["alpha"].GetInt();
	string path_to_texture = EnemyInfo["sprite_file_path"].GetString();
	bool collidable = EnemyInfo["collidable"].GetBool();
	bool isDynamic = EnemyInfo["isDynamic"].GetBool();
	float hitboxScaleX = EnemyInfo["hitboxScaleX"].GetFloat();
	float hitboxScaleY = EnemyInfo["hitboxScaleY"].GetFloat();
	types::Type object_type = static_cast<types::Type>(EnemyInfo["object_type"].GetInt());

	Enemy* the_obj = new Enemy(node_id, path_to_texture);

	the_obj->sprite_type = spriteType;
	the_obj->position.x = loc_x;
	the_obj->position.y = loc_y;
	the_obj->scaleX = scale_x;
	the_obj->scaleY = scale_y;
	the_obj->rotation = rotation;
	the_obj->alpha = alpha;
	the_obj->collidable = collidable;
	the_obj->isDynamic = isDynamic;
	the_obj->hitboxScaleX = hitboxScaleX;
	the_obj->hitboxScaleY = hitboxScaleY;
	the_obj->object_type = object_type;

	return the_obj;
}

Character* createCharacter(const Value& CharacterInfo) {
	string node_id = CharacterInfo["node_id"].GetString();
	string type_id = CharacterInfo["type_id"].GetString();
	string spriteType = CharacterInfo["sprite_type"].GetString();
	int loc_x = CharacterInfo["locationX"].GetInt();
	int loc_y = CharacterInfo["locationY"].GetInt();
	float scale_x = CharacterInfo["scaleX"].GetFloat();
	float scale_y = CharacterInfo["scaleY"].GetFloat();
	float rotation = CharacterInfo["rotation"].GetFloat();
	int alpha = CharacterInfo["alpha"].GetInt();
	string path_to_texture = CharacterInfo["sprite_file_path"].GetString();
	bool collidable = CharacterInfo["collidable"].GetBool();
	bool isDynamic = CharacterInfo["isDynamic"].GetBool();
	float hitboxScaleX = CharacterInfo["hitboxScaleX"].GetFloat();
	float hitboxScaleY = CharacterInfo["hitboxScaleY"].GetFloat();
	types::Type object_type = static_cast<types::Type>(CharacterInfo["object_type"].GetInt());

	string first_dialogue = CharacterInfo["first_dialogue"].GetString();
	string mid_dialogue = CharacterInfo["mid_dialogue"].GetString();
	string item_dialogue = CharacterInfo["item_dialogue"].GetString();
	string post_dialogue = CharacterInfo["post_dialogue"].GetString();
	string item_needed = CharacterInfo["item_needed"].GetString();
	string item_to_give = CharacterInfo["item_to_give"].GetString();
	string item_path = CharacterInfo["item_path"].GetString();
	

	Character* the_obj = new Character(node_id, path_to_texture);

	the_obj->sprite_type = spriteType;
	the_obj->position.x = loc_x;
	the_obj->position.y = loc_y;
	the_obj->scaleX = scale_x;
	the_obj->scaleY = scale_y;
	the_obj->rotation = rotation;
	the_obj->alpha = alpha;
	the_obj->collidable = collidable;
	the_obj->isDynamic = isDynamic;
	the_obj->hitboxScaleX = hitboxScaleX;
	the_obj->hitboxScaleY = hitboxScaleY;
	the_obj->object_type = object_type;
	
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

