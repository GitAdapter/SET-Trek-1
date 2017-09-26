#pragma once
/*
* FILENAME: GameController.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class GameController
*/
#include "GameLevel.h"
#include "Graphics.h"

//This will be a Singleton class (constructor is private)
class GameController
{
	GameController() {}
	static GameLevel* currentLevel;
	//static Gameboard* gameBoard;
public:
	//GameController();
	static bool Loading;
	static void Init();
	static void LoadInitialLevel(GameLevel* lev);
	static void SwitchLevel(GameLevel* lev);
	static void Render();
	static bool Update(double xCoordinate, double yCoordinate, HWND windowHandle);
};