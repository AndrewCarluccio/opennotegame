#include "Camera.h"

Camera::Camera() {

}

void Camera::applyCamera(AffineTransform& at){
	at.translate(x,y);
}

void Camera::undoCamera(AffineTransform& at) {
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
	if (xpos < viewportWidth) {
		x = xpos;
		ret = true;
	}
	if (y < ypos) {
		y = ypos;
		ret = true;
	}
	return ret;
}