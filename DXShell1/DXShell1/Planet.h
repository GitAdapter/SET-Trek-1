
/*
* FILENAME: Planet.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class Planet
*/
#pragma once

#include "GameObject.h"

//
//	Class: Planet
//  Description: This class as an abstract representation of a Planet.
//
class Planet : public GameObject
{
	SpriteSheet* sprites;
	wstring bitmapName;



public:

	Planet(string bitmapName, Graphics* gfx);
	Planet();
	~Planet();
	void Load() override;
	void Load(int flag) override;
	void Unload() override;
	void Update() override;
	void Render() override;
	void Render(float xOneCoordinate, float yOneCoordinate, float xTwoCoordinate, float yTwoCoordinate);

	SpriteSheet* getSpriteSheet() { return sprites; }
};