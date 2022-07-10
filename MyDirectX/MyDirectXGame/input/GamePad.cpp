#include"GamePad.h"
#include <DirectXMath.h>
static LPDIRECTINPUT8 g_InputInterface;							//!< DIRECTINPUT8のポインタ
static LPDIRECTINPUTDEVICE8 g_GamePadDevice;					//!< DIRECTINPUTDEVICE8のポインタ
static ButtonState g_ButtonStates[ButtonKind::ButtonKindMax];
static float leftAngle;
static float rightAngle;

// 入力インターフェースの作成
bool InterfaceCreate();

// ゲームパッドデバイスの作成
bool CreateDevice();

// ゲームパッドの更新
void UpdateGamePad();

struct DeviceEnumParameter
{
	LPDIRECTINPUTDEVICE8* GamePadDevice;
	int FindCount;
};

BOOL SetUpCooperativeLevel(LPDIRECTINPUTDEVICE8 device)
{
	return true;
}

BOOL StartGamePadControl()
{
	// デバイスが生成されてない
	if (g_GamePadDevice == nullptr)
	{
		return false;
	}

	// 制御開始
	if (FAILED(g_GamePadDevice->Acquire()))
	{
		return false;
	}

	DIDEVCAPS cap;
	g_GamePadDevice->GetCapabilities(&cap);
	// ポーリング判定
	if (cap.dwFlags & DIDC_POLLEDDATAFORMAT)
	{
		DWORD error = GetLastError();
		// ポーリング開始
		if (FAILED(g_GamePadDevice->Poll()))
		{
			return false;
		}
	}

	return true;
}

BOOL SetUpGamePadProperty(LPDIRECTINPUTDEVICE8 device)
{
	// 軸モードを絶対値モードとして設定
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_ABS;
	if (FAILED(device->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return false;
	}

	// X軸の値の範囲設定
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.diph.dwObj = DIJOFS_X;
	diprg.lMin = -1000;
	diprg.lMax = 1000;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	// Y軸の値の範囲設定
	diprg.diph.dwObj = DIJOFS_Y;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	diprg.diph.dwObj = DIJOFS_Z;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}
	//右スティック
	diprg.diph.dwObj = DIJOFS_RX;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	// Y軸の値の範囲設定
	diprg.diph.dwObj = DIJOFS_RY;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	diprg.diph.dwObj = DIJOFS_RZ;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	return true;
}

BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	DeviceEnumParameter* parameter = (DeviceEnumParameter*)pvRef;
	LPDIRECTINPUTDEVICE8 device = nullptr;

	// 既に発見しているなら終了
	if (parameter->FindCount >= 1)
	{
		return DIENUM_STOP;
	}

	// デバイス生成
	HRESULT hr = g_InputInterface->CreateDevice(
		lpddi->guidInstance,
		parameter->GamePadDevice,
		NULL);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	// 入力フォーマットの指定
	device = *parameter->GamePadDevice;
	hr = device->SetDataFormat(&c_dfDIJoystick);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	// プロパティの設定
	if (SetUpGamePadProperty(device) == false)
	{
		return DIENUM_STOP;
	}

	// 協調レベルの設定
	if (SetUpCooperativeLevel(device) == false)
	{
		return DIENUM_STOP;
	}

	// 発見数をカウント
	parameter->FindCount++;

	return DIENUM_CONTINUE;
}

bool gamePad::InitialiizeInput()
{
	// インターフェース作成
	if (InterfaceCreate() == false)
	{
		return false;
	}

	// デバイス作成
	if (CreateDevice() == false)
	{
		ReleaseInput();
		return false;
	}

	// 入力情報の初期化
	for (int i = 0; i < ButtonKind::ButtonKindMax; i++)
	{
		g_ButtonStates[i] = ButtonState::ButtonStateNone;
	}

	return true;
}

void gamePad::ReleaseInput()
{
	// デバイスの解放
	if (g_GamePadDevice != nullptr)
	{
		// 制御を停止
		g_GamePadDevice->Unacquire();
		g_GamePadDevice->Release();
		g_GamePadDevice = nullptr;
	}

	// インターフェースの解放
	if (g_InputInterface != nullptr)
	{
		g_InputInterface->Release();
		g_InputInterface = nullptr;
	}
}

void gamePad::UpdateInput()
{
	UpdateGamePad();
}

bool gamePad::IsButtonPush(ButtonKind button)
{
	if (g_ButtonStates[button] == ButtonState::ButtonStatePush)
	{
		return true;
	}

	return false;
}

bool gamePad::IsButtonUp(ButtonKind button)
{
	if (g_ButtonStates[button] == ButtonState::ButtonStateUp)
	{
		return true;
	}

	return false;
}

bool gamePad::IsButtonDown(ButtonKind button)
{
	if (g_ButtonStates[button] == ButtonState::ButtonStateDown)
	{
		return true;
	}

	return false;
}

float gamePad::GetLeftAngle()
{
	return leftAngle;
}

float gamePad::GetRightAngle()
{
	return rightAngle;
}

bool InterfaceCreate()
{
	HRESULT hr = DirectInput8Create(
		GetModuleHandle(nullptr),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&g_InputInterface,
		NULL);

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool CreateDevice()
{
	DeviceEnumParameter parameter;

	parameter.FindCount = 0;
	parameter.GamePadDevice = &g_GamePadDevice;

	// GAMEPADを調べる
	g_InputInterface->EnumDevices(
		DI8DEVTYPE_GAMEPAD,			// 検索するデバイスの種類
		DeviceFindCallBack,			// 発見時に実行する関数
		&parameter,					// 関数に渡す値
		DIEDFL_ATTACHEDONLY			// 検索方法
	);

	// JOYSTICKを調べる
	g_InputInterface->EnumDevices(
		DI8DEVTYPE_JOYSTICK,
		DeviceFindCallBack,
		&parameter,
		DIEDFL_ATTACHEDONLY
	);

	// どちらも見つけることが出来なかったら失敗
	if (parameter.FindCount == 0)
	{
		return false;
	}

	int count = 0;
	// 制御開始
	while (StartGamePadControl() == false)
	{
		Sleep(100);
		count++;
		if (count >= 5)
		{
			break;
		}
	}

	return true;
}

void UpdateGamePad()
{
	if (g_GamePadDevice == nullptr)
	{
		return;
	}

	DIJOYSTATE pad_data;

	// デバイス取得
	HRESULT hr = g_GamePadDevice->GetDeviceState(sizeof(DIJOYSTATE), &pad_data);
	if (FAILED(hr))
	{
		// 再度制御開始
		if (FAILED(g_GamePadDevice->Acquire()))
		{
			for (int i = 0; i < ButtonKind::ButtonKindMax; i++)
			{
				g_ButtonStates[i] = ButtonState::ButtonStateNone;
			}
			g_GamePadDevice->Poll();
		}
		return;
	}

	bool is_push[ButtonKind::ButtonKindMax];
	// スティック判定
	int unresponsive_range = 200;
	if (pad_data.lX < -unresponsive_range)
	{
		is_push[ButtonKind::LLeftButton] = true;
	}
	else if (pad_data.lX > unresponsive_range)
	{
		is_push[ButtonKind::LRightButton] = true;
	}

	if (pad_data.lY < -unresponsive_range)
	{
		is_push[ButtonKind::LUpButton] = true;
	}
	else if (pad_data.lY > unresponsive_range)
	{
		is_push[ButtonKind::LDownButton] = true;
	}

	if (pad_data.lRx < -unresponsive_range)
	{
		is_push[ButtonKind::RLeftButton] = true;
	}
	else if (pad_data.lRx > unresponsive_range)
	{
		is_push[ButtonKind::RRightButton] = true;
	}

	if (pad_data.lRy < -unresponsive_range)
	{
		is_push[ButtonKind::RUpButton] = true;
	}
	else if (pad_data.lRy > unresponsive_range)
	{
		is_push[ButtonKind::RDownButton] = true;
	}

	if (pad_data.lZ > unresponsive_range)
	{
		is_push[ButtonKind::ButtonLT] = true;
	}
	else if (pad_data.lZ < -unresponsive_range)
	{
		is_push[ButtonKind::ButtonRT] = true;
	}
#define PI 3.141592653589793
	leftAngle = atan2(0 - pad_data.lX, 0 - pad_data.lY);
	rightAngle = atan2(0 - pad_data.lRx, 0 - pad_data.lRy);
	// 十字キー判定
	if (pad_data.rgdwPOV[0] != 0xFFFFFFFF)
	{
		float rad = ((pad_data.rgdwPOV[0] / 100.0f) * 180.0 / PI);;
		float x = sinf(rad);
		float y = cosf(rad);

		if (x < -0.01f)
		{
			is_push[ButtonKind::LLeftButton] = true;
		}
		else if (x > 0.01f)
		{
			is_push[ButtonKind::LRightButton] = true;
		}

		if (y > 0.01f)
		{
			is_push[ButtonKind::LUpButton] = true;
		}
		else if (y < -0.01f)
		{
			is_push[ButtonKind::LDownButton] = true;
		}
	}

	// ボタン判定
	for (int i = 0; i < 32; i++)
	{
		if (!(pad_data.rgbButtons[i] & 0x80))
		{
			continue;
		}

		switch (i)
		{
		case 0:
			is_push[ButtonKind::Button01] = true;
			break;
		case 1:
			is_push[ButtonKind::Button02] = true;
			break;
		case 2:
			is_push[ButtonKind::Button03] = true;
			break;
		case 3:
			is_push[ButtonKind::Button04] = true;
			break;
		case 4:
			is_push[ButtonKind::ButtonLB] = true;
			break;
		case 5:
			is_push[ButtonKind::ButtonRB] = true;
			break;
		}
	}

	// 入力情報からボタンの状態を更新する
	for (int i = 0; i < ButtonKind::ButtonKindMax; i++)
	{
		if (is_push[i] == true)
		{
			if (g_ButtonStates[i] == ButtonState::ButtonStateNone)
			{
				g_ButtonStates[i] = ButtonState::ButtonStateDown;
			}
			else
			{
				g_ButtonStates[i] = ButtonState::ButtonStatePush;
			}
		}
		else
		{
			if (g_ButtonStates[i] == ButtonState::ButtonStatePush)
			{
				g_ButtonStates[i] = ButtonState::ButtonStateUp;
			}
			else
			{
				g_ButtonStates[i] = ButtonState::ButtonStateNone;
			}
		}
	}
}