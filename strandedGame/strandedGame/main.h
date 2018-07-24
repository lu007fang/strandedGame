#pragma once
#ifndef _UGP_MAIN_H_
#define _UGP_MAIN_H_

#include "../gameEngine/engine.h"

#pragma comment(lib,"../Release/gameEngine.lib")

#define window_width 800
#define window_height 600
#define window_name "forTheDream" 
#define window_title "stranded"
#define FULLSCREEN 0


// Main menu defines.
#define GUI_MAIN_SCREEN       1
#define GUI_START_SCREEN      2
#define GUI_CREDITS_SCREEN    3


// ids for our GUI controls.
#define STATIC_TEXT_ID     1
#define BUTTON_START_ID    2
#define BUTTON_CREDITS_ID  3
#define BUTTON_QUIT_ID     4
#define BUTTON_BACK_ID     5
#define BUTTON_LEVEL_1_ID  6

struct stGameWorld
{
	stGameWorld():m_levelID(-1),m_skyBoxID(-1){}

	int m_levelID;
	int m_skyBoxID;
};

enum GAME_STATE{ GS_MENU = 1,GS_LEVEL,GS_LEVEL_1_SWITCH};
bool InitializeEngine();
void ShutdownEngine();

bool GameInitialize();
void GameLoop();
void GameShutdown();

bool InitializeMainMenu();//作用：将GUI主菜单加载到内存中
void MainMenuCallback(int id, int state);//回调函数 操作系统用它来处理窗口信息
void MainMenuRender();//作用：将主菜单绘制在窗口中

void ProcessInput();

void GameReleaseAll();

bool LoadLevel(char* file);
void LevelRender();


HWND g_hwnd;
HINSTANCE g_hInstance;
CRenderInterface* g_Render = NULL;
CInputInterface* g_InputSystem = NULL;

int g_mainGui = -1;
int g_startGui = -1;
int g_creditsGui = -1;

int g_currentGUI = GUI_MAIN_SCREEN;

int g_arialID = -1;

bool g_LMBDown = false;
int mouseX = 0;
int mouseY = 0;

stGameWorld g_gameWorld;
GAME_STATE g_gameState = GS_MENU;

#endif