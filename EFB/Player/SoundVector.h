#pragma once
#include <DirectXMath.h>

class SoundVector
{
protected: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	static bool DistanceSearch(float playerX, float playerZ, float enemyX, float enemyZ);//距離を見る
	static float VectorSearch(float playerX, float playerZ, float enemyX, float enemyZ);//角度を見る
};

