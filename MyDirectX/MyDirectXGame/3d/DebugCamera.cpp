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
	Camera::Update();
}
