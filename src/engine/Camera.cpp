#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(int xpos, int ypos) {
	x = xpos / 2;
	y = ypos / 2;

	viewportHeight = ypos;
	viewportWidth = xpos;
}

void Camera::applyCamera(AffineTransform& at){
	
	at.translate(x,y);
	at.scale(zoom, zoom);
}

void Camera::undoCamera(AffineTransform& at) {
	at.scale(1.0 / zoom, 1.0 / zoom);
	at.translate(-x, -y);
}


bool Camera::moveCameraBy(int dx, int dy) {
	bool ret = false;
	if ((x + dx) < viewportWidth) {
		x += dx;
		ret = true;
	}
	if ((y + dy) < viewportHeight) {
		y += dy;
		ret = true;
	}
	return ret;
}

bool Camera::moveCameraTo(int xpos, int ypos) {
	bool ret = false;
	/*
	if (xpos < viewportWidth) {
		x = xpos;
		ret = true;
	}
	if (y < ypos) {
		y = ypos;
		ret = true;
	}
	*/
	x = xpos;
	y = ypos;
	return ret;
}