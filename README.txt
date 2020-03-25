COMPILATION AND EXECUTION
The dev tool should be able to compile on Unix using make. It has only been tested on Linux so there may be issues with Mac. The name of the binary built is still myGame, so it can be run using ./bin/myGame

FEATURES
SCENE EDITING
The program should launch and display a bar with several sprites, as well as the scene contained within camera_demo.json with a grid overlayed on top ofit. The editor supports clicking and dragging a sprite from the bar onto the grid, with the sprite snapping to the nearest cell when the mouse is released.  
SCENE LOADING
In order to load a scene, push the L key when focused on the game window. Then open up the terminal, and you will be prompted to type in a file name of the scene you want to load. This file must be located in the resources/Scenes directory. Currently camera_demo.json, as well as any files created by the editor are able to be loaded. Note you may have to type the filename multiple times due to the way key presses are currently implemented

SCENE SAVING
To save a scene, push the S key when focused on the game window. Then navigate to the terminal; you will be prompted to enter the name of the json file to save the scene as. As with scene loading, you may need to enter the filename multiple times.
1. At the beginning, the car fades in at the bottom left corner.
2. Control the car with the arrow keys.
3. Move the car across the screen to the coin.
