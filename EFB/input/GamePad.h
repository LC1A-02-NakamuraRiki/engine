#pragma once
#include <dinput.h>
#include <DirectXMath.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

enum ButtonKind
{
	LUpButton,
	LDownButton,
	LLeftButton,
	LRightButton,
	RUpButton,
	RDownButton,
	RLeftButton,
	RRightButton,
	Button01,
	Button02,
	Button03,
	Button04,
	ButtonRB,
	ButtonLB,
	ButtonRT,
	ButtonLT,
	ButtonKindMax,
};

enum ButtonState
{
	ButtonStateNone,
	ButtonStateDown,
	ButtonStatePush,
	ButtonStateUp,
	ButtonStateMax,
};

class gamePad
{
private:
	DIJOYSTATE pad_data;
	DIJOYSTATE oldpad_data;
	LPDIRECTINPUTDEVICE8 g_GamePadDevice = nullptr;
	LPDIRECTINPUT8 g_InputInterface = nullptr;

public:

	bool InitialiizeInput();//

	void ReleaseInput();//

	void UpdateInput();//

	bool IsButtonPush(ButtonKind button);//

	bool IsButtonUp(ButtonKind button);//

	bool IsButtonDown(ButtonKind button);//

	float GetLeftAngle();//

	float GetRightAngle();//
};