#pragma once
#include "Camera.h"
#include "../input/Input.h"

/// <summary>
/// デバッグ用カメラ
/// </summary>
class DebugCamera :
	public Camera
{
	using XMMATRIX = DirectX::XMMATRIX;
public:

	/// コンストラクタ
	DebugCamera(int window_width, int window_height,Input *input);
	
	void Update();
private:
	Input *input;
	// スケーリング
	float scaleX = 1.0f;
	float scaleY = 1.0f;
};
