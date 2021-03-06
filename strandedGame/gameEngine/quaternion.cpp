#include "quaternion.h"

CQuaternion::CQuaternion()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 1.0f;
}

CQuaternion::CQuaternion(float xAxis,float yAxis,float zAxis,float wAxis)
{
	x = xAxis;
	y = yAxis;
	z = zAxis;
	w = wAxis;
}

void CQuaternion::operator=(const CQuaternion &q)
{
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;
}

CQuaternion CQuaternion::operator*(const CQuaternion &q)
{
	return CQuaternion(w * q.x + x*q.w + y*q.z - z*q.y,
					   w * q.y - x*q.z + y*q.w + z*q.x,
					   w * q.z + x*q.y - y*q.x + z*q.w,
					   w * q.w - x*q.x - y*q.y - z*q.z);
}

CQuaternion CQuaternion::operator+(const CQuaternion &q)
{
	CQuaternion result;

	CVector3 v1(x,y,z), v2(q.x,q.y,q.z), cross, v3;
	float newW = 0;

	cross.CrossProduct(v2,v1);

	v1 *= q.w;
	v2 *= w;
	v3 = v1+v2;

	v3 = cross+v3;

	newW = w*q.w - (x*q.x + y*q.y + z*q.z);

	result.x = v3.x;
	result.y = v3.y;
	result.z = v3.z;
	result.w = newW;

	return result;
}

void CQuaternion::CreateQuatFromAxis(CVector3 &a, float radians)
{
	float sine = 0.0f;

	radians = radians * 0.5f;
	sine = (float)sin(radians);

	a.Normal();

	x = a.x;
	y = a.y;
	z = a.z;

	x *= sine;
	y *= sine;
	z *= sine;
	w = (float)cos(radians);
}

float CQuaternion::Length()
{
	return (float)sqrt(x*x+y*y+z*z+w*w);
}

void CQuaternion::Normal()
{
	float len = Length();
	len = 1/len;

	x = x*len;
	y = y*len;
	z = z*len;
	w = w*len;
}

CQuaternion CQuaternion::Conjugate()
{
	return CQuaternion(-x,-y,-z,w);
}

CQuaternion CQuaternion::CrossProduct(const CQuaternion &q)
{
	CQuaternion crossProduct;
	
	crossProduct.x = w*q.x + x*q.w + y*q.z - z*q.y;
	crossProduct.y = w*q.y + x*q.x + y*q.w - z*q.x;
	crossProduct.z = w*q.z + x*q.y + y*q.x - z*q.z;
	crossProduct.w = w*q.w + x*q.z + y*q.y - z*q.w;

	return crossProduct;
}

void CQuaternion::Rotatef(float amount,float xAixs,float yAixs,float zAixs)
{
	if((xAixs + yAixs +zAixs) != 1)
	{
		float length = (float)sqrt(xAixs*xAixs + yAixs*yAixs +zAixs*zAixs);
		xAixs /= length;
		yAixs /= length;
		zAixs /= length;
	}

	float angle = GET_RADIANS(amount);
	float sine = (float)sin(angle/2.0f);

	w = (float)cos(angle/2.0f);
	x = xAixs*sine;
	y = yAixs*sine;
	z = zAixs*sine;
}

void CQuaternion::RotationRadiansf(double X,double Y,double Z)
{
	double cosX ,cosY,cosZ;
	double sinX ,sinY,sinZ;
	double cosXY,sinXY;

	sinX = sin(X*0.5);
	cosX = cos(X*0.5);

	sinY = sin(Y*0.5);
	cosY = cos(Y*0.5);

	sinZ = sin(Z*0.5);
	cosZ = cos(Z*0.5);

	cosXY = cosX*cosY;
	sinXY = sinX*sinY;
	w = (float)(cosXY * cosZ + sinXY * sinZ);
	x = (float)(sinX * cosY * cosZ - cosX * sinY * sinZ);
	y = (float)(cosX * sinY * cosZ + sinX * cosY * sinZ);
	z = (float)(cosXY * sinZ - sinXY * cosZ);

}

void CQuaternion::CreateMatrix(float* pMatrix)
{
	if(!pMatrix) return;

	pMatrix[0] = 1.0f - 2.0f*(y*y + z*z); 
	pMatrix[1] = 2.0f * (x*y + z*w); 
	pMatrix[2] = 2.0f * (x*z - y*w); 
	pMatrix[3] = 0.0f;

	pMatrix[4] = 2.0f * (x*y - z*w); 
	pMatrix[5] = 1.0f - 2.0f * (x*x + z*z); 
	pMatrix[6] = 2.0f * (z*y - x*w); 
	pMatrix[7] = 0.0f; 

	pMatrix[8] = 2.0f * (x*z + y*w); 
	pMatrix[9] = 2.0f * (x*z - y*w); 
	pMatrix[10] = 1.0f - 2.0f * (x*x + y*y); 
	pMatrix[11] = 0.0f; 

	pMatrix[12] = 0.0f;
	pMatrix[13] = 0.0f; 
	pMatrix[14] = 0.0f; 
	pMatrix[15] = 1.0f; 
}

void CQuaternion::slerp(const CQuaternion &q1,const CQuaternion &q2,float t)
{
	float cosTheta = 0.0f;
	float sinTheta = 0.0f;
	float beta = 0.0f;

	float q2Array[4];

	q2Array[0] = q2.x;
	q2Array[1] = q2.y;
	q2Array[2] = q2.z;
	q2Array[3] = q2.w;

	cosTheta = q1.x * q2.x + q1.y* q2.y + q1.z * q2.z + q1.w * q2.w;

	if(cosTheta < 0.0f)
	{
		q2Array[0] = -q2Array[0];
		q2Array[1] = -q2Array[1];
		q2Array[2] = -q2Array[2];
		q2Array[3] = -q2Array[3];

		cosTheta = -cosTheta;
	}		

	beta = 1.0f - t;
	if(1.0f - cosTheta > 0.001f)
	{
		cosTheta = (float)acos(cosTheta);
		sinTheta = 1.0f/(float)sin(cosTheta);
		beta = (float)sin(cosTheta*beta)*sinTheta;
		t = (float)sin(cosTheta*t)*sinTheta;
	}

	x = beta * q2.x + t* q2Array[0];
	y = beta * q2.y + t* q2Array[1];
	z = beta * q2.z + t* q2Array[2];
	w = beta * q2.w + t* q2Array[3];
}