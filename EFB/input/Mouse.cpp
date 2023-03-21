#include "Mouse.h"
#pragma comment(lib,"dinput8.lib")

void Mouse::MouseInitialize(WinApp *winApp)
{
	HRESULT result;
	result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	//マウスデバイス生成
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	//入力データ形式のセット
	result = devMouse->SetDataFormat(&c_dfDIMouse);
	//排他制御レベルのセット
	result = devMouse->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Mouse::MouseUpdate()
{
	HRESULT result;

	//マウスの情報取得開始
	result = devMouse->Acquire();
	//前回のキー入力を保存
	oldMouse = mouse;
	//マウスの入力情報を取得
	result = devMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouse);
}

bool Mouse::PushMouse(int MouseNumber)
{
	if (mouse.rgbButtons[MouseNumber])
	{
		return true;
	}
	return false;
}

bool Mouse::TriggerMouse(int MouseNumber)
{
	if (mouse.rgbButtons[MouseNumber] && !oldMouse.rgbButtons[MouseNumber])
	{
		return true;
	}
	return false;
}

Mouse::MouseCursor  Mouse::GetMouseMove()
{
	MouseCursor tmp;
	tmp.lX = mouse.lX;
	tmp.lY = mouse.lY;
	tmp.lZ = mouse.lZ;
	return tmp;
}