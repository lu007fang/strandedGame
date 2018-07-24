#pragma once
#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include <math.h>
#include "vector.h"
#include "mathDefine.h"

class CQuaternion
{
public:
	CQuaternion();
	CQuaternion(float xAxis,float yAxis,float zAxis,float wAxis);

	void operator=(const CQuaternion &q);
	CQuaternion operator+(const CQuaternion &q);
	CQuaternion operator*(const CQuaternion &q);

	void CreateQuatFromAxis(CVector3 &a, float radians);

	float Length();
	void Normal();

	CQuaternion Conjugate();
	CQuaternion CrossProduct(const CQuaternion &q);

	void Rotatef(float amount,float xAixs,float yAixs,float zAixs);
	void RotationRadiansf(double X,double Y,double Z);
	void CreateMatrix(float* pMatrix);
	void slerp(const CQuaternion &q1,const CQuaternion &q2,float t);

	float w,x,y,z;

};

#endif