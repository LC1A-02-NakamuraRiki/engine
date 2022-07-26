#pragma once
#include <DirectXMath.h>
#include "../Map/MapChip.h"
#include "../3d/Object3d.h"

class Enemy
{
	enum MoveVector
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};
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

	void AI(MapChip* mapChip);//歩き

	void Move();//歩き
	
	XMFLOAT3 GetPos() { return pos; };
private:
	Model* modelEnemy = nullptr;
	Object3d* objEnemy;
	XMFLOAT3 pos = { -8.0f,0.0f,+56.0f };//プレイヤーの位置
	int nowMove = UP;
};

