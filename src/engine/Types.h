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
        PowerUp,  // 5 - automatically equipped upon impact
        Eraser, // 6 <- not implemented yet
        PaintBrush, // 7
        Cat, // 8
        Character, // 9
        Item, // 10 - items that you use manually, or need to give to someone
        Weapon, // 11 - automatically equiped upon impact, has a sprite 
        Health, // 12 - things that boost health upon impact, has sprite -> disappears after collision (unless it's an office hour ball)
        Car,
        // Add additional types above this line 
        COUNT
    };
}

#endif