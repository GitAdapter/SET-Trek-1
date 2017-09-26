/*
* FILENAME: GameController.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class GameController
*/
#include "GameController.h"

GameLevel* GameController::currentLevel;
bool GameController::Loading;

//
// METHOD:Init
// DESCRIPTION: initialize variables
// PARAMETERS: na
// RETURNS: na
//
void GameController::Init()
{
	Loading = true;
	currentLevel = 0;
}

//
// METHOD:LoadInitialLevel
// DESCRIPTION: Load the currentl level
// PARAMETERS:(GameLevel* lev
// RETURNS:na
//
void GameController::LoadInitialLevel(GameLevel* lev)
{
	Loading = true; //This can help us avoid loading activity while rendering
	currentLevel = lev;
	currentLevel->Load();
	Loading = false;
}

//
// METHOD:SwitchLevel
// DESCRIPTION: switches the level
// PARAMETERS: GameLevel* lev
// RETURNS: void
//
void GameController::SwitchLevel(GameLevel* lev)
{
	Loading = true;
	currentLevel->Unload();
	lev->Load();
	delete currentLevel;
	currentLevel = lev;
	Loading = false;
}

//
// METHOD:Render
// DESCRIPTION: doesn't render while loading
// PARAMETERS:na
// RETURNS:void
//
void GameController::Render()
{

	if (Loading)
	{
		return;
	}
	else
	{
		currentLevel->Render();
	}//nice! Do not update or render if the scene is loading.
}

//
// METHOD:Update
// DESCRIPTION: passes along mouse click coordinates and a window handle to Level one
// PARAMETERS:double xCoordinate, double yCoordinate, HWND windowHandle
// RETURNS: void
//
bool GameController::Update(double xCoordinate, double yCoordinate, HWND windowHandle)
{
	bool endGame = false;
	if (Loading)
	{

	}
	else
	{
		endGame = currentLevel->Update(xCoordinate, yCoordinate, windowHandle);
	}
	return endGame;
}