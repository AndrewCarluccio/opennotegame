#ifndef CAMERA_H
#define CAMERA_H

#include "AffineTransform.h"

class Camera{ 

public:
	Camera();
	Camera::Camera(int orig_x, int orig_y, int left, int right, int up, int down);
	~Camera();

	int x = 0;
	int y = 0;
	//int viewportWidth = 1200;
	//int viewportHeight = 1000;
	int maxX, maxY, minX, minY;

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