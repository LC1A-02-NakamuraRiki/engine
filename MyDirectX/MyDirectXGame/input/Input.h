#pragma once
#include"GamePad.h"
#include"Keyboard.h"
#include"Mouse.h"
#include"../base/WinApp.h"
class Input
{
private:
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//�R���g���[���[
	gamePad gamepad;
	//�L�[�{�[�h
	KeyBoard keybord;
	//�}�E�X
	Mouse mouse;

	WinApp* winApp = nullptr;
public:
	Input() = default;
	Input(const Input&) = delete;
	~Input() = default;
	Input& operator=(const Input&) = delete;

	static Input* GetInstance();

	//������
	void Initialize(WinApp* winApp);
	//�X�V
	void Update();

	bool KeybordPush(BYTE keyNumber);

	bool KeybordTrigger(BYTE keyNumber);

	bool ControllerPush(ButtonKind button);

	bool ControllerUp(ButtonKind button);

	bool ControllerDown(ButtonKind button);

	float GetLeftAngle();

	float GetRightAngle();

	bool ConRightInput();

	bool ConLeftInput();

	bool MousePush(int number);

	bool MouseTrigger(int number);

	Mouse::MouseCursor GetMouseMove();
};