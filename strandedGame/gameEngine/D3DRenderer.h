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

struct stD3DStaticBuffer //��̬���㻺��ṹ��
{
	stD3DStaticBuffer() : vbPtr(0), 
		                  ibPtr(0), 
		                  numVerts(0), 
                          numIndices(0),
		                  stride(0),
		                  fvf(0), 
                          primType(NULL_TYPE) {} 

   LPDIRECT3DVERTEXBUFFER9 vbPtr;  //���㻺��
   LPDIRECT3DINDEXBUFFER9 ibPtr;  //��������
   int numVerts;  //����ļ���
   int numIndices;  //�����ļ���
   int stride;   //��������ߴ����
   unsigned long fvf; //����FVF
   PrimType primType;  //��̬�����ͼԪ����
};

struct stD3DTexture //��ͼ���� 
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
	      
	//���ó�Ա������ʼֵ
	CD3DRenderer();
	~CD3DRenderer();

///////////////////////////////////       engine��ʼ��         ////////////////////////////

	bool Initialize(int w, int h, WinHWND mainWin, bool fullScreen,UGP_MS_TYPE ms);
	
	void Shutdown(); //�����Ⱦϵͳ
	void SetClearCol(float r, float g, float b);

///////////////////////////////////       ��Ⱦ����         ////////////////////////////

	void StartRender(bool bColor, bool bDepth,bool bStencil);
	void ClearBuffers(bool bColor, bool bDepth,bool bStencil);
	void EndRendering();

///////////////////////////////////       �����         ////////////////////////////

	void CalculateProjMatrix(float fov, float n,float f); //����ͶӰ
	void CalculateOrthoMatrix(float n, float f); //����ͶӰ

///////////////////////////////////       ��̬���㻺��         ////////////////////////////
	 int CreateStaticBuffer(VertexType , PrimType ,
								   int totalVerts, int totalIndices,
								   int stride, void **data, unsigned int *indices,
								   int *staticId);  //������̬���㻺�� staticId�����Ⱦ��id

///////////////////////////////////       �ƹ� ����       ////////////////////////////

	void SetMaterial(stMaterial* mat);
	
	void SetLight(stLight* light, int index);
	void DisableLight(int index);

///////////////////////////////////          ��Ⱥ�͸��           ////////////////////////////////////

	void SetDepthTesting(RenderState state);
	void SetTransparency(RenderState state,TransState src, TransState dst);

///////////////////////////////////       ����         ////////////////////////////

	int AddTexture2D(char *file, int *texId);
	void SetTextureFilter(int index, int filter, int val);
	void SetMultiTexture();
	void ApplyTexture(int index, int texId);
	void SaveScreenShot(char *file);
	
	void SetDetailMapping();
	void EnablePointSprites(float size, float min, float a, float b, float c);
	void DisablePointSprites();

/////////////////////////////////////// ���� ///////////////////////////////////////////////
	
	bool CreateText(char *font, int weight, bool italic,int size, int &id);
	
	void DisplayText(int id, long x, long y,int r, int g, int b,char *text, ...);//...�ɱ����
	
	void DisplayText(int id, long x, long y,unsigned long color,char *text, ...);

////////////////////////////////      GUI      ////////////////////////////////////////////////

	bool AddGUIBackdrop(int guiId,char *fileName);
	
	bool AddGUIStaticText(int guiId, int id,char *text, int x, int y, unsigned long color,int fontID);
	
	bool AddGUIButton(int guiId, int id, int x,int y, char *up, char *over, char *down);
	
	void ProcessGUI(int guiId, bool LMBDown,int mouseX, int mouseY,void(*funcPtr)(int id, int state));

//////////////////////////////////���� �� ����///////////////////////////////////////////////

	void EnableFog(float start,float end,UGP_FOG_TYPE type,unsigned long color,bool rangeFog);
	void DisableFog();

/////////////////////////////           ģ��                ///////////////////////////

	
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
	
///////////////////////////////////       ��Ⱦ         ////////////////////////////
	
	 int RenderStaticBuffer(int staticId); //������������ʾ����Ļ��
	 int RenderXModel(int xModelId);
private:

	void oneTimeInit();

private: //�������� ������Щ����������������ĳ�Ա����
	     
	D3DCOLOR m_Color; //���ɫ SetClearCol
	LPDIRECT3D9  m_Direct3D;  //����direct3D�ӿڶ���COMָ��)
	LPDIRECT3DDEVICE9 m_Device;  //
	bool m_renderingScene; //�Ƿ��ǵ�ǰ����
	
	stD3DStaticBuffer* m_staticBufferList;//��̬�������� (��Ⱦ��̬ģ��)
	int m_numStaticBuffers; //��̬�����С
	int m_activeStaticBuffer; //(�����ж����̬���㻺��) ��ǰ����ʹ�õľ�̬����

	stD3DTexture* m_textureList;
	unsigned int m_numTextures;

	LPD3DXFONT *m_fonts;
	//D3DXMATRIX m_projection;
	CXModel* m_xModels;
	int m_numXModels;
};

bool CreateD3DRenderer(CRenderInterface **pObj);

#endif