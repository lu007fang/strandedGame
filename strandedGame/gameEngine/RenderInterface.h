#pragma once
#ifndef _UGP_RENDERINTERFACE_H_
#define _UGP_RENDERINTERFACE_H_

#include "defines.h"
#include "light.h"
#include "material.h"
#include "GUI.h"
#include "structs.h"
#include "UMFLoader.h"
#include "OBJLoader.h"


class CRenderInterface 
{
	public:
	     
	//设置成员变量初始值
	CRenderInterface() : m_screenWidth(0),
						 m_screenHeight(0), 
						 m_near(0), 
						 m_far(0) { }
	
	virtual ~CRenderInterface() {}

///////////////////////////////////       engine初始化         ////////////////////////////

	virtual bool Initialize(int w, int h, WinHWND mainWin, bool fullScreen,UGP_MS_TYPE ms) = 0;
	virtual void Shutdown() = 0; //清楚渲染系统
	virtual void oneTimeInit() = 0;  
	virtual void SetClearCol(float r, float g, float b) = 0;

///////////////////////////////////       渲染场景         ////////////////////////////

	virtual void StartRender(bool bColor, bool bDepth,bool bStencil) = 0;
	virtual void ClearBuffers(bool bColor, bool bDepth,bool bStencil) = 0;
	virtual void EndRendering() = 0;

///////////////////////////////////       摄像机         ////////////////////////////

	virtual void CalculateProjMatrix(float fov, float n,float f) = 0; //立体投影
	virtual void CalculateOrthoMatrix(float n, float f) = 0; //正交投影

///////////////////////////////////       静态顶点缓存         ////////////////////////////
	virtual int CreateStaticBuffer(VertexType , PrimType ,
								   int totalVerts, int totalIndices,
								   int stride, void **data, unsigned int *indices,
								   int *staticId) = 0;  //创建静态定点缓存 staticId最后渲染的id

///////////////////////////////////       灯光 材质       ////////////////////////////

	virtual void SetMaterial(stMaterial* mat) = 0;

	virtual void SetLight(stLight* light, int index) = 0;
	virtual void DisableLight(int index) = 0;

///////////////////////////////////          深度和透明           ////////////////////////////////////

	virtual void SetDepthTesting(RenderState state) = 0;
	virtual void SetTransparency(RenderState state,TransState src, TransState dst) = 0;

///////////////////////////////////       纹理         ////////////////////////////

	virtual int AddTexture2D(char *file, int *texId) = 0;
	virtual void SetTextureFilter(int index, int filter, int val) = 0;
	virtual void SetMultiTexture() = 0;
	virtual void ApplyTexture(int index, int texId) = 0;
	virtual void SaveScreenShot(char *file) = 0;
	
	virtual void SetDetailMapping() = 0;
	virtual void EnablePointSprites(float size, float min, float a, float b, float c) = 0;
	virtual void DisablePointSprites() = 0;

/////////////////////////////////////// 字体 ///////////////////////////////////////////////
	
	virtual bool CreateText(char *font, int weight, bool italic,
	                           int size, int &id) = 0;
	   
	virtual void DisplayText(int id, long x, long y,
	                            int r, int g, int b,
	                            char *text, ...) = 0;//...可变参数
	   
	virtual void DisplayText(int id, long x, long y,
                                unsigned long color,
                                char *text, ...) = 0;

////////////////////////////////      GUI      ////////////////////////////////////////////////
      
	 // If porting to OpenGL would probably stay the same.
	
      bool CreateGUI(int &id) //添加新GUI对象和ID id：-1 mainGUI
    {
       if(!m_guiList)
       {
          m_guiList = new CGUISystem[1];
          if(!m_guiList) return UGP_FAIL;
       }
       else
       {
          CGUISystem *temp;   
          temp = new CGUISystem[m_totalGUIs + 1];
	
          memcpy(temp, m_guiList,
                sizeof(CGUISystem) * m_totalGUIs);
	
          delete[] m_guiList;
          m_guiList = temp;
       }
	
       id = m_totalGUIs;  
       m_totalGUIs++;
	
       return true;
    }

	  void ReleaseAllGUIs()
      {
         for(int s = 0; s < m_totalGUIs; s++)
            {
               m_guiList[s].Shutdown();
            }

         m_totalGUIs = 0;
         if(m_guiList) delete[] m_guiList;
         m_guiList = NULL;
      }


	
	virtual bool AddGUIBackdrop(int guiId,char *fileName) = 0;
	
	virtual bool AddGUIStaticText(int guiId, int id,
					char *text, int x, int y, unsigned long color,
					int fontID) = 0;
	
	virtual bool AddGUIButton(int guiId, int id, int x,
			    int y, char *up, char *over, char *down) = 0;
	
	virtual void ProcessGUI(int guiId, bool LMBDown,
							  int mouseX, int mouseY,
							  void(*funcPtr)(int id, int state)) = 0;

//////////////////////////////////采样 雾 粒子///////////////////////////////////////////////

	virtual void EnableFog(float start,float end,UGP_FOG_TYPE type,unsigned long color,bool rangeFog) = 0;
	virtual void DisableFog() = 0;

/////////////////////////////           模型                ///////////////////////////

	
	virtual int LoadUMFAsStaticBuffer(char *file, int meshIndex,int *staticID) = 0;
	virtual int LoadUMFAsStaticBuffer(char *file, int meshIndex,int staticID) = 0;
	virtual int LoadOBJAsStaticBuffer(char *file,int *staticID) = 0;
	virtual int LoadOBJAsStaticBuffer(char *file,int staticID) = 0;
	virtual int LoadXModel(char *file, int *xModelId) = 0;
	virtual int LoadXModel(char *file, int xModelId) = 0;
	
	virtual void ReleaseAllStaticBuffers() = 0;
	virtual void ReleaseAllXModels() = 0;
	virtual int ReleaseStaticBuffer(int staticID) = 0;
	virtual int ReleaseXModel(int xModelId) = 0;


///////////////////////////////////       渲染         ////////////////////////////
	
	virtual int RenderStaticBuffer(int staticId) = 0; //将缓存内容显示在屏幕上
	virtual int RenderXModel(int xModelId) = 0;


	protected: //保护类型 代表这些变量可以是派生类的成员变量
	     
	   //这都是给Direct3D_Init用的
	   int m_screenWidth; //屏幕宽度
	   int m_screenHeight;//屏幕高度
	   bool m_fullscreen; //是否全屏
	   WinHWND m_mainHandle;  //窗口句柄（Direct3D初始化函数所需）
	   float m_near; //投影矩阵所需近景
	   float m_far;  //投影矩阵所需远景
	   int m_totalFonts;
	   
	   CGUISystem* m_guiList;
	   int m_totalGUIs;
};

#endif