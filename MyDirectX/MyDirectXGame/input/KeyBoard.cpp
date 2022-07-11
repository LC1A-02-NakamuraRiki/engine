#include "KeyBoard.h"
#pragma comment(lib,"dinput8.lib")

bool KeyBoard::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT result = S_FALSE;

	// DirectInput�I�u�W�F�N�g�̐���	
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void **)&dinput, nullptr);

	// �L�[�{�[�h�f�o�C�X�̐���	
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);

	// ���̓f�[�^�`���̃Z�b�g
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��

	// �r�����䃌�x���̃Z�b�g
	result = devkeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

	return true;
}

void KeyBoard::Update()
{
	HRESULT result;

	//�L�[�{�[�h���̎擾�J�n
	result = devkeyboard->Acquire();

	memcpy(keyPre, key, sizeof(key));

	//�S�L�[�̓��͏�Ԃ��擾����
	result = devkeyboard->GetDeviceState(sizeof(key), key);
}

bool KeyBoard::PushKey(BYTE keyNumber)
{
	if (key[keyNumber])
	{
		return true;
	}
	return false;
}

bool KeyBoard::TriggerKey(BYTE keyNumber)
{
	if (!keyPre[keyNumber] && key[keyNumber])
	{
		return true;
	}
	return false;
}
