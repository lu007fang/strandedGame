#pragma once
#ifndef _UGP_STRUCTS_H_
#define _UGP_STRUCTS_H_


// A structure for our custom vertex type.
struct stGUIVertex
{
    float x, y, z, rhw;
    unsigned long color;
    float tu, tv;
};

#define D3DFVF_GUI (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

struct stModelVertex
{
    float x, y, z;
	float nx, ny, nz;
    unsigned long color;
    float tu, tv;
};

#define D3DFVF_MV (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#endif