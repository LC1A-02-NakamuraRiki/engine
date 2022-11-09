#pragma once
#include <DirectXMath.h>
#include "MapChip.h"
#include "Sprite.h"
#include "SafeDelete.h"

class Player
{
protected: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	
	~Player();

	void Initialize();//最初の初期化
	
	void InitializeValue();//タイトル時の初期化

	void Update(MapChip* mapChip,bool tutrialFlag);//アップデート
	
	void Draw();
	
	void DrawSprite();

	void Move(MapChip* mapChip);//歩き

	void WalkShaking();//揺れ

	void View(bool tutrialFlag);//視点の動き

	void AngleSearch();//歩く方向の算出
	
	XMFLOAT3 GetPos() { return pos; }
	XMFLOAT2 GetMapPos() { return mapPosValue; }
	XMFLOAT3 GetTarget() { return target; }
	float GetAngle() { return angle.y; }
	float GetViewSpeed() { return mouseViewSpeed; }
	float SetViewSpeedPlus() { return mouseViewSpeed += 0.05f; }
	float SetViewSpeedMinus() { return mouseViewSpeed -= 0.05f; }
	bool GetShakeFlag() { return shakeFlag; }
	bool SetShakeFlag(bool ShakeFlag) { return shakeFlag = ShakeFlag; }
private:

	Sprite* spritePlayerDot = nullptr;
	Sprite* spritePlayerAngle = nullptr;

	XMFLOAT3 pos = { -8.0f,0.0f,-40.0f };//プレイヤーの位置
	XMFLOAT2 miniMapPos = { 100 + (16.0f * 10),650 + (16.0f * 8) };
	XMFLOAT2 mapPosValue = { 0,0 };
	float r = 0.5;//プレイヤーの半径
	float moveSpeed = 0.2f;//歩きの速度
	float viewSpeed = 4.0f;//視点の速さ
	float mouseViewSpeed = 0.2f;//視点の速さ
	XMFLOAT3 target = { 0,0.0f,0 };//注視点
	float targetY = 0;//揺れの調整
	XMFLOAT3 angle = { 0,0,0 };//歩く方向
	float walkShaking = 2.5;//歩きの揺れる値
	bool isWalkShaking = false;//歩きの揺れのフラグ
	int walkShakingTime = 0;//歩きの揺れのタイム
	float angleX = 0; //カメラX軸
	float angleY = 0; //カメラY軸

	bool shakeFlag = true;
};