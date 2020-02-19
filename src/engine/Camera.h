#ifndef CAMERA_H
#define CAMERA_H

#include "AffineTransform.h"

class Camera{ 

public:
	Camera();
	~Camera();

	int x = 0;
	int y = 0;
	int viewportWidth = 500;
	int viewportHeight = 500;

	void applyCamera(AffineTransform& at);
	void undoCamera(AffineTransform& at);

private:

	
};

#endif