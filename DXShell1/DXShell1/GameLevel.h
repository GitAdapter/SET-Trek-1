/*
* FILENAME: GameLevel.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class Gamelevel
*/
#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"

//
//	Class: GameLevel
//  Description: This class as an abstract representation of a gameleve.
//				 although gamelevels are not rendered or stored into it, acts
//				 as a way to map a gamelevel out onto the ClientWindow
//
class GameLevel
{
protected:
	static Graphics* gfx;

public:
	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual bool Update(double xCoordinate, double yCoordinate, HWND windowHandle) = 0;
	virtual void Render() = 0;
};