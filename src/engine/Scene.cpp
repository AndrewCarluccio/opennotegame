#include "Scene.h"

Scene::Scene() {
	root = new DisplayObjectContainer();
	foreground = new DisplayObjectContainer();
	midground = new DisplayObjectContainer();
	background = new DisplayObjectContainer();

	root->addChild(background);
	root->addChild(midground);
	root->addChild(foreground);

	parent_ids.push_back("0000");
	parent_ids.push_back("0001");
	parent_ids.push_back("0002");
	parent_ids.push_back("0003");

}

void Scene::loadScene(string sceneFilePath) {
	/*
	PARSE THE JSON HERE
	
	For now, I made two lists of strings, you need to change them to whatever JSON wrapper you are going to use

	FOR NOW I AM ASSUMING PARENTS ALWAYS LISTED BEFORE CHILDREN!
	*/
		for (/*JSON TYPE*/ string json_package : the_list) {
			//TODO: Populate these fileds from the JSON package
			string node_id = "";
			string parent_id = ""; //ID 0000 is root, ID 0001 is background, 0002 is midground, 0003 is foreground
			string type_id = "";
			int loc_x = 0;
			int loc_y = 0;
			int scale_x = 0;
			int scale_y = 0;
			int rotation = 0;
			int alpha = 0;
			string path_to_texture = "";

			if ((std::find(parent_ids.begin(), parent_ids.end(), parent_id)) != parent_ids.end()) {
				if (type_id == "DisplayObject") {

					DisplayObject* the_obj = new DisplayObject(node_id, path_to_texture);

					the_obj->position.x = loc_x;
					the_obj->position.y = loc_y;
					the_obj->scaleX = scale_x;
					the_obj->scaleY = scale_y;
					the_obj->rotation = rotation;
					the_obj->alpha = alpha;


					if (parent_id == "0000") {
						//add to root
						root->addChild(the_obj);
					}
					else if (parent_id == "0001") {
						//add to bg
						background->addChild(the_obj);
					}
					else if (parent_id == "0002") {
						//add to mg
						midground->addChild(the_obj);
					}
					else if (parent_id == "0003") {
						//add to fg
						foreground->addChild(the_obj);
					}
					else {
						//search display tree for parent
						DisplayObjectContainer* parent = static_cast<DisplayObjectContainer*>(root->getChild(parent_id));
						parent->addChild(the_obj);
					}
				}
				else if (type_id == "DisplayObjectContainer") {
					DisplayObjectContainer* the_obj = new DisplayObjectContainer(node_id, path_to_texture);

					the_obj->position.x = loc_x;
					the_obj->position.y = loc_y;
					the_obj->scaleX = scale_x;
					the_obj->scaleY = scale_y;
					the_obj->rotation = rotation;
					the_obj->alpha = alpha;


					if (parent_id == "0000") {
						//add to root
						root->addChild(the_obj);
					}
					else if (parent_id == "0001") {
						//add to bg
						background->addChild(the_obj);
					}
					else if (parent_id == "0002") {
						//add to mg
						midground->addChild(the_obj);
					}
					else if (parent_id == "0003") {
						//add to fg
						foreground->addChild(the_obj);
					}
					else {
						//search display tree for parent
						DisplayObjectContainer* parent = static_cast<DisplayObjectContainer*>(root->getChild(parent_id));
						parent->addChild(the_obj);
					}
				}
				else if (type_id == "Sprite") {
					Sprite* the_obj = new Sprite(node_id, path_to_texture);

					the_obj->position.x = loc_x;
					the_obj->position.y = loc_y;
					the_obj->scaleX = scale_x;
					the_obj->scaleY = scale_y;
					the_obj->rotation = rotation;
					the_obj->alpha = alpha;


					if (parent_id == "0000") {
						//add to root
						root->addChild(the_obj);
					}
					else if (parent_id == "0001") {
						//add to bg
						background->addChild(the_obj);
					}
					else if (parent_id == "0002") {
						//add to mg
						midground->addChild(the_obj);
					}
					else if (parent_id == "0003") {
						//add to fg
						foreground->addChild(the_obj);
					}
					else {
						//search display tree for parent
						DisplayObjectContainer* parent = static_cast<DisplayObjectContainer*>(root->getChild(parent_id));
						parent->addChild(the_obj);
					}
				}
				else if (type_id == "AnimatedSprite") {
					AnimatedSprite* the_obj = new AnimatedSprite(node_id);
					//somehow associate texture

					the_obj->position.x = loc_x;
					the_obj->position.y = loc_y;
					the_obj->scaleX = scale_x;
					the_obj->scaleY = scale_y;
					the_obj->rotation = rotation;
					the_obj->alpha = alpha;


					if (parent_id == "0000") {
						//add to root
						root->addChild(the_obj);
					}
					else if (parent_id == "0001") {
						//add to bg
						background->addChild(the_obj);
					}
					else if (parent_id == "0002") {
						//add to mg
						midground->addChild(the_obj);
					}
					else if (parent_id == "0003") {
						//add to fg
						foreground->addChild(the_obj);
					}
					else {
						//search display tree for parent
						DisplayObjectContainer* parent = static_cast<DisplayObjectContainer*>(root->getChild(parent_id));
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

