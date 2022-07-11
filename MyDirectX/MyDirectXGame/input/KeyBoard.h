#pragma once
#include<windows.h>
#include<wrl.h>
#define DIRECTINPUT_VERSION 0x0800
#include<dinput.h>
#include"../base/WinApp.h"
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

class KeyBoard
{
private:
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//WindowAPI
	WinApp *winApp = nullptr;

private:
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE keyPre[256] = {};
	BYTE key[256] = {};

public:

	bool Initialize(HINSTANCE hInstance, HWND hwnd);
	void Update();
	bool PushKey(BYTE keyNumber);
	bool TriggerKey(BYTE keyNumber);
};