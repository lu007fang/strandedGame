#include "main.h"



LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_DESTROY:
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
		break;

	}

	return DefWindowProc(hWnd,msg,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hpreInstance,LPSTR lpCmdLine,int nShowCmd)
{
	WNDCLASSEX wc = {sizeof(WNDCLASSEX),
					 CS_CLASSDC,MsgProc,0,0,GetModuleHandle(NULL),
					 NULL,NULL,NULL,NULL,window_name,NULL};

	RegisterClassEx(&wc);

	if(FULLSCREEN)
	{
		g_hwnd = CreateWindowEx(NULL,window_name,window_title,
							  WS_POPUP|WS_SYSMENU|WS_VISIBLE,0,0,
							  window_width,window_height,
							  NULL,NULL,hInst,NULL);
	}
	else
	{
		g_hwnd = CreateWindowEx(NULL,window_name,window_title,
							  WS_OVERLAPPEDWINDOW|WS_VISIBLE,0,0,
							  window_width,window_height,
							  NULL,NULL,hInst,NULL);
	}

	if(g_hwnd)
	{
		ShowWindow(g_hwnd,SW_SHOWDEFAULT);
		UpdateWindow(g_hwnd);
	}

	g_hInstance = wc.hInstance;

	InitializeEngine();
	
	GameInitialize();
		
		
	MSG msg;

	ZeroMemory(&msg,sizeof(msg));
	SetCursorPos(0,0);
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg,NULL,0U,0U,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			GameLoop();
		}
	}
	
	

	GameShutdown();
	ShutdownEngine();

	UnregisterClass(window_name,wc.hInstance);

	return 0;
}

bool InitializeEngine()
{
	if(!CreateD3DRenderer(&g_Render))
		return false;

	if(!g_Render->Initialize(window_width,window_height,g_hwnd,FULLSCREEN,UGP_MS_SAMPLES_4))
		return false;

	g_Render->SetClearCol(0,0,0);

	if(!g_Render->CreateText("Arial", 0, true, 18, g_arialID))
		return false;

	if(!CreateDIInput(&g_InputSystem,g_hwnd,g_hInstance,false))
		return false;

	if(!g_InputSystem->Initialize());
		return false;

	return true;
}

void ShutdownEngine()
{
	if(g_Render)
	{
		g_Render->Shutdown();
		delete g_Render;
		g_Render = NULL;
	}

	if(g_InputSystem)
	{
		g_InputSystem->Shutdown();
		delete g_InputSystem;
		g_InputSystem = NULL;
	}
}

bool GameInitialize()
{
	if(!InitializeMainMenu()) 
		return false;

	return true;
}

void GameLoop()
{
	ProcessInput();

	if(g_gameState == GS_LEVEL)
		LevelRender();
	else if(g_gameState == GS_MENU)
		MainMenuRender();
	else if(g_gameState == GS_LEVEL_1_SWITCH)
	{
		GameReleaseAll();

		if(LoadLevel("maps/level1/level1.lvl"))
			g_gameState = GS_LEVEL;
		else
			g_gameState = GS_MENU;
	}
}

void GameShutdown()
{
	GameReleaseAll();
}

bool InitializeMainMenu()//作用：将GUI主菜单加载到内存中
{
	if(!g_Render->CreateGUI(g_mainGui)) return false;
   if(!g_Render->CreateGUI(g_startGui)) return false;
   if(!g_Render->CreateGUI(g_creditsGui)) return false;
  // if(!g_Render->CreateGUI(g_loadingGui)) return false;

   ///// Load backdrops. 读取背景文件///////////

   if(!g_Render->AddGUIBackdrop(g_mainGui, "menu/mainMenu.jpg"))
      return false;
   if(!g_Render->AddGUIBackdrop(g_startGui, "menu/startMenu.jpg"))
      return false;
   if(!g_Render->AddGUIBackdrop(g_creditsGui,"menu/creditsMenu.jpg")) 
	   return false;
//if(!g_Render->AddGUIBackdrop(g_loadingGui,"menu/loadingMenu.jpg")) 
//   return false;
  
    ///////////////////// Set main screen elements.//////////////////////////

      if(!g_Render->AddGUIStaticText(g_mainGui, STATIC_TEXT_ID,
        "Version: 1.0", PERCENT_OF(window_width, 0.85),
        PERCENT_OF(window_width, 0.05),
        UGPCOLOR_ARGB(255,255,255,255), g_arialID)) return false;
     
   if(!g_Render->AddGUIButton(g_mainGui, BUTTON_START_ID,
        PERCENT_OF(window_width, 0.05), PERCENT_OF(window_height, 0.40),
        "menu/startUp.png", "menu/StartOver.png",
        "menu/startDown.png")) return false; 
    
     if(!g_Render->AddGUIButton(g_mainGui, BUTTON_CREDITS_ID,
      PERCENT_OF(window_width, 0.05), PERCENT_OF(window_height, 0.50),
      "menu/creditsUp.png", "menu/creditsOver.png",
      "menu/creditsDown.png")) return false;
  
     if(!g_Render->AddGUIButton(g_mainGui, BUTTON_QUIT_ID,
      PERCENT_OF(window_width, 0.05), PERCENT_OF(window_height, 0.60),
      "menu/quitUp.png", "menu/quitOver.png",
      "menu/quitDown.png")) return false;
  

   //////////////////////// Set start screen elements./////////////////////////////////
   if(!g_Render->AddGUIButton(g_startGui, BUTTON_LEVEL_1_ID,
      PERCENT_OF(window_width, 0.1), PERCENT_OF(window_height, 0.15),
      "menu/level1Up.png", "menu/level1Over.png",
      "menu/level1Down.png")) return false;
  
   if(!g_Render->AddGUIButton(g_startGui, BUTTON_BACK_ID,
      PERCENT_OF(window_width, 0.1), PERCENT_OF(window_height, 0.80),
      "menu/backUp.png", "menu/backOver.png",
      "menu/backDown.png")) return false;
  
  //
  // // Set credits screen elements.
  // if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
  //    "Game Design -",
  //    PERCENT_OF(window_wight, 0.1), PERCENT_OF(window_height, 0.15),
  //    UGPCOLOR_ARGB(255,255,255,255),
  //    g_arialID)) return false;
  //
  // if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
  //    "              Allen Sherrod",
  //    PERCENT_OF(window_wight, 0.1), PERCENT_OF(window_height, 0.20),
  //    UGPCOLOR_ARGB(255,255,255,255),
  //    g_arialID)) return false;
  //
  // if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
  //    "Programming -",
  //    PERCENT_OF(window_wight, 0.1), PERCENT_OF(window_height, 0.25),
  //    UGPCOLOR_ARGB(255,255,255,255),
  //    g_arialID)) return false;
  //
  // if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
  //    "              Allen Sherrod",
  //    PERCENT_OF(window_wight, 0.1), PERCENT_OF(window_height, 0.30),
  //    UGPCOLOR_ARGB(255,255,255,255),
  //    g_arialID)) return false;
  //
  // if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
  //    "Sound -",
  //    PERCENT_OF(window_wight, 0.1), PERCENT_OF(window_height, 0.35),
  //    UGPCOLOR_ARGB(255,255,255,255),
  //    g_arialID)) return false;
  //
  // if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
  //    "              Allen Sherrod",
  //    PERCENT_OF(window_wight, 0.1), PERCENT_OF(window_height, 0.40),
  //    UGPCOLOR_ARGB(255,255,255,255),
  //    g_arialID)) return false;
  //
  // if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
  //    "Level Design -",
  //    PERCENT_OF(window_wight, 0.1), PERCENT_OF(window_height, 0.45),
  //    UGPCOLOR_ARGB(255,255,255,255),
  //    g_arialID)) return false;
  //
  // if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
  //    "              Allen Sherrod",
  //    PERCENT_OF(window_wight, 0.1), PERCENT_OF(window_height, 0.50),
  //    UGPCOLOR_ARGB(255,255,255,255),
  //    g_arialID)) return false;
  //
  // if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
  //    "Speical Thanks -",
  //    PERCENT_OF(window_wight, 0.1), PERCENT_OF(window_height, 0.55),
  //    UGPCOLOR_ARGB(255,255,255,255),
  //    g_arialID)) return false;
  //
  // if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
  //    "              Jenifer Niles",
  //    PERCENT_OF(window_wight, 0.1), PERCENT_OF(window_height, 0.60),
  //    UGPCOLOR_ARGB(255,255,255,255),
  //    g_arialID)) return false;
  //
  // if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
  //    "              Bryan Davidson",
  //    PERCENT_OF(window_wight, 0.1), PERCENT_OF(window_height, 0.65),
  //    UGPCOLOR_ARGB(255,255,255,255),
  //    g_arialID)) return false;
  //
  // if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
  //    "              Charles River Media",
  //    PERCENT_OF(window_wight, 0.1), PERCENT_OF(window_height, 0.70),
  //    UGPCOLOR_ARGB(255,255,255,255),
  //    g_arialID)) return false;
  //
  // if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
  //    "              Readers of this book",
  //    PERCENT_OF(window_wight, 0.1), PERCENT_OF(window_height, 0.75),
  //    UGPCOLOR_ARGB(255,255,255,255),
  //    g_arialID)) return false;
  //
  if(!g_Render->AddGUIButton(g_creditsGui, BUTTON_BACK_ID,
     PERCENT_OF(window_width, 0.1), PERCENT_OF(window_height, 0.80),
     "menu/backUp.png", "menu/backOver.png",
     "menu/backDown.png")) return false;
  
	return true;
}
void MainMenuCallback(int id, int state)//回调函数 操作系统用它来处理窗口信息
{
	switch(id)
      {
         case BUTTON_START_ID:
            if(state == UGP_BUTTON_DOWN)
               g_currentGUI = GUI_START_SCREEN;
            break;

         case BUTTON_CREDITS_ID:
            if(state == UGP_BUTTON_DOWN)
               g_currentGUI = GUI_CREDITS_SCREEN;
            break;

         case BUTTON_BACK_ID:
            if(state == UGP_BUTTON_DOWN)
               g_currentGUI = GUI_MAIN_SCREEN;
            break;

         case BUTTON_QUIT_ID:
            if(state == UGP_BUTTON_DOWN)
             
			  PostQuitMessage(0);
            break;

         case BUTTON_LEVEL_1_ID:
			if(state == UGP_BUTTON_DOWN)
				g_gameState = GS_LEVEL_1_SWITCH;
            break;
      }
}
void MainMenuRender()//作用：将主菜单绘制在窗口中
{
	if(!g_Render) return;

   g_Render->StartRender(1, 1, 0);


   
      if(g_currentGUI == GUI_MAIN_SCREEN)
      {   
		 g_Render->ProcessGUI(g_mainGui, g_LMBDown, mouseX,
                              mouseY, MainMenuCallback);  
	  }
	  else if(g_currentGUI == GUI_START_SCREEN)
	  {
         g_Render->ProcessGUI(g_startGui, g_LMBDown, mouseX,
                              mouseY, MainMenuCallback);
	  }
	  else
	  {
         g_Render->ProcessGUI(g_creditsGui, g_LMBDown, mouseX,
	                        mouseY, MainMenuCallback);
	  }
   g_Render->EndRendering();
}

void ProcessInput()
{
	 if(!g_InputSystem) 
		 return;

   // Updatea all devices.
   g_InputSystem->UpdateDevices();


   // Keyboard Input.
   if(g_InputSystem->KeyUp(DIK_ESCAPE))
      {
		  if(g_gameState == GS_MENU)
		  {
			switch(g_currentGUI)
			   {
			      case GUI_MAIN_SCREEN:
			         PostQuitMessage(0);
			         break;

			      default:
			         g_currentGUI = GUI_MAIN_SCREEN;
			   }
		  }
		  else if(g_gameState == GS_LEVEL)
		  {
			  GameReleaseAll();

			  InitializeMainMenu();
			  g_gameState = GS_MENU;
			  g_currentGUI = GUI_MAIN_SCREEN;
		  }
      }


   // Mouse Input
   POINT pos = { 0, 0 };
   GetCursorPos(&pos);

   mouseX = pos.x;
   mouseY = pos.y;

   if(g_InputSystem->MouseButtonDown(UGP_LEFT_BUTTON))
      g_LMBDown = true;
   if(!g_InputSystem->MouseButtonDown(UGP_LEFT_BUTTON))
      g_LMBDown = false;
}

void GameReleaseAll()
{
	if(!g_Render)
		return;

	g_Render->ReleaseAllStaticBuffers();
	g_Render->ReleaseAllXModels();
	g_Render->ReleaseAllGUIs();

	g_gameWorld.m_levelID = -1;
	g_gameWorld.m_skyBoxID = -1;

	g_mainGui = -1;
	g_startGui = -1;
	g_creditsGui = -1;
	g_currentGUI = GUI_MAIN_SCREEN;

}

bool LoadLevel(char* file)
{
	if(!g_Render || !file) 
		return false;

   CCommandScript script;
   char command[MAX_COMMAND_SIZE];
   char param[MAX_PARAM_SIZE];


   if(!script.LoadScriptFile(file))
      return false;


   for(int i = 0; i < script.GetTotalLines(); i++)
      {
         script.ParseCommand(command);

         if(stricmp(command, "LoadSkyBoxAsX") == 0) { }
         else if(stricmp(command, "LoadTerrainAsX") == 0) { }
         else if(stricmp(command, "LoadStaticModelAsX") == 0) { }
         else if(stricmp(command, "LoadAnimatedModelAsX") == 0) { }
         else if(stricmp(command, "#") == 0) { }
         else
            {
               char err[64];

               sprintf(err, "Error loading level on %d.",
                       script.GetCurrentLineNum() + 1);

               // TODO: Write to error log.
               script.Shutdown();
               return false;
            }

         script.MoveToNextLine();
      }

   script.MoveToStart();

   for(int i = 0; i < script.GetTotalLines(); i++)
      {
         script.ParseCommand(command);

         if(stricmp(command, "LoadSkyBoxAsX") == 0)
            {
               script.ParseStringParam(param);
               
               if(g_gameWorld.m_skyBoxID == -1)
                  {
                     if(!g_Render->LoadXModel(param, &g_gameWorld.m_skyBoxID))
                        return false;
                  }
               else
                  {
                     if(!g_Render->LoadXModel(param, g_gameWorld.m_skyBoxID))
                        return false;
                  }
            }
         else if(stricmp(command, "LoadTerrainAsX") == 0)
            {
               script.ParseStringParam(param);
               
               if(g_gameWorld.m_levelID == -1)
                  {
                     if(!g_Render->LoadXModel(param, &g_gameWorld.m_levelID))
                        return false;
                  }
               else
                  {
                     if(!g_Render->LoadXModel(param, g_gameWorld.m_levelID))
                        return false;
                  }
            }
         else if(stricmp(command, "LoadStaticModelAsX") == 0) { }
         else if(stricmp(command, "LoadAnimatedModelAsX") == 0) { }
         else if(stricmp(command, "#") == 0) { }

         script.MoveToNextLine();
      }

   script.Shutdown();

   return true;

}
void LevelRender()
{
	 if(!g_Render || g_gameState != GS_LEVEL) return;

   g_Render->StartRender(1, 1, 0);

      g_Render->RenderXModel(g_gameWorld.m_skyBoxID);
      g_Render->RenderXModel(g_gameWorld.m_levelID);

   g_Render->EndRendering();

}