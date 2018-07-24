#pragma once
#ifndef _UGP_DEFINES_H_
#define _UGP_DEFINES_H_

#include<windows.h>
#include<stdio.h>

#define WinHWND HWND

//directInput
#define KEYS_SIZE          256


#define UGP_INFINITE -1
#define UGP_INVALID -1
#define UGP_OK       1
#define UGP_FAIL     0

#define LIGHT_SPOT         1
#define	LIGHT_DIRECTIONAL  2
#define LIGHT_POINT        3

// Types of controls we support.//////GUI¿Ø¼þ
#define UGP_GUI_STATICTEXT 1
#define UGP_GUI_BUTTON     2
#define UGP_GUI_BACKDROP   3

// Mouse button states. /////°´Å¥×´Ì¬
#define UGP_BUTTON_UP      1
#define UGP_BUTTON_OVER    2
#define UGP_BUTTON_DOWN    3
#define UGP_LEFT_BUTTON    0
#define UGP_RIGHT_BUTTON   1


#define PERCENT_OF(a, b) (int)(a * b)
#define GUI_FVF      2
#define MV_FVF       3


#define UGPCOLOR_ARGB(a,r,g,b) ((unsigned long)((((a)&0xff)<<24)|\
                               (((r)&0xff)<<16)|(((g)&0xff)<<8)|\
                               ((b)&0xff)))


enum PrimType
{
   NULL_TYPE,
   POINT_LIST,
   TRIANGLE_LIST,
   TRIANGLE_STRIP,
   TRIANGLE_FAN,
   LINE_LIST,
   LINE_STRIP
};

enum RenderState //Ã¶¾Ù Í¸Ã÷¶ÈµÄäÖÈ¾×´Ì¬
{
   CULL_NONE,
   CULL_CW,
   CULL_CCW,
   DEPTH_NONE,
   DEPTH_READONLY,
   DEPTH_READWRITE,
   SHADE_POINTS,
   SHADE_SOLIDTRI,
   SHADE_WIRETRI,
   SHADE_WIREPOLY,
   TRANSPARENCY_NONE,
   TRANSPARENCY_ENABLE
};

enum TransState //Í¸Ã÷¶È×´Ì¬Öµ
{
   TRANS_ZERO = 1,
   TRANS_ONE,
   TRANS_SRCCOLOR,
   TRANS_INVSRCCOLOR,
   TRANS_SRCALPHA,
   TRANS_INVSRCALPHA,
   TRANS_DSTALPHA,
   TRANS_INVDSTALPHA,
   TRANS_DSTCOLOR,
   TRANS_INVDSTCOLOR,
   TRANS_SRCALPHASAT,
   TRANS_BOTHSRCALPHA,
   TRANS_INVBOTHSRCALPHA,
   TRANS_BLENDFACTOR,
   TRANS_INVBLENDFACTOR
};

enum TextureState //ÎÆÀíÂË²¨Æ÷
{
   MIN_FILTER,
   MAG_FILTER,
   MIP_FILTER
};

enum FilterType //ÎÆÀíÂË²¨Æ÷ÀàÐÍ
{
   POINT_TYPE,
   LINEAR_TYPE,
   ANISOTROPIC_TYPE
};

enum UGP_MS_TYPE
{
	UGP_MS_NONE,
	UGP_MS_SAMPLES_2,
	UGP_MS_SAMPLES_4,
	UGP_MS_SAMPLES_8,
	UGP_MS_SAMPLES_16

};

enum UGP_FOG_TYPE
{
	UGP_VERTEX_FOG,
	UGP_PIXEL_FOG
};

typedef long VertexType;



#endif
