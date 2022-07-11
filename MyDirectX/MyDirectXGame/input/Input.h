#pragma once
#include"GamePad.h"
#include"Keyboard.h"
#include"Mouse.h"
#include"../base/WinApp.h"
class Input
{
private:
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//コントローラー
	gamePad gamepad;
	//キーボード
	KeyBoard keybord;
	//マウス
	Mouse mouse;

	WinApp* winApp = nullptr;
public:
	Input() = default;
	Input(const Input&) = delete;
	~Input() = default;
	Input& operator=(const Input&) = delete;

	static Input* GetInstance();

	//初期化
	void Initialize(WinApp* winApp);
	//更新
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