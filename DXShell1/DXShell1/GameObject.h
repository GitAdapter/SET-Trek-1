
/*
* FILENAME: GameObject.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class Gameobject
*/
#pragma once

#include "Graphics.h"
#include "GameLevel.h"
#include "Vector.h"
#include <string.h>
#include <string>
#include <cstring>

using namespace std;

//
//	Class: Gameobject
//  Description: This class as an abstract representation of a gameobject.
//				 although gameobjects are not rendered or stored into it, acts
//				 as a way to map gameobjects out onto the ClientWindow
//
class GameObject
{
protected:
	static Graphics* gfx;

public:


	static Graphics* GetGFX()
	{
		return gfx;
	}

	static void Init(Graphics* graphics)
	{
		gfx = graphics;
	}

	virtual void Load() = 0;
	virtual void Load(int flag) = 0;
	virtual void Unload() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};