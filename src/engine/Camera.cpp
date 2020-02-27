#include "Camera.h"
#include <iostream>

Camera::Camera() {

}

Camera::Camera(int orig_x, int orig_y, int left, int right, int up, int down) {
	x = orig_x;
	y = orig_y;

	minX = orig_x - left;
	maxY = orig_y - up;
	maxX = orig_x + right;
	minY = orig_y - down;
}

void Camera::applyCamera(AffineTransform& at) {
	at.translate(int(x*scrollRate), int(y*scrollRate));
	at.scale(zoom, zoom);
}

void Camera::undoCamera(AffineTransform& at) {
	at.scale(1.0 / zoom, 1.0 / zoom);
	at.translate(int(-x*scrollRate), int(-y*scrollRate));
}

bool Camera::moveCameraBy(int dx, int dy) {
	bool ret = false;
	if ((x + dx*zoom) < maxX && (x + dx * zoom) > minX) {
		x += dx*zoom;
		ret = true;
	}
	if ((y + dy*zoom) < maxY && (y + dy * zoom) > minY) {
		y += dy*zoom;
		ret = true;
	}
	cout << "x ";
	cout << x << endl;
	cout << "y ";
	cout << y << endl;
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

bool Camera::setZoom(double z) {
	//viewportHeight = (viewportHeight / zoom) *z;
	//viewportWidth = (viewportWidth / zoom) * z;

	zoom = z;

	return true;
}

void Camera::setBounds(int l, int r, int u, int d) {
	minX = x - l;
	maxY = y - u;
	maxX = x + r;
	minY = y - d;
}