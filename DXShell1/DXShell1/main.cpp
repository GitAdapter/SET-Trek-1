/*
* FILENAME: main.h
* PROJECT: DXShell1
* PROGRAMMER: Jody Markic
* FIRST VERSION: 2017-03-25
* DESCRIPTION: file contains the entry point the win32Main of the program SET Trek
*/
#include "Sound.h"
#include <Windows.h>
#include "Graphics.h"
#include "Level1.h"
#include "GameController.h"
//#include "Wave.h"
#include "Gameboard.h"
#include <windowsx.h>
#include <atlbase.h>
//#include <xaudio2.h>
#include <tchar.h>

Graphics* graphics;
Gameboard* gameBoard;

Sound* sound;

//IXAudio2* g_engine;
IXAudio2SourceVoice* g_source;
//IXAudio2MasteringVoice* g_master;
//GameController* gameController = new GameController();

bool usersTurn = false;
static int cmdShow;
bool endGame = false;

/*
Your Mission: Document the following code. What do all these components do?
*/
LRESULT CALLBACK WindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam )
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }
//BIG CHANGE! We are not Drawing/rendering here! 
// We've moved this down to the message handling loop below

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


LRESULT CALLBACK WindowProcPlanetMenu(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	if (uMsg == WM_DESTROY) { PostQuitMessage(0); return 0; }
	//BIG CHANGE! We are not Drawing/rendering here! 
	// We've moved this down to the message handling loop below

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Have you seen a 'main' for a Win32 app before? Please comment this.
int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE prevInstance,
	LPWSTR cmd,
	int nCmdShow
)

{
	//sound = new Sound();
	//sound->SoundInitialize("SpaceExplorationTwo.wav");
	//sound->RunSoundFileOnce();


	//CoInitializeEx(NULL, COINIT_MULTITHREADED);

	////create the engine
	//if (FAILED(XAudio2Create(&g_engine)))
	//{
	//	CoUninitialize();
	//	return -1;
	//}

	////create the mastering voice
	//if (FAILED(g_engine->CreateMasteringVoice(&g_master)))
	//{
	//	g_engine->Release();
	//	CoUninitialize();
	//	return -2;
	//}

	////helper class to load wave files; trust me, this makes it MUCH easier
	//Wave buffer;

	////load a wave file
	//if (!buffer.load("SpaceExplorationTwo.wav"))
	//{
	//	g_engine->Release();
	//	CoUninitialize();
	//	return -3;
	//}


	////create the source voice, based on loaded wave format
	//if (FAILED(g_engine->CreateSourceVoice(&g_source, buffer.wf())))
	//{
	//	g_engine->Release();
	//	CoUninitialize();
	//	return -4;
	//}

	////start consuming audio in the source voice
	//g_source->Start();

	//g_source->Stop();
	//g_source->FlushSourceBuffers();
	//g_source->Start();

	////play the sound
	//g_source->SubmitSourceBuffer(buffer.xaBuffer());


	//THESE NEED TO NOT EXIST OR GO SOMEWHERE ELSE
	//simple message loop
	//while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
	//{
		//play the sound
	//	g_source->SubmitSourceBuffer(buffer.xaBuffer());
	//}



	//release the engine, NOT the voices!
	//g_engine->Release();
	//again, for COM
	//CoUninitialize();
	// END OF THESE NEED TO NOT EXIST OR GO SOMEWHERE ELSE


	//Do a bit of reading - What is this Window Class used for? 
	// What are the major parameters below?
	//GameController* gameController = new GameController();
	cmdShow = nCmdShow;
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW; //Alert - This is useful here... what does it do?

	RegisterClassEx(&windowclass);


	RECT rect = { 0, 0, 1024, 768 };//Do these numbers look significant to you? What are they?
	AdjustWindowRectEx(&rect, WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION | WS_SIZEBOX, false, WS_EX_OVERLAPPEDWINDOW);

	//Below is another important process to understand... what are we doing?
	//Why is this connected to rect we just defined above?
	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "DirectXShell1", WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CAPTION | WS_SIZEBOX,
		100, 100, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);

	if (!windowhandle) return -1;

	graphics = new Graphics();
	if (!graphics->Init(windowhandle))
	{
		delete graphics;
		return -1;
	}

	GameLevel::Init(graphics);
	ShowWindow(windowhandle, nCmdShow);
	GameController::LoadInitialLevel(new Level1()); //render space

	//render planets

#pragma region GameLoop
	//Below, we have essentially an infinite loop that will keep the window running and will dispatch/show messages
	//As many people will tell you, most Windows you see are just infinite loops waiting for some kind of work-flow or 
	//system-based interuption.

	//Note - Our message handling has changed from the first demo code.
	//Here, we use a PeekMessage to avoid locking the graphics/windoProc
	//when a message has to be dispatched.
	MSG message;
	message.message = WM_NULL; //Do not have this set to WM_QUIT, which has a specific context

	static int xCoordinate = -1;
	static int yCoordinate= -1;
	while (message.message != WM_QUIT)
	{		
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			//This allows us to send a message to the WindowProc IF there is one
			DispatchMessage(&message);

		}
		else
		{
			//if a left button click happens on the client window
			if (message.message == WM_LBUTTONDOWN)
			{
				//get the x and y pixel position
				xCoordinate = GET_X_LPARAM(message.lParam);
				yCoordinate = GET_Y_LPARAM(message.lParam);
			}
			
			//pass the pixel position into the Method Update
			endGame = GameController::Update(xCoordinate, yCoordinate, windowhandle);
			xCoordinate = -1;
			yCoordinate = -1;
			//Update Routine... we've moved the code for handling updates to GameController
			//GameController::Update(xCoordinate, yCoordinate);

			//Render Routine... This is very modular. GameController now handles the rendering
			graphics->BeginDraw();
			GameController::Render();
			graphics->EndDraw();



			DXGI_PRESENT_PARAMETERS parameters = { 0 };
			parameters.DirtyRectsCount = 0;
			parameters.pDirtyRects = nullptr;
			parameters.pScrollRect = nullptr;
			parameters.pScrollOffset = nullptr;
			graphics->GetSwapChain()->Present1(1, 0, &parameters);

			if (endGame)
			{
				DestroyWindow(windowhandle);
			}
			//hr = DXGISwapChain->Present1(1, 0, &parameters);
		}
	}

#pragma endregion
	LPCSTR endMessage = "Your Energy Points Have Reached Zero.\n Please Play Again!";
	//LPCWSTR ouput = A2W(endMessage);
	MessageBox(NULL,
		_T("Your Energy Points Have Reached Zero.\n Please Play Again!"),
		_T("Your Ship Has Been Destroyed!"),
		MB_ICONWARNING | MB_DEFBUTTON2);
	delete graphics;
	return 0;
}