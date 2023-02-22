#include "Player.h"
#include "Input.h"
using namespace DirectX;

Player::~Player()
{
	safe_delete(spritePlayerDot);
	safe_delete(spritePlayerAngle);
	safe_delete(spriteMoveUI);
	safe_delete(spriteViewUI);
	safe_delete(spriteOpenUI);
}

void Player::Initialize()
{
	if (!Sprite::LoadTexture(3, L"Resources/PlayerDot.png")) {
		assert(0);
		return;
	}
	spritePlayerDot = Sprite::Create(3, miniMapPos);

	if (!Sprite::LoadTexture(6, L"Resources/angle.png")) {
		assert(0);
		return;
	}
	spritePlayerAngle = Sprite::Create(6, miniMapPos);

	if (!Sprite::LoadTexture(100, L"Resources/MoveUI.png")) {
		assert(0);
		return;
	}
	spriteMoveUI = Sprite::Create(100, {0,0});

	if (!Sprite::LoadTexture(101, L"Resources/ViewUI.png")) {
		assert(0);
		return;
	}
	spriteViewUI = Sprite::Create(101, {0,0});

	if (!Sprite::LoadTexture(102, L"Resources/OpenUI.png")) {
		assert(0);
		return;
	}
	spriteOpenUI = Sprite::Create(102, { 0,0 });
}

void Player::InitializeValue()
{
	miniMapPos = { 100 + (16.0f * 11),650 + (16.0f * 11) };//ミニマップ初期値
	pos = { -4.0f,0.0f,4.0f };//プレイヤーの位置
	mapPosValue = {0,0};//マップの座標
	r = 0.5;//プレイヤーの半径
	moveSpeed = 0.18f;//歩きの速度
	viewSpeed = 4.0f;//視点の速さ
	target = { 0,0.0f,0 };//注視点
	targetY = 0;//揺れの調整
	angle = { 0,0,0 };//歩く方向
	walkShaking = 2.5;//歩きの揺れる値
	isWalkShaking = false;//歩きの揺れのフラグ
	walkShakingTime = 0;//歩きの揺れのタイム
	angleX = 0; //カメラX軸
	angleY = 0; //カメラY軸

}

void Player::Update(MapChip *mapChip,bool tutrialFlag,bool catchFlag, bool catchFlag2, bool catchFlag3)
{
	if (mapChip->GetGateOpenFlag())
	{
		openTutorialFlag = true;
	}
	AngleSearch();//プレイヤーの向きの算出
	if (tutrialFlag == false && catchFlag == false && catchFlag2 == false && catchFlag3 == false)
	{
		Move(mapChip);//移動
	}
	WalkShaking();//歩きの揺れ
	View(tutrialFlag,catchFlag, catchFlag2, catchFlag3);//視点制御

	//スプライト関連のポジションとアングルセット
	spritePlayerDot->SetPosition({ 100 + (16.0f * 10), 650 + (16.0f * 11) });
	spritePlayerAngle->SetPosition({ 100 + (16.0f * 10) + 8, 650 + (16.0f * 11) + 8 });
	spritePlayerAngle->SetRotation(angle.y + 135);
}

void Player::Draw()
{
}

void Player::DrawSprite()
{
	//プレイヤーのミニマップの情報
	spritePlayerAngle->Draw(1.0f);
	spritePlayerDot->Draw(1.0f);
	if (moveTutorialFlag)
	{
		moveTutorial -= 0.05f;
	}
	if (viewTutorialFlag)
	{
		viewTutorial -= 0.05f;
	}
	if (openTutorialFlag)
	{
		openTutorial -= 0.05f;
	}
	spriteViewUI->Draw(viewTutorial);
	spriteMoveUI->Draw(moveTutorial);
	spriteOpenUI->Draw(openTutorial);

}

void Player::Move(MapChip *mapChip)
{
	float r = 0.5f;//半径
	float corner = 0.35f;//角までの距離
	if (mapChip->ArrayValue(pos.x - corner, pos.z + corner) == 1 || mapChip->ArrayValue(pos.x - corner, pos.z + corner) == 11)
	{
		pos.x += cos((45 * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((45 * 3.14f) / -180) * moveSpeed;      // z座標を更新
		mapPosValue.x += cos((45 * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((45 * 3.14f) / -180) * (moveSpeed * 2);
	}
	else if (mapChip->ArrayValue(pos.x + corner, pos.z + corner) == 1|| mapChip->ArrayValue(pos.x + corner, pos.z + corner) == 11)
	{
		pos.x += cos((135 * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((135 * 3.14f) / -180) * moveSpeed;      // z座標を更新
		mapPosValue.x += cos((135 * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((135 * 3.14f) / -180) * (moveSpeed * 2);

	}
	else if (mapChip->ArrayValue(pos.x - corner, pos.z - corner) == 1|| mapChip->ArrayValue(pos.x - corner, pos.z - corner) == 11)
	{
		pos.x += cos((-45 * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((-45 * 3.14f) / -180) * moveSpeed;      // z座標を更新
		mapPosValue.x += cos((-45 * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((-45 * 3.14f) / -180) * (moveSpeed * 2);
	}
	else if (mapChip->ArrayValue(pos.x + corner, pos.z - corner) == 1|| mapChip->ArrayValue(pos.x + corner, pos.z - corner) == 11)
	{
		pos.x += cos((225 * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((225 * 3.14f) / -180) * moveSpeed;      // z座標を更新
		mapPosValue.x += cos((225 * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((225 * 3.14f) / -180) * (moveSpeed * 2);
	}

	if (Input::GetInstance()->KeybordPush(DIK_W))
	{
		moveTutorialFlag = true;
		pos.x += cos((angle.y * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((angle.y * 3.14f) / -180) * moveSpeed;      // z座標を更新

		mapPosValue.x += cos(((angle.y + 180 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);

		target.x += cos((angle.y * 3.14f) / -180) * moveSpeed;      // x座標を更新
		target.z += sin((angle.y * 3.14f) / -180) * moveSpeed;      // z座標を更新
		//上
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1|| mapChip->ArrayValue(pos.x, pos.z + r) == 11)
		{
			pos.z += sin(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // z座標を更新

			mapPosValue.y += sin(((angle.y) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//左
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1|| mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // x座標を更新

			mapPosValue.x += cos(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//下
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1|| mapChip->ArrayValue(pos.x, pos.z - r) == 11)
		{
			pos.z += sin(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // z座標を更新
			mapPosValue.y += sin(((angle.y) * 3.14f) / -180) * (moveSpeed * 2);
			
		}
		//右
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1|| mapChip->ArrayValue(pos.x + r, pos.z) == 11)
		{
			pos.x += cos(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // x座標を更新

			mapPosValue.x += cos(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_A))
	{
		moveTutorialFlag = true;
		pos.x += cos(((angle.y - 90) * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin(((angle.y - 90) * 3.14f) / -180) * moveSpeed;      // z座標を更新

		mapPosValue.x += cos(((angle.y + 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin(((angle.y + 90) * 3.14f) / -180) * (moveSpeed * 2);

		target.x += cos(((angle.y - 90) * 3.14f) / -180) * moveSpeed;      // x座標を更新
		target.z += sin(((angle.y - 90) * 3.14f) / -180) * moveSpeed;      // z座標を更新
		//上
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1|| mapChip->ArrayValue(pos.x, pos.z + r) == 11)
		{
			pos.z += sin(((angle.y - 90 + 180) * 3.14f) / -180) * moveSpeed;      // z座標を更新
			mapPosValue.y += sin(((angle.y + 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
			
		}
		//左
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1|| mapChip->ArrayValue(pos.x - r, pos.z) == 11)
		{
			pos.x += cos(((angle.y - 90 + 180) * 3.14f) / -180) * moveSpeed;      // x座標を更新

			mapPosValue.x += cos(((angle.y + 90 + 180 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//下
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1|| mapChip->ArrayValue(pos.x, pos.z - r) == 11)
		{
			pos.z += sin(((angle.y - 90 + 180) * 3.14f) / -180) * moveSpeed;      // z座標を更新

			mapPosValue.y += sin(((angle.y + 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//右
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1|| mapChip->ArrayValue(pos.x + r, pos.z) == 11)
		{
			pos.x += cos(((angle.y - 90 + 180) * 3.14f) / -180) * moveSpeed;      // x座標を更新

			mapPosValue.x += cos(((angle.y + 90 + 180 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_S))
	{
		moveTutorialFlag = true;
		pos.x += cos(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // z座標を更新
		mapPosValue.x += cos(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((angle.y * 3.14f) / -180) * (moveSpeed * 2);

		target.x -= cos((angle.y * 3.14f) / -180) * moveSpeed;      // x座標を更新
		target.z -= sin((angle.y * 3.14f) / -180) * moveSpeed;      // z座標を更新
		//上
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1|| mapChip->ArrayValue(pos.x, pos.z + r) == 11)
		{
			pos.z += sin(((angle.y) * 3.14f) / -180) * moveSpeed;      // z座標を更新
			mapPosValue.y += sin(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//左
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1|| mapChip->ArrayValue(pos.x - r, pos.z) == 11)
		{
			pos.x += cos(((angle.y) * 3.14f) / -180) * moveSpeed;      // x座標を更新
			mapPosValue.x += cos(((angle.y + 360) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//下
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1|| mapChip->ArrayValue(pos.x, pos.z - r) == 11)
		{
			pos.z += sin(((angle.y) * 3.14f) / -180) * moveSpeed;      // z座標を更新
			mapPosValue.y += sin(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//右
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1|| mapChip->ArrayValue(pos.x + r, pos.z) == 11)
		{
			pos.x += cos(((angle.y) * 3.14f) / -180) * moveSpeed;      // x座標を更新
			mapPosValue.x += cos(((angle.y + 360) * 3.14f) / -180) * (moveSpeed * 2);
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_D))
	{
		moveTutorialFlag = true;
		pos.x += cos(((angle.y + 90) * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin(((angle.y + 90) * 3.14f) / -180) * moveSpeed;      // z座標を更新
		mapPosValue.x += cos(((angle.y - 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin(((angle.y - 90) * 3.14f) / -180) * (moveSpeed * 2);

		target.x += cos(((angle.y + 90) * 3.14f) / -180) * moveSpeed;      // x座標を更新
		target.z += sin(((angle.y + 90) * 3.14f) / -180) * moveSpeed;      // z座標を更新
		//上
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1 || mapChip->ArrayValue(pos.x, pos.z + r) == 11)
		{
			pos.z += sin(((angle.y + 90 + 180) * 3.14f) / -180) * moveSpeed;      // z座標を更新
			mapPosValue.y += sin(((angle.y - 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//左
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1 || mapChip->ArrayValue(pos.x - r, pos.z) == 11)
		{
			pos.x += cos(((angle.y + 90 + 180) * 3.14f) / -180) * moveSpeed;      // x座標を更新
			mapPosValue.x += cos(((angle.y - 90 + 180 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//下
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1 || mapChip->ArrayValue(pos.x, pos.z - r) == 11)
		{
			pos.z += sin(((angle.y + 90 + 180) * 3.14f) / -180) * moveSpeed;      // z座標を更新
			mapPosValue.y += sin(((angle.y - 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//右
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1 || mapChip->ArrayValue(pos.x + r, pos.z) == 11)
		{
			pos.x += cos(((angle.y + 90 + 180) * 3.14f) / -180) * moveSpeed;      // x座標を更新
			mapPosValue.x += cos(((angle.y - 90 + 180 + 180) * 3.14f) / -180) * (moveSpeed*2);
		}
		isWalkShaking = true;
	}
}

void Player::WalkShaking()
{
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
				walkShaking += 0.05f;
			}
			else if (walkShakingTime >= 8 && walkShakingTime <= 16)
			{
				walkShaking -= 0.05f;
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

void Player::View(bool tutrialFlag, bool catchFlag,bool catchFlag2, bool catchFlag3)
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
	if (tutrialFlag == false&&catchFlag==false && catchFlag2 == false && catchFlag3 == false)
	{
		if (angleY != 0&& angleX != 0)
		{
			viewTutorialFlag = true;
		}
		if (angleX >= 85)
		{
			angleX = 85;
		}
		else if (Input::GetInstance()->KeybordPush(DIK_UP))
		{
			angleX += viewSpeed;
		}
		if (angleX <= -85)
		{
			angleX = -85;
		}
		else if (Input::GetInstance()->KeybordPush(DIK_DOWN))
		{
			angleX -= viewSpeed;
		}
		if (Input::GetInstance()->KeybordPush(DIK_LEFT))
		{
			angleY -= viewSpeed;
		}
		if (Input::GetInstance()->KeybordPush(DIK_RIGHT))
		{
			angleY += viewSpeed;
		}
		if (angleY < -180)
		{
			angleY = 180;
		}
		if (angleY > 180)
		{
			angleY = -180;
		}
		angleY += Input::GetInstance()->GetMouseMove().lX * mouseViewSpeed;
		angleX -= Input::GetInstance()->GetMouseMove().lY * mouseViewSpeed;
	}
}

void Player::AngleSearch()
{
	angle.y = XMConvertToDegrees(atan2(pos.x - target.x, pos.z - target.z)) + 90;
}

XMFLOAT2 Player::GetShortCut(MapChip* mapChip, XMFLOAT3 enemyPos)
{
	int mapX = int((enemyPos.x / 8) + ((21 + 1) / 2));
	int mapY = int((enemyPos.z / 8) + ((21 + 1) / 2));
	for (int i = 1; i < 5; i++)
	{
		if (mapChip->GetArrayValue(mapX, mapY - i) == 1)
		{
			i = 5;
		}
		else if (mapChip->GetArrayValue(mapX, mapY - i) != 1 && mapChip->GetPlayerArrayValue(mapX, mapY - i) == 1)
		{
			return XMFLOAT2{ 0,0 };
		}
	}
	for (int i = 1; i < 5; i++)
	{
		if (mapChip->GetArrayValue(mapX, mapY + i) == 1)
		{
			i = 5;
		}
		else if (mapChip->GetArrayValue(mapX, mapY + i) != 1 && mapChip->GetPlayerArrayValue(mapX, mapY + i) == 1)
		{
			return XMFLOAT2{ 0,0 };
		}
	}
	for (int i = 1; i < 5; i++)
	{
		if (mapChip->GetArrayValue(mapX - 1, mapY) == 1)
		{
			i = 5;
		}
		else if (mapChip->GetArrayValue(mapX - i, mapY) != 1 && mapChip->GetPlayerArrayValue(mapX - i, mapY) == 1)
		{
			return XMFLOAT2{ 0,0 };
		}
	}
	for (int i = 1; i < 5; i++)
	{
		if (mapChip->GetArrayValue(mapX + 1, mapY) == 1)
		{
			i = 5;
		}
		else if (mapChip->GetArrayValue(mapX + i, mapY) != 1 && mapChip->GetPlayerArrayValue(mapX + i, mapY) == 1)
		{
			return XMFLOAT2{ 0,0 };
		}
	}
	


	XMFLOAT2 plusValue = {0,0};
	float vectorX = pos.x - enemyPos.x;
	float vectorZ = pos.z - enemyPos.z;
 	if (-45 < angleY && angleY < 45)
	{
		for (int i = 1; i < 6; i++)
		{
			if (mapChip->ArrayValue(pos.x ,pos.z + (-8*i)) == 1 || i== 5)
			{
				plusValue.x = 0;
				plusValue.y = -8.0f * (i - 1);
				return plusValue;
			}
		}
	}
	else if (135 < angleY || angleY < -135)
	{
		for (int i = 1; i < 6; i++)
		{
			if (mapChip->ArrayValue(pos.x, pos.z + (8 * i)) == 1 || i == 5)
			{
				plusValue.x = 0;
				plusValue.y = 8.0f * (i - 1);
				return plusValue;
			}
		}
	}
	else if (-135 < angleY && angleY < -45)
	{
		for (int i = 1; i < 6; i++)
		{
			if (mapChip->ArrayValue(pos.x + (8 * i), pos.z) == 1 || i == 5)
			{
				plusValue.y = 0;
				plusValue.x = 8.0f * (i - 1);
				return plusValue;
			}
		}
	}
	else if (45 < angleY && angleY < 135)
	{
		for (int i = 1; i < 6; i++)
		{
			if (mapChip->ArrayValue(pos.x + (-8 * i), pos.z) == 1 || i == 5)
			{
				plusValue.y = 0;
				plusValue.x = -8.0f * (i-1);
				return plusValue;
			}
		}
	}

	return plusValue;
}
