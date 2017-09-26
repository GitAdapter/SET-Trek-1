
/*
* FILENAME: Planet.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class Planet
*/
#include "Planet.h"

Planet::Planet() {}

//
// METHOD:Planet
// DESCRIPTION: Constructor
// PARAMETERS:string whichBitmap, Graphics* gfx
// RETURNS: na
//
Planet::Planet(string whichBitmap, Graphics* gfx)
{
	string bitmapBuffer = whichBitmap;
	wstring bitmapName(bitmapBuffer.begin(), bitmapBuffer.end());
	this->bitmapName = bitmapName;
	this->gfx = gfx;
	Load();
}

//
// METHOD~Planet
// DESCRIPTION: destructor
// PARAMETERS: na
// RETURNS: na
//
Planet::~Planet()
{
}

//
// METHOD:Load
// DESCRIPTION: load spritesheet
// PARAMETERS: na
// RETURNS:void
//
void Planet::Load()
{
	sprites = new SpriteSheet((wchar_t*)bitmapName.c_str(), gfx);
}


//
// METHOD:Load
// DESCRIPTION: na
// PARAMETERS: na
// RETURNS: na
//
void Planet::Load(int flag)
{

}

//
// METHOD:Unload
// DESCRIPTION: na
// PARAMETERS: na
// RETURNS: na
//
void Planet::Unload()
{
}


//
// METHOD:Update
// DESCRIPTION: na
// PARAMETERS: na
// RETURNS: na
//
void Planet::Update()
{
	
}

//
// METHOD:Render
// DESCRIPTION: na
// PARAMETERS: na
// RETURNS: na
//
void Planet::Render()
{

}

//
//	METHOD: Render()
//	DESCRIPTION: this method passes coordinates onto a Draw() overload
//	PARAMETERS: float xOneCoordinate, 
//				float yOneCoordinate,
//			    float xTwoCoordinate,
//				float yTwoCoordinate
//	RETURNS void
//
void Planet::Render(float xOneCoordinate, float yOneCoordinate, float xTwoCoordinate, float yTwoCoordinate) {

	sprites->Draw(xOneCoordinate, yOneCoordinate, xTwoCoordinate, yTwoCoordinate);
}