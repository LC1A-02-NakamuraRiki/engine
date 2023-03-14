#pragma once
#include <DirectXMath.h>
#include "MapChip.h"
#include "Object3d.h"
#include "Player.h"
#include "Sprite.h"
#include "SafeDelete.h"
#include "FbxObject3d.h"

class Enemy
{
	enum class MoveVector//移動方向
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};

	enum class AriaValue//移動方向
	{
		LEFTTOP = 2,
		CENTERTOP = 3,
		RIGHTTOP = 4,
		LEFTMIDDLE = 5,
		CENTERMIDDLE = 6,
		RIGHTMIDDLE = 7,
		LEFTBOTTOM = 8,
		CENTERBOTTOM = 9,
		RIGHTBOTTOM = 10,
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

	void ObjectUpdate(Player* player, MapChip* mapChip);

	void Draw(Player* player, ID3D12GraphicsCommandList* cmdList);//3dの描画

	void DrawSprite(MapChip* mapChip);//2dの描画

	void AI(Player* player,MapChip* mapChip, XMFLOAT2 plusValue);//歩き

	void Move(Player* player,MapChip* mapChip, XMFLOAT2 mapPos);//歩き

	void MoveValue(float spriteAngle, float objectAngle, float xSpeed, float zSpeed, float adjustX, float adjustZ);
	
	bool CatchCollision(Player* player);//プレイヤーと敵当たり判定

	bool DeathAnimation(Player* player);//殴りアニメーション

	bool StartFlag(Player* player, MapChip* mapChip, bool catchFlag1, bool catchFlag2);

	bool AnimationStop(MapChip* mapChip);

	void AiPriority(Player* player, XMFLOAT2 plusValue);

	int NodeValue(MapChip* mapChip);

	int CornerJudge(MoveVector vec, MoveVector result);

	void ThreeWayJudge1();
	void ThreeWayJudge2();
	void ThreeWayJudge3();
	void ThreeWayJudge4();
	void FourWayJudge();

	XMFLOAT3 GetPos() { return pos; };//座標
	float GetRotation() { return angle; };//角度取得
	int GetStartStopTime() {return startStopTime;}//スタートの硬直時間
	
private:
	float vectorX = 0;
	float vectorZ = 0;
	const float WALLSIZE = 8;//壁の大きさ
	const float MAPWALLSIZE = 16.0f;//ミニマップの壁の大きさ
	const int MAPVALUE = 21;//マップの最大サイズ
	std::unique_ptr<FbxModel> modelWalking;//歩きモデル
	std::unique_ptr<FbxObject3d> objectWalking;//歩きオブジェ
	std::unique_ptr<FbxModel> modelAttack;//攻撃モデル
	std::unique_ptr<FbxObject3d> objectAttack;//攻撃オブジェ
	float angle; //向き
	std::unique_ptr<Sprite> spriteEnemyDot;//ミニマップの敵
	std::unique_ptr<Sprite> spriteEnemyAngle;//ミニマップの敵の向き
	std::unique_ptr<Sprite> spriteDeadEffect;//ミニマップの敵の向き
	XMFLOAT2 miniMapPos = { 100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 14) };//ミニマップのドット座標
	XMFLOAT3 pos = { -8.0f,0.0f,+56.0f };//位置
	float speed = 2.0f;//スピード
	int nowMove = static_cast<int>(MoveVector::UP);//どの動きをしているか
	float adjustValueX = 0;//位置調整用変数X
	float adjustValueZ = 0;//位置調整用変数Z
	bool vReserveFlag = false;//縦優先
	bool wallHitFlag = false;//先読みの座標が壁に当たっているか
	int adjustmentTime = 0;//位置調整の時間
	int maxAdjustmentTime = 0;//位置調整の最大時間
	bool adjustmentFlag = false;//位置調整フラグ

	int killTime = 0;//殴りモーションの時間
	int startStopTime = 0;//スタートまでの硬直時間

	int mapX = int((pos.x / WALLSIZE) + ((MAPVALUE + 1) / 2));//マップチップの座標X
	int mapZ = int((pos.z / WALLSIZE) + ((MAPVALUE + 1) / 2));//マップチップの座標Z

	XMFLOAT3 deadPos = { 0.0f,2.5f,0.0f };//捕獲時のポジション
	float deadView = 0.0f;//捕獲時の視点
	float deadAlpha = 0.0f;//捕獲時のアルファ
	bool deadAlphaCountFlag = false;//捕獲時のアルファのフラグ
};

