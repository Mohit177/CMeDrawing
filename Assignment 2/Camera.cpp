#include "Camera.h"

Camera:: Camera(void)
{
	setShape(45.0f, SCREEN_WIDTH/SCREEN_HEIGHT, 25.0f, 1000.0f); 
	
	Point3 eyePoint = Point3( 0.0, 0.0, 20.0 );
	Point3 lookPoint = Point3( 0.0, 0.0, -20.0f );
	Vector3 upVector = Vector3( 0, 1, 0 );

	set( eyePoint, lookPoint, upVector );
}


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

void Camera:: slide(float delU, float delV, float delN)
{
	
	if(eye.x + delU * u.x + delV * v.x + delN * n.x >100 || eye.x + delU * u.x + delV * v.x + delN * n.x < -100)	return;
	if(eye.y + delU * u.y + delV * v.y + delN * n.y >100 || eye.y + delU * u.y + delV * v.y + delN * n.y < 0)	return;
	if(eye.z + delU * u.z + delV * v.z + delN * n.z >100 || eye.z + delU * u.z + delV * v.z + delN * n.z < -100)	return;
	
	eye.x += delU * u.x + delV * v.x + delN * n.x;
	eye.y += delU * u.y + delV * v.y + delN * n.y;
	eye.z += delU * u.z + delV * v.z + delN * n.z;
	
	
	look.x += delU * u.x + delV * v.x + delN * n.x;
	look.y += delU * u.y + delV * v.y + delN * n.y;
	look.z += delU * u.z + delV * v.z + delN * n.z;
	setModelviewMatrix();
}

void Camera:: roll(float angle)
{
	float cs= cos(PI/180 * angle);
	float sn= sin(PI/180 * angle);
	Vector3 t(u);
	u.set(cs* t.x - sn*v.x,cs*t.y - sn*v.y, cs*t.z - sn*v.z);
	v.set(cs* v.x + sn*t.x,cs*v.y + sn*t.y, cs*v.z + sn*t.z);
	setModelviewMatrix();
}

void Camera:: pitch(float angle)
{
	float cs= cos(PI/180 * angle);
	float sn= sin(PI/180 * angle);
	Vector3 t(v);
	v.set(cs * t.x - sn * n.x,cs * t.y - sn * n.y, cs * t.z - sn * n.z);
	n.set(cs * n.x + sn * v.x, cs * n.y + sn * v.y, cs * n.z + sn * v.z);
	setModelviewMatrix(); 
}

void Camera:: yaw(float angle)
{
	float cs= cos(PI/180 * angle);
	float sn= sin(PI/180 * angle);
	Vector3 t(u);
	u.set(cs* t.x + sn * n.x, cs* t.y + sn * n.y, cs* t.z + sn * n.z);
	n.set(cs* n.x - sn* u.x, cs* n.y - sn* u.y, cs* n.z - sn* u.z);
	setModelviewMatrix(); 
}
