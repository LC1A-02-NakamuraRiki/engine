#include "Mouse.h"
#pragma comment(lib,"dinput8.lib")

void Mouse::MouseInitialize(WinApp *winApp)
{
	HRESULT result;
	result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	//�}�E�X�f�o�C�X����
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	//���̓f�[�^�`���̃Z�b�g
	result = devMouse->SetDataFormat(&c_dfDIMouse);
	//�r�����䃌�x���̃Z�b�g
	result = devMouse->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
}

void Mouse::MouseUpdate()
{
	HRESULT result;

	//�}�E�X�̏��擾�J�n
	result = devMouse->Acquire();
	//�O��̃L�[���͂�ۑ�
	oldMouse = mouse;
	//�}�E�X�̓��͏����擾
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