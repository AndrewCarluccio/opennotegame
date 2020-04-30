#include "SceneWriter.h"

SceneWriter::SceneWriter(Scene *scene) {
    this->scene = scene;
    this->s = new StringBuffer();
    this->writer = new PrettyWriter<StringBuffer>(*s);
}

SceneWriter::~SceneWriter() {
    delete s;
    delete writer;
}

void SceneWriter::saveScene(std::string filepath) {
    saveObject(writer, scene->root->children[0]);

    std::ofstream of;
    of.open(filepath);
    of << s->GetString();
    of.close();

    if (!of.good())
        throw std::runtime_error("Can't write the JSON string to the file!");
}

void SceneWriter::saveObject(PrettyWriter<StringBuffer> *writer, DisplayObject *object) {
    writer->StartObject();
    if (dynamic_cast<TransitionPoint *>(object) != NULL) {
        saveTransitionPoint(writer, (TransitionPoint *)object);
    }else if (dynamic_cast<Character*>(object) != NULL) {
        saveCharacter(writer, (Character *)object);
    }else if (dynamic_cast<DisplayObjectContainer*>(object) != NULL) {
        saveDisplayObjectContainer(writer, (DisplayObjectContainer *)object);
    } else {
        saveDisplayObject(writer, object);
    }
    writer->EndObject();
}

void SceneWriter::saveDisplayObject(PrettyWriter<StringBuffer> *writer, DisplayObject *object) {
    writer->Key("node_id");
    writer->String(object->id.c_str());
    writer->Key("type_id");
    writer->String(object->type.c_str());
    writer->Key("sprite_type");
    writer->String(object->sprite_type.c_str());
    writer->Key("locationX");
    writer->Int(object->position.x);
    writer->Key("locationY");
    writer->Int(object->position.y);
    writer->Key("scaleX");
    writer->Double(object->scaleX);
    writer->Key("scaleY");
    writer->Double(object->scaleY);
    writer->Key("rotation");
    writer->Double(object->rotation);
    writer->Key("alpha");
    writer->Int(object->alpha);
    writer->Key("sprite_file_path");
    writer->String(object->imgPath.c_str());
    writer->Key("collidable");
    writer->Bool(object->collidable);
    writer->Key("isDynamic");
    writer->Bool(object->isDynamic);
    writer->Key("hitboxScaleX");
    writer->Double(object->hitboxScaleX);
    writer->Key("hitboxScaleY");
    writer->Double(object->hitboxScaleY);
    writer->Key("object_type");
    writer->Int(object->object_type);
}

void SceneWriter::saveDisplayObjectContainer(PrettyWriter<StringBuffer> *writer, DisplayObjectContainer *object) {
    saveDisplayObject(writer, object);
    writer->Key("children");
    writer->StartArray();
    for (const auto&child: object->children) {
        saveObject(writer, child);
    }
    writer->EndArray();

}

void SceneWriter::saveTransitionPoint(PrettyWriter<StringBuffer> *writer, TransitionPoint *tp) {
    saveDisplayObjectContainer(writer, tp);
    writer->Key("transition_scene_name");
    writer->String(tp->transition_scene_name.c_str());

}

void SceneWriter::saveCharacter(PrettyWriter<StringBuffer> *writer, Character *c) {
    saveDisplayObjectContainer(writer, c);
    writer->Key("first_dialogue");
    writer->String(c->firstDialogue.c_str());
    writer->Key("mid_dialogue");
    writer->String(c->midDialogue.c_str());
    writer->Key("item_dialogue");
    writer->String(c->itemDialogue.c_str());
    writer->Key("post_dialogue");
    writer->String(c->postDialogue.c_str());
    writer->Key("item_needed");
    writer->String(c->itemNeeded.c_str());
    writer->Key("item_to_give");
    writer->String(c->itemToGive.c_str());
    writer->Key("item_path");
    writer->String(c->itemPath.c_str());

}
