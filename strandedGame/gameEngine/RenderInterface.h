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
	     
	//���ó�Ա������ʼֵ
	CRenderInterface() : m_screenWidth(0),
						 m_screenHeight(0), 
						 m_near(0), 
						 m_far(0) { }
	
	virtual ~CRenderInterface() {}

///////////////////////////////////       engine��ʼ��         ////////////////////////////

	virtual bool Initialize(int w, int h, WinHWND mainWin, bool fullScreen,UGP_MS_TYPE ms) = 0;
	virtual void Shutdown() = 0; //�����Ⱦϵͳ
	virtual void oneTimeInit() = 0;  
	virtual void SetClearCol(float r, float g, float b) = 0;

///////////////////////////////////       ��Ⱦ����         ////////////////////////////

	virtual void StartRender(bool bColor, bool bDepth,bool bStencil) = 0;
	virtual void ClearBuffers(bool bColor, bool bDepth,bool bStencil) = 0;
	virtual void EndRendering() = 0;

///////////////////////////////////       �����         ////////////////////////////

	virtual void CalculateProjMatrix(float fov, float n,float f) = 0; //����ͶӰ
	virtual void CalculateOrthoMatrix(float n, float f) = 0; //����ͶӰ

///////////////////////////////////       ��̬���㻺��         ////////////////////////////
	virtual int CreateStaticBuffer(VertexType , PrimType ,
								   int totalVerts, int totalIndices,
								   int stride, void **data, unsigned int *indices,
								   int *staticId) = 0;  //������̬���㻺�� staticId�����Ⱦ��id

///////////////////////////////////       �ƹ� ����       ////////////////////////////

	virtual void SetMaterial(stMaterial* mat) = 0;

	virtual void SetLight(stLight* light, int index) = 0;
	virtual void DisableLight(int index) = 0;

///////////////////////////////////          ��Ⱥ�͸��           ////////////////////////////////////

	virtual void SetDepthTesting(RenderState state) = 0;
	virtual void SetTransparency(RenderState state,TransState src, TransState dst) = 0;

///////////////////////////////////       ����         ////////////////////////////

	virtual int AddTexture2D(char *file, int *texId) = 0;
	virtual void SetTextureFilter(int index, int filter, int val) = 0;
	virtual void SetMultiTexture() = 0;
	virtual void ApplyTexture(int index, int texId) = 0;
	virtual void SaveScreenShot(char *file) = 0;
	
	virtual void SetDetailMapping() = 0;
	virtual void EnablePointSprites(float size, float min, float a, float b, float c) = 0;
	virtual void DisablePointSprites() = 0;

/////////////////////////////////////// ���� ///////////////////////////////////////////////
	
	virtual bool CreateText(char *font, int weight, bool italic,
	                           int size, int &id) = 0;
	   
	virtual void DisplayText(int id, long x, long y,
	                            int r, int g, int b,
	                            char *text, ...) = 0;//...�ɱ����
	   
	virtual void DisplayText(int id, long x, long y,
                                unsigned long color,
                                char *text, ...) = 0;

////////////////////////////////      GUI      ////////////////////////////////////////////////
      
	 // If porting to OpenGL would probably stay the same.
	
      bool CreateGUI(int &id) //�����GUI�����ID id��-1 mainGUI
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

//////////////////////////////////���� �� ����///////////////////////////////////////////////

	virtual void EnableFog(float start,float end,UGP_FOG_TYPE type,unsigned long color,bool rangeFog) = 0;
	virtual void DisableFog() = 0;

/////////////////////////////           ģ��                ///////////////////////////

	
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


///////////////////////////////////       ��Ⱦ         ////////////////////////////
	
	virtual int RenderStaticBuffer(int staticId) = 0; //������������ʾ����Ļ��
	virtual int RenderXModel(int xModelId) = 0;


	protected: //�������� ������Щ����������������ĳ�Ա����
	     
	   //�ⶼ�Ǹ�Direct3D_Init�õ�
	   int m_screenWidth; //��Ļ���
	   int m_screenHeight;//��Ļ�߶�
	   bool m_fullscreen; //�Ƿ�ȫ��
	   WinHWND m_mainHandle;  //���ھ����Direct3D��ʼ���������裩
	   float m_near; //ͶӰ�����������
	   float m_far;  //ͶӰ��������Զ��
	   int m_totalFonts;
	   
	   CGUISystem* m_guiList;
	   int m_totalGUIs;
};

#endif