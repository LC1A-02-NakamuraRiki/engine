#pragma once
#include<windows.h>
#include<wrl.h>
#define DIRECTINPUT_VERSION 0x0800
#include<dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include"../base/WinApp.h"
class Mouse
{
public:
	struct MouseCursor {
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};
private:
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	WinApp* winApp = nullptr;
public:
	void MouseInitialize(WinApp *winApp);
	void MouseUpdate();
	bool PushMouse(int MouseNumber);
	bool TriggerMouse(int MouseNumber);
	MouseCursor GetMouseMove();
private:
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE mouse = { 0 };
	DIMOUSESTATE oldMouse = { 0 };
};