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
	//スプライトの作成
	spritePlayerDot = std::unique_ptr<Sprite>(Sprite::Create(3, miniMapPos));	//プレイヤーの点
	spritePlayerAngle = std::unique_ptr<Sprite>(Sprite::Create(6, miniMapPos));	//プレイヤーの向いてる方向
	spriteMoveUI = std::unique_ptr<Sprite>(Sprite::Create(100, { 0,0 }));		//チュートリアルMoveのUI
	spriteViewUI = std::unique_ptr<Sprite>(Sprite::Create(101, { 0,0 }));		//チュートリアルViewのUI
	spriteOpenUI = std::unique_ptr<Sprite>(Sprite::Create(102, { 0,0 }));		//チュートリアルOpenのUI
}

void Player::InitializeValue()
{
	miniMapPos = { 100 + (MAPWALLSIZE * 11),650 + (MAPWALLSIZE * 11) };	//ミニマップ初期値
	pos = { -4.0f,0.0f,4.0f };											//プレイヤーの位置
	mapPosValue = { 0,0 };												//マップの座標
	viewSpeed = 4.0f;													//視点の速さ
	target = { 0,0.0f,0 };												//注視点
	targetY = 0;														//揺れの調整
	angle = { 0,0,0 };													//歩く方向
	walkShaking = 2.5;													//歩きの揺れる値
	isWalkShaking = false;												//歩きの揺れのフラグ
	walkShakingTime = 0;												//歩きの揺れのタイム
	angleX = 0;															//カメラX軸
	angleY = 0;															//カメラY軸

}

void Player::Update(MapChip* mapChip, bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3)
{
	//チュートリアルの演出
	TutorialAlpha(mapChip);
	
	//プレイヤーの向きの算出
	AngleSearch();

	//移動
	Move(mapChip,tutrialFlag,catchFlag,catchFlag2,catchFlag3);

	//歩きの揺れ
	WalkShaking();

	//視点
	View(tutrialFlag, catchFlag, catchFlag2, catchFlag3);

	//スプライト関連のポジションとアングルセット
	UiUpdate();
}

void Player::DrawSprite()
{
	//マップの描画
	MapDraw();

	//UIの描画
	UiDraw();
}

void Player::Move(MapChip* mapChip, bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3)
{	
	//移動
	if (MoveStopFlag(tutrialFlag, catchFlag, catchFlag2, catchFlag3)){
		//前
		if (Input::GetInstance()->KeybordPush(DIK_W)){
			MoveUpdate(mapChip, FRONT);
		}
		//左
		if (Input::GetInstance()->KeybordPush(DIK_A)){
			MoveUpdate(mapChip, LEFT);
		}
		//後
		if (Input::GetInstance()->KeybordPush(DIK_S)){
			MoveUpdate(mapChip, BACK);
		}
		//右
		if (Input::GetInstance()->KeybordPush(DIK_D)){
			MoveUpdate(mapChip, RIGHT);
		}
	}
}

bool Player::MoveStopFlag(bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3)
{
	//演出に入っていないか
	if (tutrialFlag == false && catchFlag == false && catchFlag2 == false && catchFlag3 == false){
		return true;
	}
	return false;
}

void Player::MoveValue(float vec)
{
	//チュートリアル終了したか
	if (!moveTutorialFlag) { moveTutorialFlag = true; }

	//位置移動
	pos.x += cos(((angle.y + vec) * PI) / -INVERSEVECTOR) * MOVESPEED;      // x座標を更新
	pos.z += sin(((angle.y + vec) * PI) / -INVERSEVECTOR) * MOVESPEED;      // z座標を更新

	//マップの位置移動
	mapPosValue.x += cos(((angle.y + vec) * PI) / -INVERSEVECTOR) * (MOVESPEED * 2);				   // x座標を更新
	mapPosValue.y += sin((((angle.y + vec) + INVERSEVECTOR) * PI) / -INVERSEVECTOR) * (MOVESPEED * 2); // y座標を更新

	//視点移動
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

void Player::MoveUpdate(MapChip* mapChip, float vec)
{
	//移動計算
	MoveValue(vec);

	//当たり判定
	MoveCollision(mapChip, vec);
}

bool Player::TouchWall(MapChip* mapChip, CollisionDirection direction)
{
	//壁に触れているか
	float XR = 0.0f;
	float ZR = 0.0f;
	
	//半径rの値入れ
	if (direction == CollisionDirection::FRONT) { ZR = R; }
	else if (direction == CollisionDirection::BACK) { ZR = -R; }
	else if (direction == CollisionDirection::RIGHT) { XR = R; }
	else if (direction == CollisionDirection::LEFT) { XR = -R; }

	//当たっているかどうかの判別
	if (mapChip->ArrayValue(pos.x + XR, pos.z + ZR) == 1 || mapChip->ArrayValue(pos.x + XR, pos.z + ZR) == 11){
		return true;
	}
	return false;
}

void Player::PushBack(VerticalOrHorizontal VerOrHor ,float vec)
{
	//押し戻し縦
	if (VerOrHor == VerticalOrHorizontal::VERTICAL){
		pos.z += sin(((angle.y + vec + INVERSEVECTOR) * PI) / -INVERSEVECTOR) * MOVESPEED;      // z座標を更新
		mapPosValue.y += sin(((angle.y + vec) * PI) / -INVERSEVECTOR) * (MOVESPEED * 2);
	}

	//押し戻し横
	else if (VerOrHor == VerticalOrHorizontal::HORIZONTAL)
	{
		pos.x += cos(((angle.y + vec + INVERSEVECTOR) * PI) / -INVERSEVECTOR) * MOVESPEED;      // x座標を更新
		mapPosValue.x += cos(((angle.y + vec + INVERSEVECTOR) * PI) / -INVERSEVECTOR) * (MOVESPEED * 2);
	}
}

void Player::WalkShaking()
{
	//シェイクしない
	if (!shakeFlag){
		pos.y = 2.5;
	}
	//シェイクする
	else if (shakeFlag) {
		ShaikingMove();
	}
}

void Player::ShaikingMove()
{
	//シェイク値
	const float shakeValue = 0.05f;
	if (isWalkShaking == true)
	{
		walkShakingTime++;
		if (walkShakingTime <= 8){
			walkShaking += shakeValue;
		}
		else if (walkShakingTime >= 8 && walkShakingTime <= 16){
			walkShaking -= shakeValue;
		}
		else if (walkShakingTime > 16){
			walkShaking = 2.5f;
			walkShakingTime = 0;
			isWalkShaking = false;
		}
	}
	pos.y = 0.5f + walkShaking;
	target.y = targetY + walkShaking;
}

void Player::View(bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3)
{	
	//位置座標と注視点座標の計算
	ViewCalculation();

	//視点を動かせない状態の時返す
	if (ViewFixedFlag(tutrialFlag, catchFlag, catchFlag2, catchFlag3)) { return; }

	//視点を動かしたかどうか
	if (angleY != 0 && angleX != 0) {
		viewTutorialFlag = true;
	}

	//視点の移動
	angleY += Input::GetInstance()->GetMouseMove().lX * mouseViewSpeed;
	angleX -= Input::GetInstance()->GetMouseMove().lY * mouseViewSpeed;
}

void Player::ViewCalculation()
{
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

	//視点制限
	if (angleY < -INVERSEVECTOR) {
		angleY = INVERSEVECTOR;
	}
	else if (angleY > INVERSEVECTOR) {
		angleY = -INVERSEVECTOR;
	}
	angleX = std::clamp(angleX, -85.0f, 85.0f);
}

bool Player::ViewFixedFlag(bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3)
{
	if (tutrialFlag == true || catchFlag == true || catchFlag2 == true || catchFlag3 == true)
	{
		return true;
	}
	return false;
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
	if (moveTutorialFlag){
		moveTutorial -= alphaSpeed;
	}
	if (viewTutorialFlag){
		viewTutorial -= alphaSpeed;
	}
	if (openTutorialFlag){
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

	//プレイヤーのスプライトの関連
	spritePlayerDot->SetPosition({ mapLeftValue + (MAPWALLSIZE * 10), mapTopValue + (MAPWALLSIZE * 11) });
	spritePlayerAngle->SetPosition({ mapLeftValue + (MAPWALLSIZE * 10) + enemyAngleAdjustValue, mapTopValue + (MAPWALLSIZE * 11) + enemyAngleAdjustValue });
	spritePlayerAngle->SetRotation(angle.y + angleConvertValue);
}

void Player::MapDraw()
{
	//プレイヤーのミニマップの情報
	spritePlayerAngle->Draw(1.0f);
	spritePlayerDot->Draw(1.0f);
}

void Player::UiDraw()
{
	//チュートリアルの描画
	spriteViewUI->Draw(viewTutorial);
	spriteMoveUI->Draw(moveTutorial);
	spriteOpenUI->Draw(openTutorial);
}

bool Player::AlartCalculation(MapChip* mapChip, int mapX, int mapY, int X, int Z)
{
	//近くに壁があるか
	for (int i = 1; i < ALARTMAXSEARCH; i++) {
		if (SarchWall(mapChip, mapX, mapY, X, Z, i)) {
			i = ALARTMAXSEARCH;
		}
		if (SarchEnemy(mapChip, mapX, mapY, X, Z, i)) {
			return true;
		}
	}
	return false;
}

bool Player::AlartFlag(MapChip* mapChip, XMFLOAT3 enemyPos)
{
	//マップ内の座標の取得
	int mapX = int((enemyPos.x / 8) + ((MAPVALUE + 1) / 2));
	int mapY = int((enemyPos.z / 8) + ((MAPVALUE + 1) / 2));

	//近くに壁があるか
	if (AlartCalculation(mapChip, mapX, mapY, 1, -1)) {return true;}
	if (AlartCalculation(mapChip, mapX, mapY, 1, +1)) {return true;}
	if (AlartCalculation(mapChip, mapX, mapY, -1, 1)) {return true;}
	if (AlartCalculation(mapChip, mapX, mapY, +1, 1)) {return true;}
	
	return false;
}

int Player::ShortCutFlag(MapChip* mapChip, XMFLOAT3 enemyPos, int X, int Z)
{
	//マップ内の座標の取得
	int mapX = int((enemyPos.x / 8) + ((MAPVALUE + 1) / 2));
	int mapY = int((enemyPos.z / 8) + ((MAPVALUE + 1) / 2));
	
	//近くに壁があるか
	for (int i = 1; i < ALARTMAXSEARCH; i++){
		if (SarchWall(mapChip, mapX, mapY, X, Z, i)){
			return i;
		}
		if (SarchEnemy(mapChip, mapX, mapY, X, Z, i)){
			return i;
		}	
	}
	return 0;
}

bool Player::SarchWall(MapChip* mapChip, int mapX, int mapY, int X, int Z, int count)
{
	//壁の位置
	if (mapChip->GetArrayValue(mapX + (count * X), mapY + (count * Z)) == WALL) {
		return true;
	}
	return false;
}

bool Player::SarchEnemy(MapChip* mapChip, int mapX, int mapY, int X, int Z, int count)
{
	//敵の位置
	if (mapChip->GetArrayValue(mapX + (count * X), mapY + (count * Z)) != WALL && mapChip->GetPlayerArrayValue(mapX + (count * X), mapY + (count * Z)) == WALL) {
		return true;
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

	//どれだけ先を見るかの判定
	for (int i = 1; i < ALARTMAXSEARCH + 1; i++){
		if (mapChip->ArrayValue(pos.x + (WALLSIZE * (i * X)), pos.z + (WALLSIZE * (i * Z))) == WALL || i == ALARTMAXSEARCH){
			if (vector == CHECKVECTOR::ZMINUS){
				plusValue.x = 0;
				plusValue.y = -WALLSIZE * (i - 1);
			}
			else if (vector == CHECKVECTOR::ZPLUS){
				plusValue.x = 0;
				plusValue.y = WALLSIZE * (i - 1);
			}
			else if (vector == CHECKVECTOR::XMINUS){
				plusValue.y = 0;
				plusValue.x = -WALLSIZE * (i - 1);
			}
			else if (vector == CHECKVECTOR::XPLUS){
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
	if (VIEWFRONT - VIEWARIA < angleY && angleY < VIEWFRONT + VIEWARIA){
		plusValue = ShortCutValue(mapChip, enemyPos, 1.0f, -1.0f, CHECKVECTOR::ZMINUS);
	}
	else if (VIEWBACKPLUS - VIEWARIA < angleY || angleY < VIEWBACKMINUS + VIEWARIA){
		plusValue = ShortCutValue(mapChip, enemyPos, 1.0f, 1.0f, CHECKVECTOR::ZPLUS);
	}
	else if (VIEWLEFT - VIEWARIA < angleY && angleY < VIEWLEFT + VIEWARIA){
		plusValue = ShortCutValue(mapChip, enemyPos, 1.0f, 1.0f, CHECKVECTOR::XPLUS);
	}
	else if (VIEWRIGHT - VIEWARIA < angleY && angleY < VIEWRIGHT + VIEWARIA){
		plusValue = ShortCutValue(mapChip, enemyPos, -1.0f, 1.0f, CHECKVECTOR::XMINUS);
	}
	return plusValue;
}