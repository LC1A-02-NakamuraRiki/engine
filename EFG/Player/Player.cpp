#include "Player.h"
#include "Input.h"
#include <algorithm>
#include <iostream>

using namespace DirectX;

Player::~Player()
{
}

void Player::Initialize()
{
	//スプライトの初期化
	Sprite::LoadTexture(3, L"Resources/PlayerDot.png");	//プレイヤーの点
	Sprite::LoadTexture(6, L"Resources/angle.png");		//プレイヤーの向いてる方向
	Sprite::LoadTexture(100, L"Resources/MoveUI.png");	//チュートリアルMoveのUI
	Sprite::LoadTexture(101, L"Resources/ViewUI.png");	//チュートリアルViewのUI
	Sprite::LoadTexture(102, L"Resources/OpenUI.png");	//チュートリアルOpenのUI
	//スプライトの作成
	spritePlayerDot = std::unique_ptr<Sprite>(Sprite::Create(3, miniMapPos));	//プレイヤーの点
	spritePlayerAngle = std::unique_ptr<Sprite>(Sprite::Create(6, miniMapPos));	//プレイヤーの向いてる方向
	spriteMoveUI = std::unique_ptr<Sprite>(Sprite::Create(100, { 0,0 }));		//チュートリアルMoveのUI
	spriteViewUI = std::unique_ptr<Sprite>(Sprite::Create(101, { 0,0 }));		//チュートリアルViewのUI
	spriteOpenUI = std::unique_ptr<Sprite>(Sprite::Create(102, { 0,0 }));		//チュートリアルOpenのUI
}

void Player::InitializeValue()
{
	miniMapPos = { 100 + (MAPWALLSIZE * 11),650 + (MAPWALLSIZE * 11) };//ミニマップ初期値
	pos = { -4.0f,0.0f,4.0f };	//プレイヤーの位置
	mapPosValue = { 0,0 };		//マップの座標
	viewSpeed = 4.0f;			//視点の速さ
	target = { 0,0.0f,0 };		//注視点
	targetY = 0;				//揺れの調整
	angle = { 0,0,0 };			//歩く方向
	walkShaking = 2.5;			//歩きの揺れる値
	isWalkShaking = false;		//歩きの揺れのフラグ
	walkShakingTime = 0;		//歩きの揺れのタイム
	angleX = 0;					//カメラX軸
	angleY = 0;					//カメラY軸

}

void Player::Update(MapChip* mapChip, bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3)
{
	//チュートリアルの演出
	TutorialAlpha(mapChip);
	
	//プレイヤーの向きの算出
	AngleSearch();

	//移動関連
	Move(mapChip,tutrialFlag,catchFlag,catchFlag2,catchFlag3);//移動	
	WalkShaking();//歩きの揺れ
	View(tutrialFlag, catchFlag, catchFlag2, catchFlag3);//視点制御

	//スプライト関連のポジションとアングルセット
	UiUpdate();
}

void Player::DrawSprite()
{
	//プレイヤーのミニマップの情報
	spritePlayerAngle->Draw(1.0f);
	spritePlayerDot->Draw(1.0f);

	//チュートリアルの描画
	spriteViewUI->Draw(viewTutorial);
	spriteMoveUI->Draw(moveTutorial);
	spriteOpenUI->Draw(openTutorial);
}

void Player::Move(MapChip* mapChip, bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3)
{	
	//移動
	if (tutrialFlag == false && catchFlag == false && catchFlag2 == false && catchFlag3 == false)//演出に入っていないか
	{
		if (Input::GetInstance()->KeybordPush(DIK_W)){
			MoveValue(0);
			MoveCollision(mapChip, 0);
		}
		if (Input::GetInstance()->KeybordPush(DIK_A)){
			MoveValue(270);
			MoveCollision(mapChip, 270);
		}
		if (Input::GetInstance()->KeybordPush(DIK_S)){
			MoveValue(180);
			MoveCollision(mapChip, 180);
		}
		if (Input::GetInstance()->KeybordPush(DIK_D)){
			MoveValue(90);
			MoveCollision(mapChip, 90);
		}
	}
}

void Player::MoveValue(float vec)
{
	if (!moveTutorialFlag) { moveTutorialFlag = true; }
	pos.x += cos(((angle.y + vec) * PI) / -INVERSEVECTOR) * MOVESPEED;      // x座標を更新
	pos.z += sin(((angle.y + vec) * PI) / -INVERSEVECTOR) * MOVESPEED;      // z座標を更新

	mapPosValue.x += cos(((angle.y + vec) * PI) / -INVERSEVECTOR) * (MOVESPEED * 2);				   // x座標を更新
	mapPosValue.y += sin((((angle.y + vec) + INVERSEVECTOR) * PI) / -INVERSEVECTOR) * (MOVESPEED * 2); // y座標を更新

	target.x += cos(((angle.y + vec) * PI) / -INVERSEVECTOR) * MOVESPEED;      // x座標を更新
	target.z += sin(((angle.y + vec) * PI) / -INVERSEVECTOR) * MOVESPEED;      // z座標を更新
}

void Player::MoveCollision(MapChip* mapChip, float vec)
{
	//前側の当たり判定
	if(TouchWall(mapChip, CollisionDirection::FRONT ))
	{
		PushBack(VerticalOrHorizontal::VERTICAL, vec);
	}
	//左側の当たり判定
	if (TouchWall(mapChip, CollisionDirection::LEFT))
	{
		PushBack(VerticalOrHorizontal::HORIZONTAL, vec);
	}
	//後ろ側の当たり判定
	if (TouchWall(mapChip, CollisionDirection::BACK))
	{
		PushBack(VerticalOrHorizontal::VERTICAL, vec);
	}
	//右側の当たり判定
	if (TouchWall(mapChip, CollisionDirection::RIGHT))
	{
		PushBack(VerticalOrHorizontal::HORIZONTAL,vec);
	}
	isWalkShaking = true;
}

bool Player::TouchWall(MapChip* mapChip, CollisionDirection direction)
{
	//壁に触れているか
	float XR = 0.0f;
	float ZR = 0.0f;
	if (direction == CollisionDirection::FRONT) { ZR = R; }
	else if (direction == CollisionDirection::BACK) { ZR = -R; }
	else if (direction == CollisionDirection::RIGHT) { XR = R; }
	else if (direction == CollisionDirection::LEFT) { XR = -R; }
	if (mapChip->ArrayValue(pos.x + XR, pos.z + ZR) == 1 || mapChip->ArrayValue(pos.x + XR, pos.z + ZR) == 11){
		return true;
	}
	return false;
}

void Player::PushBack(VerticalOrHorizontal VerOrHor ,float vec)
{
	//押し戻し
	if (VerOrHor == VerticalOrHorizontal::VERTICAL)
	{
		pos.z += sin(((angle.y + vec + INVERSEVECTOR) * PI) / -INVERSEVECTOR) * MOVESPEED;      // z座標を更新
		mapPosValue.y += sin(((angle.y + vec) * PI) / -INVERSEVECTOR) * (MOVESPEED * 2);
	}
	else if (VerOrHor == VerticalOrHorizontal::HORIZONTAL)
	{
		pos.x += cos(((angle.y + vec + INVERSEVECTOR) * PI) / -INVERSEVECTOR) * MOVESPEED;      // x座標を更新
		mapPosValue.x += cos(((angle.y + vec + INVERSEVECTOR) * PI) / -INVERSEVECTOR) * (MOVESPEED * 2);
	}
}

void Player::WalkShaking()
{
	//シェイク値
	const float shakeValue = 0.05f;
	if (!shakeFlag)//シェイクしない
	{
		pos.y = 2.5;
	}
	else if (shakeFlag)//シェイクする 
	{
		if (isWalkShaking == true)
		{
			walkShakingTime++;
			if (walkShakingTime <= 8)
			{
				walkShaking += shakeValue;
			}
			else if (walkShakingTime >= 8 && walkShakingTime <= 16)
			{
				walkShaking -= shakeValue;
			}
			else if (walkShakingTime > 16)
			{
				walkShaking = 2.5f;
				walkShakingTime = 0;
				isWalkShaking = false;
			}
		}
		pos.y = 0.5f + walkShaking;
		target.y = targetY + walkShaking;
	}
}

void Player::View(bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3)
{
	const float INVERSEVECTOR = 180;
	//視点計算
	XMVECTOR v0 = { 0,0,-10, 0 };
	//angleラジアンだけy軸まわりに回転。半径は-100
	XMMATRIX  rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationX(XMConvertToRadians(angleX));
	rotM *= XMMatrixRotationY(XMConvertToRadians(angleY));
	XMVECTOR v = XMVector3TransformNormal(v0, rotM);
	XMVECTOR cameraPos = { pos.x,pos.y,pos.z };
	XMVECTOR v3 = cameraPos + v;
	XMFLOAT3 f = { v3.m128_f32[0], v3.m128_f32[1], v3.m128_f32[2] };
	pos = { cameraPos.m128_f32[0], cameraPos.m128_f32[1], cameraPos.m128_f32[2] };
	target = f;

	//視点を動かせない状態の時返す
	if (tutrialFlag == true || catchFlag == true || catchFlag2 == true || catchFlag3 == true) { return; }

	//視点を動かしたかどうか
	if (angleY != 0 && angleX != 0) {
		viewTutorialFlag = true;
	}

	//視点制限
	if (angleY < -INVERSEVECTOR) {
		angleY = INVERSEVECTOR;
	}
	else if (angleY > INVERSEVECTOR) {
		angleY = -INVERSEVECTOR;
	}
	angleX = std::clamp(angleX, -85.0f, 85.0f);

	//視点の移動
	angleY += Input::GetInstance()->GetMouseMove().lX * mouseViewSpeed;
	angleX -= Input::GetInstance()->GetMouseMove().lY * mouseViewSpeed;

}

void Player::AngleSearch()
{
	//見ている方向の角度
	angle.y = XMConvertToDegrees(atan2(pos.x - target.x, pos.z - target.z)) + 90;
}

void Player::TutorialAlpha(MapChip* mapChip)
{
	//ドアが開いたかどうか
	if (mapChip->GetGateOpenFlag()) {
		openTutorialFlag = true;
	}
	//チュートリアル関連
	const float alphaSpeed = 0.025f;
	if (moveTutorialFlag)
	{
		moveTutorial -= alphaSpeed;
	}
	if (viewTutorialFlag)
	{
		viewTutorial -= alphaSpeed;
	}
	if (openTutorialFlag)
	{
		openTutorial -= alphaSpeed;
	}
}

void Player::UiUpdate()
{
	//UIの位置セット
	const float mapLeftValue = 100.0f;
	const float mapTopValue = 650.0f;
	const float angleConvertValue = 135;
	const float enemyAngleAdjustValue = 8.0f;
	spritePlayerDot->SetPosition({ mapLeftValue + (MAPWALLSIZE * 10), mapTopValue + (MAPWALLSIZE * 11) });
	spritePlayerAngle->SetPosition({ mapLeftValue + (MAPWALLSIZE * 10) + enemyAngleAdjustValue, mapTopValue + (MAPWALLSIZE * 11) + enemyAngleAdjustValue });
	spritePlayerAngle->SetRotation(angle.y + angleConvertValue);
}

bool Player::AlartFlag(MapChip* mapChip, XMFLOAT3 enemyPos)
{
	//マップ内の座標の取得
	int mapX = int((enemyPos.x / 8) + ((MAPVALUE + 1) / 2));
	int mapY = int((enemyPos.z / 8) + ((MAPVALUE + 1) / 2));

	//近くに壁があるか
	const int ALARTMAXSEARCH = 5;
	for (int i = 1; i < ALARTMAXSEARCH; i++)
	{
		if (mapChip->GetArrayValue(mapX, mapY - i) == 1)
		{
			i = ALARTMAXSEARCH;
		}
		else if (mapChip->GetArrayValue(mapX, mapY - i) != 1 && mapChip->GetPlayerArrayValue(mapX, mapY - i) == 1)
		{
			return true;
		}
	}
	for (int i = 1; i < ALARTMAXSEARCH; i++)
	{
		if (mapChip->GetArrayValue(mapX, mapY + i) == 1)
		{
			i = ALARTMAXSEARCH;
		}
		else if (mapChip->GetArrayValue(mapX, mapY + i) != 1 && mapChip->GetPlayerArrayValue(mapX, mapY + i) == 1)
		{
			return true;
		}
	}
	for (int i = 1; i < ALARTMAXSEARCH; i++)
	{
		if (mapChip->GetArrayValue(mapX - 1, mapY) == 1)
		{
			i = ALARTMAXSEARCH;
		}
		else if (mapChip->GetArrayValue(mapX - i, mapY) != 1 && mapChip->GetPlayerArrayValue(mapX - i, mapY) == 1)
		{
			return true;
		}
	}
	for (int i = 1; i < ALARTMAXSEARCH; i++)
	{
		if (mapChip->GetArrayValue(mapX + 1, mapY) == 1)
		{
			i = ALARTMAXSEARCH;
		}
		else if (mapChip->GetArrayValue(mapX + i, mapY) != 1 && mapChip->GetPlayerArrayValue(mapX + i, mapY) == 1)
		{
			return true;
		}
	}
	return false;
}

bool Player::ShortCutFlag(MapChip* mapChip, XMFLOAT3 enemyPos, int X, int Z)
{
	//マップ内の座標の取得
	int mapX = int((enemyPos.x / 8) + ((MAPVALUE + 1) / 2));
	int mapY = int((enemyPos.z / 8) + ((MAPVALUE + 1) / 2));
	const int ALARTMAXSEARCH = 5;
	const int PLAYER = 1;
	const int WALL = 1;
	//近くに壁があるか
	for (int i = 1; i < ALARTMAXSEARCH; i++)
	{
		if (mapChip->GetArrayValue(mapX + (i * X), mapY + (i * Z)) == WALL)
		{
			i = ALARTMAXSEARCH;
		}
		else if (mapChip->GetArrayValue(mapX + (i * X), mapY + (i * Z)) != WALL && mapChip->GetPlayerArrayValue(mapX + (i * X), mapY + (i * Z)) == WALL)
		{
			return true;
		}
	}

	return false;
}

XMFLOAT2 Player::ShortCutValue(MapChip* mapChip, XMFLOAT3 enemyPos, float X, float Z, CHECKVECTOR vector)
{
	//何マス先を見るかの調整
	XMFLOAT2 plusValue = { 0,0 };
	float vectorX = pos.x - enemyPos.x;
	float vectorZ = pos.z - enemyPos.z;
	const int ALARTMAXSEARCH = 5;
	const int WALL = 1;

	for (int i = 1; i < ALARTMAXSEARCH + 1; i++)
	{
		if (mapChip->ArrayValue(pos.x + (WALLSIZE * (i * X)), pos.z + (WALLSIZE * (i * Z))) == WALL || i == ALARTMAXSEARCH)
		{
			if (vector == CHECKVECTOR::ZMINUS)
			{
				plusValue.x = 0;
				plusValue.y = -WALLSIZE * (i - 1);
			}
			else if (vector == CHECKVECTOR::ZPLUS)
			{
				plusValue.x = 0;
				plusValue.y = WALLSIZE * (i - 1);
			}
			else if (vector == CHECKVECTOR::XMINUS)
			{
				plusValue.y = 0;
				plusValue.x = -WALLSIZE * (i - 1);
			}
			else if (vector == CHECKVECTOR::XPLUS)
			{
				plusValue.y = 0;
				plusValue.x = WALLSIZE * (i - 1);
			}
		}
	}
	return plusValue;
}

XMFLOAT2 Player::GetShortCut(MapChip* mapChip, XMFLOAT3 enemyPos)
{
	//マップ内の座標の取得
	int mapX = int((enemyPos.x / 8) + ((MAPVALUE + 1) / 2));
	int mapY = int((enemyPos.z / 8) + ((MAPVALUE + 1) / 2));
	const int ALARTMAXSEARCH = 5;
	const int PLAYER = 1;
	const int WALL = 1;

	//近くに壁があるか
	if (ShortCutFlag(mapChip, enemyPos, 1, -1)) { return XMFLOAT2{ 0,0 }; }
	if (ShortCutFlag(mapChip, enemyPos, 1, +1)) { return XMFLOAT2{ 0,0 }; }
	if (ShortCutFlag(mapChip, enemyPos, -1, 1)) { return XMFLOAT2{ 0,0 }; }
	if (ShortCutFlag(mapChip, enemyPos, +1, 1)) { return XMFLOAT2{ 0,0 }; }

	//何マス先を見るかの調整
	XMFLOAT2 plusValue = { 0,0 };
	float vectorX = pos.x - enemyPos.x;
	float vectorZ = pos.z - enemyPos.z;
	if (-45 < angleY && angleY < 45)
	{
		plusValue = ShortCutValue(mapChip, enemyPos, 1.0f, -1.0f, CHECKVECTOR::ZMINUS);
	}
	else if (135 < angleY || angleY < -135)
	{
		plusValue = ShortCutValue(mapChip, enemyPos, 1.0f, 1.0f, CHECKVECTOR::ZPLUS);
	}
	else if (-135 < angleY && angleY < -45)
	{
		plusValue = ShortCutValue(mapChip, enemyPos, 1.0f, 1.0f, CHECKVECTOR::XPLUS);
	}
	else if (45 < angleY && angleY < 135)
	{
		plusValue = ShortCutValue(mapChip, enemyPos, -1.0f, 1.0f, CHECKVECTOR::XMINUS);
	}
	return plusValue;
}
