#include "Camera.h"
#include <iostream>

Camera::Camera() {

}

Camera::Camera(int viewport_width, int viewport_height) {
	//originX = viewport_width /2.0;
	//originY = viewport_height / 2.0;

	x = 0;
	y = 0;

	minX = viewport_width / 2.0;
	maxX = viewport_width / 2.0;

	minY = viewport_height / 2.0;
	maxY = viewport_height / 2.0;
}

void Camera::applyCamera(AffineTransform& at) {
	at.scale(zoom, zoom);
	at.translate(int(x), int(y));
	
}

void Camera::applyCameraScale(AffineTransform& at) {
	at.scale(zoom, zoom);

}
 
void Camera::applyCameraTrans(AffineTransform& at) {
	at.translate(int(x), int(y));

}

void Camera::undoCameraScale(AffineTransform& at) {
	at.scale(1.0 / zoom, 1.0 / zoom);

}

void Camera::undoCameraTrans(AffineTransform& at) {
	at.scale(1.0 / zoom, 1.0 / zoom);

}

void Camera::undoCamera(AffineTransform& at) {
	at.translate(int(-x), int(-y));
	at.scale(1.0 / zoom, 1.0 / zoom);

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
	cout << ret << endl;
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
	minX = -l;  
	maxX = r;

	minY = -u;
	maxY = d;
}