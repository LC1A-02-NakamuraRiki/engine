#pragma once
#include <DirectXMath.h>
#include "MapChip.h"
#include "Object3d.h"
#include "Player.h"
#include "Sprite.h"
#include "SafeDelete.h"

class Enemy
{
	enum MoveVector
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};
	struct Node
	{
		int startX;
		int startZ;
		int startVector;
		
		int endX;
		int endZ;
		int endVector;
	};
protected: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	~Enemy();
	void Initialize();//最初の初期化

	void InitializeValue();//タイトル時の初期化
	void InitializeValue2();//タイトル時の初期化

	void Update(Player* player,MapChip* mapChip,XMFLOAT2 mapPos,XMFLOAT2 plusValue);//アップデート

	void Draw();

	void DrawSprite(MapChip* mapChip);

	void AI(Player* player,MapChip* mapChip, XMFLOAT2 plusValue);//歩き

	void Move(MapChip* mapChip, XMFLOAT2 mapPos);//歩き
	
	bool CatchCollision(Player* player);//プレイヤーと敵当たり判定

	bool DeathAnimation(Player* player);
	XMFLOAT3 GetPos() { return pos; };
private:
	Sprite* spriteEnemyDot = nullptr;
	Sprite* spriteEnemyAngle = nullptr;
	XMFLOAT2 miniMapPos = { 100 + (16.0f * 10),650 + (16.0f * 14) };
	float wallSize = 8;
	Model* modelEnemy = nullptr;
	Object3d* objEnemy;
	XMFLOAT3 pos = { -8.0f,0.0f,+56.0f };//位置
	float speed = 2.0f;
	int nowMove = UP;//どの動きをしているか
	float adjustValueX = 0;//位置調整用変数X
	float adjustValueZ = 0;//位置調整用変数Z
	bool vReserveFlag = false;//縦優先
	bool wallHitFlag = false;
	int adjustmentTime = 0;
	int maxAdjustmentTime = 0;
	bool adjustmentFlag = false;

	int killTime = 0;

	Node node[120];

	int mapZ = int((pos.z / 8) + ((21 + 1) / 2));
	int mapX = int((pos.x / 8) + ((21 + 1) / 2));
	int count = 0;
	int nextVector = 0;
};

