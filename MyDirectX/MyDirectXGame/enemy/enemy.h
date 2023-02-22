#pragma once
#include <DirectXMath.h>
#include "MapChip.h"
#include "Object3d.h"
#include "Player.h"
#include "Sprite.h"
#include "SafeDelete.h"

class Enemy
{
	enum MoveVector//移動方向
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
	~Enemy();
	void Initialize();//最初の初期化

	void InitializeValue();//タイトル時の初期化
	void InitializeValue2();//タイトル時の初期化
	void InitializeValue3();//タイトル時の初期化

	void Update(Player* player,MapChip* mapChip,XMFLOAT2 mapPos,XMFLOAT2 plusValue, bool catchFlag1, bool catchFlag2);//アップデート

	void Draw();//3dの描画

	void DrawSprite(MapChip* mapChip);//2dの描画

	void AI(Player* player,MapChip* mapChip, XMFLOAT2 plusValue);//歩き

	void Move(MapChip* mapChip, XMFLOAT2 mapPos);//歩き
	
	bool CatchCollision(Player* player);//プレイヤーと敵当たり判定

	bool DeathAnimation(Player* player);//殴りアニメーション

	XMFLOAT3 GetPos() { return pos; };//座標
	float GetRotation() { return angle; };//角度取得
	int GetStartStopTime() {return startStopTime;}//スタートの硬直時間
	
private:
	float angle; //向き
	Sprite* spriteEnemyDot = nullptr;//ミニマップの敵
	Sprite* spriteEnemyAngle = nullptr;//ミニマップの敵の向き
	Sprite* spriteDeadEffect = nullptr;//ミニマップの敵の向き
	XMFLOAT2 miniMapPos = { 100 + (16.0f * 10),650 + (16.0f * 14) };//ミニマップのドット座標
	float wallSize = 8;//壁の大きさ
	Model* modelEnemy = nullptr;//敵モデル
	Object3d* objEnemy;//敵OBJ
	XMFLOAT3 pos = { -8.0f,0.0f,+56.0f };//位置
	float speed = 2.0f;//スピード
	int nowMove = UP;//どの動きをしているか
	float adjustValueX = 0;//位置調整用変数X
	float adjustValueZ = 0;//位置調整用変数Z
	bool vReserveFlag = false;//縦優先
	bool wallHitFlag = false;//先読みの座標が壁に当たっているか
	int adjustmentTime = 0;//位置調整の時間
	int maxAdjustmentTime = 0;//位置調整の最大時間
	bool adjustmentFlag = false;//位置調整フラグ

	int killTime = 0;//殴りモーションの時間
	int startStopTime = 0;//スタートまでの硬直時間

	int mapX = int((pos.x / 8) + ((21 + 1) / 2));//マップチップの座標X
	int mapZ = int((pos.z / 8) + ((21 + 1) / 2));//マップチップの座標Z

	XMFLOAT3 deadPos = { 0.0f,2.5f,0.0f };
	float deadView = 0.0f;
	float deadAlpha = 0.0f;
	bool deadAlphaCountFlag = false;
};

