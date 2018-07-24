/*
   Demo Name:  Game Project 11
      Author:  Allen Sherrod
     Chapter:  Chapter 12
*/


#ifndef _OBJ_LOADER_H_
#define _OBJ_LOADER_H_

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"Token.h"

// Pretty straight forward don't you think?
struct stObjModel
{
   float *vertices;
   float *normals;
   float *texCoords;
   int numFaces;
};

stObjModel *LoadOBJModel(char *fileName);
void FreeOBJModel(stObjModel *model);

#endif