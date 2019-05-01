#define USE_GLFW 1
#ifdef USE_GLFW
	#include "EngineCore.h"
#endif

#include "BellfruitGame.h"
#include "WindowSettings.h"



int main(int argc, char* argv[])
{
	//IEngineCore* engineCore;

#ifdef USE_GLFW
	EngineCore* engineCore = engineCore->Instance();
#endif

	WindowSettings& g_window = g_window.getInstance();

	if (!engineCore->initWindow(g_window.getScreenWidth(), g_window.getScreenHeight(),  "Double-click this bar for fullscreen"))
		return -1;

	BellfruitGame* myFirstGame = new BellfruitGame();

	engineCore->runEngine(myFirstGame);

	return 0;
	
}