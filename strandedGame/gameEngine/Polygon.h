#pragma once
#ifndef __UGP_POLYGON_H_
#define __UGP_POLYGON_H_

#include"Vector.h"
#include"Ray.h"
//#include"Plane.h"
#include"mathDefine.h"


class CPolygon
{
   public:
      CPolygon() { }

     // void SetFlag(unsigned int fl) { m_flag = fl; }
      //unsigned int GetFlag() { return m_flag; }
      void Copy(CPolygon &pol);

      //void Clip(CPlane &pl, CPolygon *front, CPolygon *back);
      
      bool Intersect(CRay &ray, bool cull, float *dist);

      //unsigned int m_flag;
      CVector3 m_vertexList[3];
};

#endif