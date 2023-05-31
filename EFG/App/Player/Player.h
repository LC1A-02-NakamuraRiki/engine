#pragma once
#include <DirectXMath.h>
#include "MapChip.h"
#include "Sprite.h"

class Player
{
	enum class CollisionDirection//移動方向
	{
		FRONT,
		BACK,
		RIGHT,
		LEFT
	};
	enum class VerticalOrHorizontal//移動方向
	{
		VERTICAL,
		HORIZONTAL
	};

	enum class CHECKVECTOR//移動方向
	{
		ZPLUS,
		ZMINUS,
		XPLUS,
		XMINUS,
	};
private: // エイリアス
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

	void Update(MapChip* mapChip,bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3);//アップデート
	
	void DrawSprite();//2D描画

	void Move(MapChip* mapChip, bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3);//歩き

	void MoveValue(float vec);

	void MoveCollision(MapChip* mapChip, float vec);

	

	bool TouchWall(MapChip* mapChip, CollisionDirection direction);

	void PushBack(VerticalOrHorizontal VerOrHor, float vec);

	void WalkShaking();//揺れ

	void View(bool tutrialFlag, bool catchFlag,bool catchFlag2, bool catchFlag3);//視点の動き

	void AngleSearch();//歩く方向の算出

	void TutorialAlpha(MapChip* mapChip);

	void UiUpdate();

	void MapDraw();

	void UiDraw();

	bool AlartFlag(MapChip* mapChip, XMFLOAT3 enemyPos);

	int ShortCutFlag(MapChip* mapChip, XMFLOAT3 enemyPos, int X, int Z);

	XMFLOAT2 ShortCutValue(MapChip* mapChip, XMFLOAT3 enemyPos, float X, float Z,CHECKVECTOR vector);

	XMFLOAT2 GetShortCut(MapChip* mapChip,XMFLOAT3 enemyPos);//プレイヤーの4マス先読み

	XMFLOAT3 GetPos() { return pos; }//3D座標の取得
	XMFLOAT3 SetPos(XMFLOAT3 pos) { return this->pos = pos; }//3D座標の指定
	XMFLOAT2 GetMapPos() { return mapPosValue; }//2D座標の取得
	XMFLOAT3 GetTarget() { return target; }//注視点の取得
	float GetAngle() { return angle.y; }//見ている方向の取得
	float GetViewAngle() { return angleY; }//見ている方向の取得
	float SetViewAngleY(float value) { return angleY += value; }//見ている方向の指定
	float SetViewAngleY2(float value) { return angleY = value; }//見ている方向の指定
	float SetViewAngleX(float value) { return angleX += value; }//見ている方向の指定
	float SetViewAngleX2(float value) { return angleX = value; }//見ている方向の指定
	float GetViewSpeed() { return mouseViewSpeed; }//視点感度の取得
	float SetViewSpeedPlus() { return mouseViewSpeed += 0.05f; }//視点感度の指定
	float SetViewSpeedMinus() { return mouseViewSpeed -= 0.05f; }//視点感度の指定
	bool GetShakeFlag() { return shakeFlag; }//シェイクフラグの取得
	bool SetShakeFlag(bool ShakeFlag) { return shakeFlag = ShakeFlag; }//シェイクフラグの指定
private:
	const float WALLSIZE = 8.0f;//壁の大きさ
	const float MAPWALLSIZE = 16.0f;//ミニマップの壁の大きさ
	const int MAPVALUE = 21;//マップの最大サイズ
	const float MOVESPEED = 0.18f;//歩きの速度
	const float PI = 3.141592f;
	const float INVERSEVECTOR = 180;
	const float R = 0.5f;//半径
	const float CORNER = 0.35f;//角までの距離
	std::unique_ptr<Sprite> spritePlayerDot;//ミニマップのドット
	std::unique_ptr<Sprite> spritePlayerAngle;//ミニマップの見ている位置
	std::unique_ptr<Sprite> spriteMoveUI;//移動のUI
	std::unique_ptr<Sprite> spriteViewUI;//視点のUI
	std::unique_ptr<Sprite> spriteOpenUI;//開けるUI
	XMFLOAT3 pos = { -8.0f,0.0f,-40.0f };//プレイヤーの位置
	XMFLOAT2 miniMapPos = { 100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 8) };//ミニマップ初期値
	XMFLOAT2 mapPosValue = { 0,0 };//マップの座標
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

	bool shakeFlag = true;//シェイクのON/OFF

	float moveTutorial = 1.0f;//移動チュートリアルアルファ
	bool moveTutorialFlag = false;//移動チュートリアルフラグ
	float viewTutorial = 1.0f;//視点チュートリアルアルファ
	bool viewTutorialFlag = false;//視点チュートリアルフラグ
	float openTutorial = 1.0f;//開けるチュートリアルアルファ
	bool openTutorialFlag = false;//開けるチュートリアルフラグ
};