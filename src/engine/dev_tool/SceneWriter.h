#ifndef SCENE_WRITER_H
#define SCENE_WRITER_H

#include "Scene.h"
#include <string>
#include <iostream>
#include "../../plugins/rapidjson/document.h"
#include "../../plugins/rapidjson/prettywriter.h"
#include "../../plugins/rapidjson/stringbuffer.h"

using namespace rapidjson;

class SceneWriter {
    public:
        SceneWriter(Scene *scene);
        ~SceneWriter();
        void saveScene(std::string filepath);
        void saveObject(PrettyWriter<StringBuffer> *writer, DisplayObject *object);
        void saveDisplayObject(PrettyWriter<StringBuffer> *writer, DisplayObject *object);
        void saveDisplayObjectContainer(PrettyWriter<StringBuffer> *writer, DisplayObjectContainer *object);
    private:
        Scene *scene;
        StringBuffer *s;
        PrettyWriter<StringBuffer> *writer;
};

#endif