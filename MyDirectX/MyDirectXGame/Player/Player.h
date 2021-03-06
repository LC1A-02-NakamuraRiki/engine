#pragma once
#include <DirectXMath.h>
#include "../Map/MapChip.h"

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
	void Initialize();
	
	void InitializeValue();

	void Update(MapChip* mapChip);
	
	void Draw();

	void Move(MapChip* mapChip);//歩き

	void WalkShaking();//揺れ

	void View();//視点の動き

	void AngleSearch();//歩く方向の算出
	
	XMFLOAT3 GetPos() { return pos; }
	XMFLOAT3 GetTarget() { return target; }
	float GetAngle() { return angle.y; }
	float GetViewSpeed() { return mouseViewSpeed; }
private:
	XMFLOAT3 pos = { -8.0f,0.0f,-40.0f };//プレイヤーの位置
	float r = 0.5;//プレイヤーの半径
	float moveSpeed = 0.4f;//歩きの速度
	float viewSpeed = 4.0f;//視点の速さ
	float mouseViewSpeed = 0.3f;//視点の速さ
	XMFLOAT3 target = { 0,0.0f,0 };//注視点
	float targetY = 0;//揺れの調整
	XMFLOAT3 angle = { 0,0,0 };//歩く方向
	float walkShaking = 2.5;//歩きの揺れる値
	bool isWalkShaking = false;//歩きの揺れのフラグ
	int walkShakingTime = 0;//歩きの揺れのタイム
	float angleX = 0; //カメラX軸
	float angleY = 180; //カメラY軸


};