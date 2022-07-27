#pragma once
#include <DirectXMath.h>
#include "../Map/MapChip.h"
#include "../3d/Object3d.h"
#include "../Player/Player.h"

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

	void InitializeValue();

	void Update(Player* player,MapChip* mapChip);

	void Draw();

	void AI(Player* player,MapChip* mapChip);//歩き

	void Move();//歩き
	
	bool catchCollision(Player* player);

	XMFLOAT3 GetPos() { return pos; };
private:
	Model* modelEnemy = nullptr;
	Object3d* objEnemy;
	XMFLOAT3 pos = { -8.0f,0.0f,+56.0f };//プレイヤーの位置
	int nowMove = UP;
	float adjustValueX = 0;
	float adjustValueZ = 0;
	bool vReserveFlag = false;
};

