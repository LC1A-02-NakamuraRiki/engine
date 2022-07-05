#include "DebugCamera.h"
#include <cassert>
#include "../input/Input.h"
using namespace DirectX;

DebugCamera::DebugCamera(int window_width, int window_height)
	: Camera(window_width, window_height)
{
	// 画面サイズに対する相対的なスケールに調整
	scaleX = 1.0f / (float)window_width;
	scaleY = 1.0f / (float)window_height;
}

void DebugCamera::Update()
{		
	float move = 0.1;
	if (Input::GetInstance()->PushKey(DIK_RSHIFT) && Input::GetInstance()->PushKey(DIK_RCONTROL))
	{
		if (Input::GetInstance()->PushKey(DIK_7)) { CameraMoveEyeVector({ 0.0f,+move,0.0f }); }
		else if (Input::GetInstance()->PushKey(DIK_8)) { CameraMoveEyeVector({ 0.0f,-move,0.0f }); }
		if (Input::GetInstance()->PushKey(DIK_5)) { CameraMoveEyeVector({-move, 0.0f,0.0f }); }
		else if (Input::GetInstance()->PushKey(DIK_6)) { CameraMoveEyeVector({+move, 0.0f,0.0f }); }
		if (Input::GetInstance()->PushKey(DIK_9)) { CameraMoveEyeVector({ 0.0f, 0.0f,move }); }
		else if (Input::GetInstance()->PushKey(DIK_0)) { CameraMoveEyeVector({ 0.0f, 0.0f,-move }); }
	}
	Camera::Update();
}
