#pragma once
#include <DirectXMath.h>
class Collision
{
protected: // エイリアス
// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	static bool ChenkSphere2Sphere(XMFLOAT3 pos1, XMFLOAT3 pos2, float r1, float r2);
};