/*
* FILENAME: Graphics.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class Graphicss
*/
#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d2d1_1.h>
#include <d2d1_1helper.h>
#include <d3d11_1.h>
#include <d2d1effects_2.h>
#include <d2d1effecthelpers.h>
//
//	Class: Grapics
//  Description: This class as an abstract representation of a Graphics engine.
//				 it hold all necessary factors to render 2D and 3D objects for the SET Trek program
//
class Graphics
{
	//Below, these are all COM interfaces we're using to create D2D resources.
	//We release them as part of the ~Graphics deconstructor... or bad things can happen
	ID2D1Factory1* factory; //The factory allows us to create many other types of D2D resources

	// Direct3D device
	ID3D11Device1 *Direct3DDevice;
	// Direct3D device context
	ID3D11DeviceContext1 *Direct3DContext;
	// Direct2D device
	ID2D1Device *Direct2DDevice;
	// DXGI swap chain
	IDXGISwapChain1 *DXGISwapChain;
	// Direct2D target rendering bitmap
	// (linked to DXGI back buffer which is linked to Direct3D pipeline)
	ID2D1Bitmap1 *Direct2DBackBuffer;

	// The render target device context
	ID2D1DeviceContext *Screen;


	ID2D1HwndRenderTarget* rendertarget; //this is typically an area in our GPU memory.. like a back buffer 
	ID2D1SolidColorBrush* brush; //Note this COM interface! Remember to release it!
	//ID3D11Device* device;
	//ID3D11DeviceContext* context;

	//ID2D1Device* deviceBro;
	//ID2D1DeviceContext* broooooo;
	//ID2D1Effect* FXbrooooooo;

	//UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	//D3D_FEATURE_LEVEL featureLevels[]{
	//	D3D_FEATURE_LEVEL_11_1,
	//	D3D_FEATURE_LEVEL_11_0,
	//	D3D_FEATURE_LEVEL_10_1,
	//	D3D_FEATURE_LEVEL_10_0,
	//	D3D_FEATURE_LEVEL_9_3,
	//	D3D_FEATURE_LEVEL_9_2,
	//	D3D_FEATURE_LEVEL_9_1
	//};

	
public:
	Graphics();

	~Graphics();

	bool Init(HWND windowHandle);

	/*ID2D1RenderTarget* GetRenderTarget()
	{
		return rendertarget;
	}*/

	void BeginDraw(){ Screen->BeginDraw(); }
	void EndDraw(){ Screen->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	
	// Hrmmm... r, g, b, a? Where do we know these from?

	IDXGISwapChain1* GetSwapChain();

	ID2D1DeviceContext* GetDeviceContext();

	ID2D1Bitmap1* GetBitMap();

};
