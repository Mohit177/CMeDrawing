/**	\file Camera.h
Camera functions header file.
*/
#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include "Utility.h"
#define PI 3.14159265

#define SCREEN_WIDTH 1366.0f
#define SCREEN_HEIGHT 768.0f

class Camera {
	private:
		Point3 eye, look, up;
		Vector3 u, v, n;
		double viewAngle, aspect, nearDist, farDist;

	public:
		Camera();
		void setModelviewMatrix();
		void set(Point3 eye, Point3 look, Vector3 up);
		void roll(float angle);
		void pitch(float angle);
		void yaw(float angle);
		bool slide(float delU, float delV, float delN);
		void setShape(float vAng, float asp, float nearD, float farD);
		//void getShape(float &vAng, float &asp, float &nearD, float &farD);
};


#endif
