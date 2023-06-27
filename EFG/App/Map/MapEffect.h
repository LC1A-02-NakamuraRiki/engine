#pragma once
#include <DirectXMath.h>

class MapEffect
{
private: // エイリアス
// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	static bool LightAction(bool lightActionFlag, float lightCount);

	//ドア開く
	static float DoorOpen(float MapEffect::DoorOpen(XMFLOAT3 pos, bool gateOpenFlag, float doorAngle);
};

