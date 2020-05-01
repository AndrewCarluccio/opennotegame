#ifndef TYPES_H
#define TYPES_H

namespace types {
    // Maybe give this a better name
    enum Type {
        Default,                // 0
        Player,                 // 1
        Platform,               // 2
        TransitionPoint,        // 3
        Enemy,                  // 4
        Boss,                   // 5
        EnvironmentalObject,    // 6
        Character,              // 7
        Item,                   // 8
        Health,                 // 9
        PowerUp,                // 10
        Weapon,                 // 11
        CloudPlatform,          // 12
        // Add additional types above this line 
        COUNT
    };
}

#endif