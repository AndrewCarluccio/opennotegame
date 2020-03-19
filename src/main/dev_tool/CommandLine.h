#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

#include "../engine/dev_tool/SceneWriter.h"
#include "../engine/Scene.h"

#include "DevTool.h"

// forard declaration to allow codependency
class DevTool;

class CommandLine {
    public:
        CommandLine(DevTool *instance);
        void run();

    private:
        DevTool *instance;
        void load();
        void save();
};

#endif