#pragma once
#ifndef _UGP_PHYSICS_MASS_H_
#define _UGP_PHYSICS_MASS_H_

#include"Vector.h"
#include <stdio.h>

struct stPointMass
{
   stPointMass() : m(0) {}
   float m;
   CVector3 pos;
   CVector3 velocity;
   CVector3 force;
};


inline void ApplyForce(CVector3 force, stPointMass *m)
{
   if(m != NULL) 
	   m->force += force;
}


inline void SimulateMass(float dt, stPointMass *m)
{
   // Calculate new velocity and position.
   if(m != NULL)
      {
         m->velocity += (m->force / m->m) * dt;
         m->pos += m->velocity * dt;
      }
}

#endif