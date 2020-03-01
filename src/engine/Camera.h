#ifndef CAMERA_H
#define CAMERA_H

#include "AffineTransform.h"

class Camera{ 

public:
	Camera();
	Camera(int viewport_width, int viewport_height); //you pass in the dimensions of the window here
	~Camera();

	int originX;
	int originY;

	int x = 0;
	int y = 0;
	int maxX, maxY, minX, minY; //these are RELATIVE TO THE CENTER OF THE SCREEN

	double zoom = 1.0;

	void applyCamera(AffineTransform& at);
	void undoCamera(AffineTransform& at);

	float scrollRate = 1.0;

	//Will return true if either x or y is changed, or both
	bool moveCameraBy(int dx, int dy);
	bool moveCameraTo(int xpos, int ypos);

	bool setZoom(double z);

	void setBounds(int l, int r, int u, int d);

private:

	
};

#endif