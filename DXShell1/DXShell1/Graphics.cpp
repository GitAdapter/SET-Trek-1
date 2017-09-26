
/*
* FILENAME: Graphics.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains code for the class Graphicss
*/
#include "Graphics.h"

/***********************************************************************************
The intent of the Graphics class is to handle our DirectX calls, and to be largely responsible 
for managing the rendertarget.
******************************************************************************************/

//Constructor for Graphics class
Graphics::Graphics()
{
	factory = NULL;
	rendertarget = NULL;
	//brush = NULL;
}

//Destructor for Graphics class
//Note that all COM objects we instantiate should be 'released' here 
//Look for comments on COM usage in the corresponding header file.

Graphics::~Graphics()
{
	//if (context) context->Release();
	if (Direct2DBackBuffer) Direct2DBackBuffer->Release();
	if (DXGISwapChain) DXGISwapChain->Release();
	if (Screen) Screen->Release();
	if (Direct2DDevice) Direct2DDevice->Release();
	if (Direct3DContext) Direct3DContext->Release();
	if (Direct3DDevice) Direct3DDevice->Release();

	//if (brush) brush->Release();
}

//Provide some comments for each of the methods below.
//Be sure you get a sense of what is happening, and resolve any issues you have understanding these
// methods, their parameters, returns and so on.
bool Graphics::Init(HWND windowHandle)
{
	UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	D3D_FEATURE_LEVEL returnedFeatureLevel;

	D3D_FEATURE_LEVEL featureLevels[]{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	//HRESULT res = D3D11CreateDevice(
	//	NULL,	//IDXGIAdapter
	//	D3D_DRIVER_TYPE_HARDWARE, //D3D_DRIVER_TYPE
	//	0, //HMODULE
	//	creationFlags, //UNIT
	//	featureLevels, //D3D_FEATURE_LEVELS
	//	D3D11_CREATE_DEVICE_SINGLETHREADED| D3D11_CREATE_DEVICE_BGRA_SUPPORT, //UINT
	//	D3D11_SDK_VERSION, //UNIT
	//	&device, //ID3D11Device
	//	NULL, //D3D_FEATURE_LEVEL
	//	&context); //ID3D11DeviceContext
	//if (res != S_OK) return false;

	//SETUP OUR D3D1 COM OBJECTS AND CONNECT THEM D2D1
	//WE'LL NEED TO RERUN THIS CODE EVERY TIME IF WE WANT TO RESCALE
	D2D1_FACTORY_OPTIONS options;
	ZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), &options, reinterpret_cast<void **>(&factory));
	if (res != S_OK) return false;

	ID3D11Device *device;
	ID3D11DeviceContext *context;
	res = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, creationFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION,
		&device, &returnedFeatureLevel, &context);
	if (res != S_OK) return false;
	//release local com objects
	//if (context) context->Release();
	//if (device) device->Release();

	device->QueryInterface(__uuidof(ID3D11Device1), (void **)&Direct3DDevice);
	context->QueryInterface(__uuidof(ID3D11DeviceContext1), (void **)&Direct3DContext);

	IDXGIDevice *dxgiDevice;
	Direct3DDevice->QueryInterface(__uuidof(IDXGIDevice), (void **)&dxgiDevice);
	factory->CreateDevice(dxgiDevice, &Direct2DDevice);

	//release dxgiDevice
	//if (dxgiDevice) dxgiDevice->Release();

	Direct2DDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &Screen);
	//
	IDXGIAdapter *dxgiAdapter;
	dxgiDevice->GetAdapter(&dxgiAdapter);

	// Get the DXGI factory instance
	IDXGIFactory2 *dxgiFactory;
	dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };

	swapChainDesc.Width = 0;
	swapChainDesc.Height = 0;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	// Create DXGI swap chain targeting a window handle (the only Windows 7-compatible option)
	dxgiFactory->CreateSwapChainForHwnd(Direct3DDevice, windowHandle, &swapChainDesc, nullptr, nullptr, &DXGISwapChain);

	//NOT SURE IF THIS NEEDS TO BE SOMEWHERE ELSE

	// Get the back buffer as an IDXGISurface (Direct2D doesn't accept an ID3D11Texture2D directly as a render target)
	IDXGISurface *dxgiBackBuffer;
	DXGISwapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackBuffer));

	// Get screen DPI
	FLOAT dpiX, dpiY;
	factory->GetDesktopDpi(&dpiX, &dpiY);

	// Create a Direct2D surface (bitmap) linked to the Direct3D texture back buffer via the DXGI back buffer
	D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), dpiX, dpiY);

	Screen->CreateBitmapFromDxgiSurface(dxgiBackBuffer, &bitmapProperties, &Direct2DBackBuffer);
	Screen->SetTarget(Direct2DBackBuffer);

	if (dxgiBackBuffer) dxgiBackBuffer->Release();
	if (dxgiFactory) dxgiFactory->Release();
	if (dxgiAdapter) dxgiAdapter->Release();
	if (dxgiDevice) dxgiDevice->Release();
	if (context) context->Release();
	if (device) device->Release();
     //HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	//if (res != S_OK) return false;

	//RECT rect;
	//GetClientRect(windowHandle, &rect); //set the rect's right and bottom properties = the client window's size

	//res = factory->CreateHwndRenderTarget(
	//	D2D1::RenderTargetProperties(),
	//	D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
	//	&rendertarget);
	//if (res != S_OK) return false;

	//factory->
	
	/*res = rendertarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if (res != S_OK) return false;*/
	return true;
}

IDXGISwapChain1* Graphics::GetSwapChain() {

	return DXGISwapChain;
}

ID2D1DeviceContext* Graphics::GetDeviceContext() {

	return Screen;
}

ID2D1Bitmap1* Graphics::GetBitMap() {

	return Direct2DBackBuffer;
}


void Graphics::ClearScreen(float r, float g, float b) 
{
	Screen->Clear(D2D1::ColorF(r, g, b));
}

//void Graphics::DrawGridLines()
//{
//	brush->SetColor(D2D1::ColorF(1.0, 1.0, 1.0, 1.0));
//	rendertarget->DrawLine(D2D1::Line(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);	
//}



/*void BeginDraw() { Screen->BeginDraw(); }
void EndDraw() { Screen->EndDraw(); }*/