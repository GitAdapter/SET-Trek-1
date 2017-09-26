#pragma once
#include <Windows.h>
#include <xaudio2.h>
#include <string.h>
#include <string>
#include "Wave.h"

using namespace std;

class Sound {

private:
	IXAudio2* g_engine;
	IXAudio2SourceVoice* g_source;
	IXAudio2MasteringVoice* g_master;
	Wave buffer;

public:

	Sound()
	{
	}

	~Sound()
	{
		g_engine->Release();
		//again, for COM
		CoUninitialize();
	}

	int SoundInitialize(char* wave_file)
	{
		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		//create the engine
		if (FAILED(XAudio2Create(&g_engine)))
		{
			CoUninitialize();
			return -1;
		}

		//create the mastering voice
		if (FAILED(g_engine->CreateMasteringVoice(&g_master)))
		{
			g_engine->Release();
			CoUninitialize();
			return -2;
		}

		if (!buffer.load(wave_file))
		{
			g_engine->Release();
			CoUninitialize();
			return -3;
		}


		//create the source voice, based on loaded wave format
		if (FAILED(g_engine->CreateSourceVoice(&g_source, buffer.wf())))
		{
			g_engine->Release();
			CoUninitialize();
			return -4;
		}
	}

	int SoundInitialize(char* wave_file, bool repeat)
	{
		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		//create the engine
		if (FAILED(XAudio2Create(&g_engine)))
		{
			CoUninitialize();
			return -1;
		}

		//create the mastering voice
		if (FAILED(g_engine->CreateMasteringVoice(&g_master)))
		{
			g_engine->Release();
			CoUninitialize();
			return -2;
		}

		if (!buffer.load(wave_file, repeat))
		{
			g_engine->Release();
			CoUninitialize();
			return -3;
		}


		//create the source voice, based on loaded wave format
		if (FAILED(g_engine->CreateSourceVoice(&g_source, buffer.wf())))
		{
			g_engine->Release();
			CoUninitialize();
			return -4;
		}
	}

	void RunSoundFileOnce()
	{
		g_source->Start();

		//g_source->Stop();
		//g_source->FlushSourceBuffers();
		//g_source->Start();

		//play the sound
		g_source->SubmitSourceBuffer(buffer.xaBuffer());
	}

	void StopSoundFile()
	{
		g_source->FlushSourceBuffers();
		g_source->Stop();
	}
};