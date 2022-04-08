#pragma once
#include<windows.h>
#include<wrl.h>
#define DIRECTINPUT_VERSION 0x0800
#include<dinput.h>
#include"../base/WinApp.h"
class Input
{
public:
	struct MousePoint {
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};

private:
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//WindowAPI
	WinApp *winApp = nullptr;

public: // ê√ìIÉÅÉìÉoïœêî
	static Input *GetInstance();

public:
	bool Initialize(HINSTANCE hInstance, HWND hwnd);
	void MouseInitialize(WinApp *winApp);

	void Update();
	void MouseUpdate();
	bool PushKey(BYTE keyNumber);
	bool PushMouse(int MouseNumber);
	bool TriggerKey(BYTE keyNumber);
	bool TriggerMouse(int MouseNumber);
	MousePoint GetMousePoint();
private:
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devkeyboard;
	BYTE keyPre[256] = {};
	BYTE key[256] = {};

	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouse = { 0 };
	DIMOUSESTATE2 oldMouse = { 0 };
};