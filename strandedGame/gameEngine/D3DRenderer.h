#pragma once
#ifndef _UGP_D3DRENDERER_H_
#define _UGP_D3DRENDERER_H_

#include<Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include"RenderInterface.h"
#include"UMFLoader.h"
#include"OBJLoader.h"
#include "XMesh.h"

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

struct stD3DStaticBuffer //静态顶点缓存结构体
{
	stD3DStaticBuffer() : vbPtr(0), 
		                  ibPtr(0), 
		                  numVerts(0), 
                          numIndices(0),
		                  stride(0),
		                  fvf(0), 
                          primType(NULL_TYPE) {} 

   LPDIRECT3DVERTEXBUFFER9 vbPtr;  //顶点缓存
   LPDIRECT3DINDEXBUFFER9 ibPtr;  //索引缓存
   int numVerts;  //顶点的计数
   int numIndices;  //索引的计数
   int stride;   //单个顶点尺寸幅度
   unsigned long fvf; //顶点FVF
   PrimType primType;  //静态缓存的图元类型
};

struct stD3DTexture //贴图对象 
{
   stD3DTexture() : fileName(0), image(0), width(0), height(0) {}

   char *fileName;
   int width, height;
   LPDIRECT3DTEXTURE9 image; 
};
/*
class CXModel
{
   public:
      CXModel()
      {
         model = NULL;
         numMaterials = 0;
         matList = NULL;
         textureList = NULL;
      }
      
      void Shutdown()
      {
         if(model != NULL) model->Release();
         model = NULL;

         if(textureList)
            {
               for(unsigned long i = 0; i < numMaterials; i++)
                  {
                     if(textureList[i] != NULL)
                        {
                           textureList[i]->Release();
                           textureList[i] = NULL;
                        }
                  }
            }

         if(matList != NULL)
            {
               delete[] matList;
               matList = NULL;
            }

         if(textureList != NULL)
            {
               delete[] textureList;
               textureList = NULL;
            }
      }

      LPD3DXMESH model;
      unsigned long numMaterials;
      D3DMATERIAL9 *matList;
      LPDIRECT3DTEXTURE9 *textureList;
};

*/

class CD3DRenderer : public CRenderInterface 
{
	public:
	      
	//设置成员变量初始值
	CD3DRenderer();
	~CD3DRenderer();

///////////////////////////////////       engine初始化         ////////////////////////////

	bool Initialize(int w, int h, WinHWND mainWin, bool fullScreen,UGP_MS_TYPE ms);
	
	void Shutdown(); //清楚渲染系统
	void SetClearCol(float r, float g, float b);

///////////////////////////////////       渲染场景         ////////////////////////////

	void StartRender(bool bColor, bool bDepth,bool bStencil);
	void ClearBuffers(bool bColor, bool bDepth,bool bStencil);
	void EndRendering();

///////////////////////////////////       摄像机         ////////////////////////////

	void CalculateProjMatrix(float fov, float n,float f); //立体投影
	void CalculateOrthoMatrix(float n, float f); //正交投影

///////////////////////////////////       静态顶点缓存         ////////////////////////////
	 int CreateStaticBuffer(VertexType , PrimType ,
								   int totalVerts, int totalIndices,
								   int stride, void **data, unsigned int *indices,
								   int *staticId);  //创建静态定点缓存 staticId最后渲染的id

///////////////////////////////////       灯光 材质       ////////////////////////////

	void SetMaterial(stMaterial* mat);
	
	void SetLight(stLight* light, int index);
	void DisableLight(int index);

///////////////////////////////////          深度和透明           ////////////////////////////////////

	void SetDepthTesting(RenderState state);
	void SetTransparency(RenderState state,TransState src, TransState dst);

///////////////////////////////////       纹理         ////////////////////////////

	int AddTexture2D(char *file, int *texId);
	void SetTextureFilter(int index, int filter, int val);
	void SetMultiTexture();
	void ApplyTexture(int index, int texId);
	void SaveScreenShot(char *file);
	
	void SetDetailMapping();
	void EnablePointSprites(float size, float min, float a, float b, float c);
	void DisablePointSprites();

/////////////////////////////////////// 字体 ///////////////////////////////////////////////
	
	bool CreateText(char *font, int weight, bool italic,int size, int &id);
	
	void DisplayText(int id, long x, long y,int r, int g, int b,char *text, ...);//...可变参数
	
	void DisplayText(int id, long x, long y,unsigned long color,char *text, ...);

////////////////////////////////      GUI      ////////////////////////////////////////////////

	bool AddGUIBackdrop(int guiId,char *fileName);
	
	bool AddGUIStaticText(int guiId, int id,char *text, int x, int y, unsigned long color,int fontID);
	
	bool AddGUIButton(int guiId, int id, int x,int y, char *up, char *over, char *down);
	
	void ProcessGUI(int guiId, bool LMBDown,int mouseX, int mouseY,void(*funcPtr)(int id, int state));

//////////////////////////////////采样 雾 粒子///////////////////////////////////////////////

	void EnableFog(float start,float end,UGP_FOG_TYPE type,unsigned long color,bool rangeFog);
	void DisableFog();

/////////////////////////////           模型                ///////////////////////////

	
	int LoadUMFAsStaticBuffer(char *file, int meshIndex,int *staticID);
	int LoadUMFAsStaticBuffer(char *file, int meshIndex,int staticID);
	int LoadOBJAsStaticBuffer(char *file,int *staticID);
	int LoadOBJAsStaticBuffer(char *file,int staticID);
	int LoadXModel(char *file, int *xModelId);
	int LoadXModel(char *file, int xModelId);
	
	void ReleaseAllStaticBuffers();
	void ReleaseAllXModels();
	int ReleaseStaticBuffer(int staticID);
	int ReleaseXModel(int xModelId);
	
///////////////////////////////////       渲染         ////////////////////////////
	
	 int RenderStaticBuffer(int staticId); //将缓存内容显示在屏幕上
	 int RenderXModel(int xModelId);
private:

	void oneTimeInit();

private: //保护类型 代表这些变量可以是派生类的成员变量
	     
	D3DCOLOR m_Color; //清除色 SetClearCol
	LPDIRECT3D9  m_Direct3D;  //定义direct3D接口对象（COM指针)
	LPDIRECT3DDEVICE9 m_Device;  //
	bool m_renderingScene; //是否是当前场景
	
	stD3DStaticBuffer* m_staticBufferList;//静态缓存数组 (渲染静态模型)
	int m_numStaticBuffers; //静态缓存大小
	int m_activeStaticBuffer; //(可以有多个静态顶点缓存) 当前正在使用的静态缓存

	stD3DTexture* m_textureList;
	unsigned int m_numTextures;

	LPD3DXFONT *m_fonts;
	//D3DXMATRIX m_projection;
	CXModel* m_xModels;
	int m_numXModels;
};

bool CreateD3DRenderer(CRenderInterface **pObj);

#endif