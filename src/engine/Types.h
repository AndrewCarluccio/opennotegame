#ifndef TYPES_H
#define TYPES_H

namespace types {
    // Maybe give this a better name
    enum Type {
        Default,  // 0
        Player,   // 1
        Platform, // 2
        Enemy,    // 3
        HiggsBoson, // 4
        PowerUp,  // 5
        Eraser, // 6 <- not implemented yet
        PaintBrush, // 7
        Cat, // 8
        Character, // 9



        // Add additional types above this line 
        COUNT
    };
}

#endif