#ifndef CAMERA_H
#define CAMERA_H

#include "AffineTransform.h"

class Camera{ 

public:
	Camera();
	Camera(int xpos, int ypos);
	~Camera();

	int x = 0;
	int y = 0;
	int viewportWidth = 1200;
	int viewportHeight = 1000;

	double zoom = 1.0;

	void applyCamera(AffineTransform& at);
	void undoCamera(AffineTransform& at);

	//Will return true if either x or y is changed, or both
	bool moveCameraBy(int dx, int dy);
	bool moveCameraTo(int xpos, int ypos);

private:

	
};

#endif