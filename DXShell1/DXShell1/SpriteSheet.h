
/*
* FILENAME: SpriteSheet.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class SpriteSheet
*/
#pragma once

#include <wincodec.h> //This is the WIC codec header - we need this to decode image files
#include "Graphics.h" //This includes both Windows and D2D libraries
//Remember to add "windowscodecs.lib" to your Linker/Input/AdditionalDependencies

//
//	Class: SpriteSheet
//  Description: This class as an abstract representation of a Spritesheet.
//				 it allows us to render Bitmaps and images to the ClientWindow
//
class SpriteSheet
{
	Graphics* gfx; //Reference to the Graphics class
	ID2D1Effect* chromaKey;
	ID2D1Effect* scale;
	ID2D1Bitmap1* bmp; //This will hold our loaded and converted Bitmap file
	ID2D1Effect* compositeEffect;
	ID2D1Image* EffectImage;


public:
	//Constructor
	SpriteSheet(wchar_t* filename, Graphics* gfx);

	//Destructor
	~SpriteSheet();

	//Draw bitmap to the render target
	void SpriteSheet::Draw(float firstX, float firstY, float orientation);
	void SpriteSheet::Draw(float firstX, float firstY, float secondX, float secondY);
	ID2D1Effect*  GetChromaEffect();
	void ChromaKeyEffect(float firstX, float firstY, float secondX, float secondY, int colorFlag);
	//void ChromaKeyEffect(SpriteSheet* classDetails, int firstX, int firstY, int secondX, int secondY);
	ID2D1Bitmap1*  GetCurrentBitmap();
	void Draw();
	void SpriteSheet::CompositeEffect(ID2D1Image* base, ID2D1Image* detail);


	ID2D1Effect* GetCompositeEffect();
	//void SetCurrentBitmap(ID2D1Bitmap1* newBitmap);
	//ID2D1Image* GetImage();

	void SetImage();
	ID2D1Image* GetImage();


};