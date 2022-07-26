#pragma once
#include <DirectXMath.h>
#include "../Map/MapChip.h"
#include "../3d/Object3d.h"

class Enemy
{
protected: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Initialize();

	void Update(MapChip* mapChip);

	void Draw();

	void Move(MapChip* mapChip);//歩き
private:
	Model* modelEnemy = nullptr;
	Object3d* objEnemy;
};

