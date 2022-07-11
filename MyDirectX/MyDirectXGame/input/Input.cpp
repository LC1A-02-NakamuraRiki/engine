#include "Input.h"

void Input::Initialize(WinApp* winApp)
{
	//�L�[�{�[�h������
	keybord.Initialize(winApp->GetHInstance(), winApp->GetHwnd());

	//�R���g���[���[������
	gamepad.InitialiizeInput();

	//�}�E�X������
	mouse.MouseInitialize(winApp);
}

Input* Input::GetInstance()
{
	static Input input;
	return &input;
}

void Input::Update()
{
	//�L�[�{�[�h�X�V	
	keybord.Update();
	//�R���g���[���[�X�V
	gamepad.UpdateInput();
	//�}�E�X�X�V
	mouse.MouseUpdate();
}

bool Input::KeybordPush(BYTE keyNumber)
{
	return keybord.PushKey(keyNumber);
}

bool Input::KeybordTrigger(BYTE keyNumber)
{
	return keybord.TriggerKey(keyNumber);
}

bool Input::ControllerPush(ButtonKind button)
{
	return gamepad.IsButtonPush(button);
}

bool Input::ControllerUp(ButtonKind button)
{
	return gamepad.IsButtonUp(button);
}

bool Input::ControllerDown(ButtonKind button)
{
	return gamepad.IsButtonDown(button);
}

float Input::GetLeftAngle()
{
	return gamepad.GetLeftAngle();
}

float Input::GetRightAngle()
{
	return gamepad.GetRightAngle();
}

bool Input::ConRightInput()
{
	bool isHit = false;
	if (ControllerPush(RUpButton) == true ||
		ControllerPush(RDownButton) == true ||
		ControllerPush(RLeftButton) == true ||
		ControllerPush(RRightButton) == true)
	{
		isHit = true;
	}
	return isHit;
}

bool Input::ConLeftInput()
{
	bool isHit = false;
	if (ControllerPush(LUpButton) == true ||
		ControllerPush(LDownButton) == true ||
		ControllerPush(LLeftButton) == true ||
		ControllerPush(LRightButton) == true)
	{
		isHit = true;
	}
	return isHit;
}

bool Input::MousePush(int number)
{
	return mouse.PushMouse(number);
}

bool Input::MouseTrigger(int number)
{
	return mouse.TriggerMouse(number);
}

Mouse::MouseCursor Input::GetMouseMove()
{
	return mouse.GetMouseMove();
}