/**	@file Camera.cpp
Camera functions implementation file.
*/
#include "Camera.h"

/**
	Empty constructor to initialize a camera.
*/
Camera:: Camera(void)
{
	setShape(45.0f, SCREEN_WIDTH/SCREEN_HEIGHT, 0.01f, 1000.0f); 
	
	Point3 eyePoint = Point3( 0.0, 0.0, 0.0 );
	Point3 lookPoint = Point3( 0.0, 0.0, -20.0f );
	Vector3 upVector = Vector3( 0, 1, 0 );

	set( eyePoint, lookPoint, upVector );
}


/**
Method to set the Viewing volume.
@param vAngle:	Viewing angle.
@param asp:		Aspect ratio of the screen.
@param nr:		Near clipping plane.
@param fr:		Further clipping plane.
@return 		void
*/
void Camera :: setShape(float vAngle, float asp, float nr, float fr) 
{ 
    viewAngle = vAngle; 
    aspect = asp; 
    nearDist = nr; 
    farDist = fr; 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(viewAngle, aspect, nearDist, farDist); 
    glMatrixMode(GL_MODELVIEW); 
}

/**
Method to set the Model view matrix.
@param: void
@return void

*/
void Camera :: setModelviewMatrix(void)
{
	float m[16];
	Vector3 eVec(eye.x, eye.y, eye.z);
	m[0]=u.x;
	m[1]=v.x;
	m[2]=n.x;
	m[3]=0;
	m[4]=u.y;
	m[5]=v.y;
	m[6]=n.y;
	m[7]=0;
	m[8]=u.z;
	m[9]=v.z;
	m[10]=n.z;
	m[11]=0;
	m[12]=-eVec.dot(u);
	m[13]=-eVec.dot(v);
	m[14]=-eVec.dot(n);
	m[15]=1.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
}

/**
Method to update the eye, normal, view, and up vectors.
@param Eye: Point3 object containing the new location of eye.
@param look: Point3 object containing the new look location.
@param up:	Vector3 object containing the new up vector.
@return void
*/
void Camera:: set(Point3 Eye, Point3 look, Vector3 up)
{
	eye.set(Eye);
	n.set(eye.x - look.x, eye.y - look.y, eye.z - look.z);
	u.set(up.cross(n));
	
	v.set(n.cross(u));
	n.normalize();
	u.normalize();
	v.normalize();
	setModelviewMatrix(); 
}

/**
Method to slide the camera in the given direction.
@param delU: Change in Up vector.
@param delV: Change in View vector.
@param delN: Change in Normal vector.
@return true if camera slides successfullly(i.e. its new position is inside the park), false otherwise.
*/
bool Camera:: slide(float delU, float delV, float delN){
	
	if(eye.x + delU * u.x + delV * v.x + delN * n.x >100 || eye.x + delU * u.x + delV * v.x + delN * n.x < -100)	return false;
	if(eye.y + delU * u.y + delV * v.y + delN * n.y >100 || eye.y + delU * u.y + delV * v.y + delN * n.y < 0)		return false;
	if(eye.z + delU * u.z + delV * v.z + delN * n.z >100 || eye.z + delU * u.z + delV * v.z + delN * n.z < -100)	return false;
	
	eye.x += delU * u.x + delV * v.x + delN * n.x;
	eye.y += delU * u.y + delV * v.y + delN * n.y;
	eye.z += delU * u.z + delV * v.z + delN * n.z;
	
	look.x += delU * u.x + delV * v.x + delN * n.x;
	look.y += delU * u.y + delV * v.y + delN * n.y;
	look.z += delU * u.z + delV * v.z + delN * n.z;
	setModelviewMatrix();
	return true;
}

/**
Method to roll the view, along the front-to-back axis.
@param angle: Angle of rotation.
@return void
*/
void Camera:: roll(float angle)
{
	float cs= cos(PI/180 * angle);
	float sn= sin(PI/180 * angle);
	Vector3 t(u);
	u.set(cs* t.x - sn*v.x,cs*t.y - sn*v.y, cs*t.z - sn*v.z);
	v.set(cs* v.x + sn*t.x,cs*v.y + sn*t.y, cs*v.z + sn*t.z);
	setModelviewMatrix();
}


/**
Method to pitch the view, along side-to-side axis.
@param angle: Angle of rotation.
@return void
*/
void Camera:: pitch(float angle)
{
	float cs= cos(PI/180 * angle);
	float sn= sin(PI/180 * angle);
	Vector3 t(v);
	v.set(cs * t.x - sn * n.x,cs * t.y - sn * n.y, cs * t.z - sn * n.z);
	n.set(cs * n.x + sn * v.x, cs * n.y + sn * v.y, cs * n.z + sn * v.z);
	setModelviewMatrix(); 
}

/**
Method to yaw the view, along vertical axis.
@param angle: Angle of rotation.
@return void
*/
void Camera:: yaw(float angle)
{
	float cs= cos(PI/180 * angle);
	float sn= sin(PI/180 * angle);
	Vector3 t(u);
	u.set(cs* t.x + sn * n.x, cs* t.y + sn * n.y, cs* t.z + sn * n.z);
	n.set(cs* n.x - sn* u.x, cs* n.y - sn* u.y, cs* n.z - sn* u.z);
	setModelviewMatrix(); 
}
