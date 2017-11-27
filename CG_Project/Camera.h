/**	@file Camera.h
* Camera functions header file.
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
/**
Camera class for defining view and motion.
*/
class Camera {
	private:
		Point3 eye;		//!< Eye coordinates
		Point3 look;	//!< Look point coordinates
		Point3 up;		//!< Up point coordinates
		Vector3 u;		//!< Up vector
		Vector3 v; 		//!< view vector
		Vector3 n;		//!< Normal vector
		double viewAngle; //!< Field of view
		double aspect;	//!< Aspect ratio
		double nearDist;	//!< Near clipping plane
		double farDist;		//!< Far clipping plane

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
