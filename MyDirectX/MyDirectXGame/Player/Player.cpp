#include "Player.h"
#include "Input.h"
using namespace DirectX;

Player::~Player()
{
	safe_delete(spritePlayerDot);
	safe_delete(spritePlayerAngle);
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
}

void Player::InitializeValue()
{
	miniMapPos = { 100 + (16.0f * 10),650 + (16.0f * 8) };
	pos = { 4.0f,0.0f,4.0f };//プレイヤーの位置
	mapPosValue = {0,0};
	r = 0.5;//プレイヤーの半径
	moveSpeed = 0.25f;//歩きの速度
	viewSpeed = 4.0f;//視点の速さ
	target = { 0,0.0f,0 };//注視点
	targetY = 0;//揺れの調整
	angle = { 0,0,0 };//歩く方向
	walkShaking = 2.5;//歩きの揺れる値
	isWalkShaking = false;//歩きの揺れのフラグ
	walkShakingTime = 0;//歩きの揺れのタイム
	angleX = 0; //カメラX軸
	angleY = 90; //カメラY軸
}

void Player::Update(MapChip *mapChip,bool tutrialFlag)
{
	AngleSearch();//プレイヤーの向きの算出
	if (tutrialFlag == false)
	{
		Move(mapChip);//移動
	}
	WalkShaking();//歩きの揺れ
	View(tutrialFlag);//視点制御

	spritePlayerDot->SetPosition({ 100 + (16.0f * 9), 634 + (16.0f * 12) });
	spritePlayerAngle->SetPosition({ 100 + (16.0f * 9) + 8, 634 + (16.0f * 12) + 8 });
	spritePlayerAngle->SetRotation(angle.y + 135);
}

void Player::Draw()
{
}

void Player::DrawSprite()
{
	spritePlayerAngle->Draw();
	spritePlayerDot->Draw();
}

void Player::Move(MapChip *mapChip)
{
	float r = 0.5f;
	float cornerR = 0.35f;
	if (mapChip->ArrayValue(pos.x - cornerR, pos.z + cornerR) == 1)
	{
		pos.x += cos((45 * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((45 * 3.14f) / -180) * moveSpeed;      // z座標を更新
		mapPosValue.x += cos((45 * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((45 * 3.14f) / -180) * (moveSpeed * 2);
	}
	else if (mapChip->ArrayValue(pos.x + cornerR, pos.z + cornerR) == 1)
	{
		pos.x += cos((135 * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((135 * 3.14f) / -180) * moveSpeed;      // z座標を更新
		mapPosValue.x += cos((135 * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((135 * 3.14f) / -180) * (moveSpeed * 2);

	}
	else if (mapChip->ArrayValue(pos.x - cornerR, pos.z - cornerR) == 1)
	{
		pos.x += cos((-45 * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((-45 * 3.14f) / -180) * moveSpeed;      // z座標を更新
		mapPosValue.x += cos((-45 * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((-45 * 3.14f) / -180) * (moveSpeed * 2);
	}
	else if (mapChip->ArrayValue(pos.x + cornerR, pos.z - cornerR) == 1)
	{
		pos.x += cos((225 * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((225 * 3.14f) / -180) * moveSpeed;      // z座標を更新
		mapPosValue.x += cos((225 * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((225 * 3.14f) / -180) * (moveSpeed * 2);
	}

	if (Input::GetInstance()->KeybordPush(DIK_W))
	{
		pos.x += cos((angle.y * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((angle.y * 3.14f) / -180) * moveSpeed;      // z座標を更新

		mapPosValue.x += cos(((angle.y + 180 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);

		target.x += cos((angle.y * 3.14f) / -180) * moveSpeed;      // x座標を更新
		target.z += sin((angle.y * 3.14f) / -180) * moveSpeed;      // z座標を更新
		//上
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // z座標を更新

			mapPosValue.y += sin(((angle.y) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//左
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // x座標を更新

			mapPosValue.x += cos(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//下
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // z座標を更新
			mapPosValue.y += sin(((angle.y) * 3.14f) / -180) * (moveSpeed * 2);
			
		}
		//右
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // x座標を更新

			mapPosValue.x += cos(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_A))
	{
		pos.x += cos(((angle.y - 90) * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin(((angle.y - 90) * 3.14f) / -180) * moveSpeed;      // z座標を更新

		mapPosValue.x += cos(((angle.y + 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin(((angle.y + 90) * 3.14f) / -180) * (moveSpeed * 2);

		target.x += cos(((angle.y - 90) * 3.14f) / -180) * moveSpeed;      // x座標を更新
		target.z += sin(((angle.y - 90) * 3.14f) / -180) * moveSpeed;      // z座標を更新
		//上
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y - 90 + 180) * 3.14f) / -180) * moveSpeed;      // z座標を更新
			mapPosValue.y += sin(((angle.y + 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
			
		}
		//左
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y - 90 + 180) * 3.14f) / -180) * moveSpeed;      // x座標を更新

			mapPosValue.x += cos(((angle.y + 90 + 180 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//下
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y - 90 + 180) * 3.14f) / -180) * moveSpeed;      // z座標を更新

			mapPosValue.y += sin(((angle.y + 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//右
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y - 90 + 180) * 3.14f) / -180) * moveSpeed;      // x座標を更新

			mapPosValue.x += cos(((angle.y + 90 + 180 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_S))
	{
		pos.x += cos(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // z座標を更新
		mapPosValue.x += cos(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((angle.y * 3.14f) / -180) * (moveSpeed * 2);

		target.x -= cos((angle.y * 3.14f) / -180) * moveSpeed;      // x座標を更新
		target.z -= sin((angle.y * 3.14f) / -180) * moveSpeed;      // z座標を更新
		//上
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y) * 3.14f) / -180) * moveSpeed;      // z座標を更新
			mapPosValue.y += sin(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//左
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y) * 3.14f) / -180) * moveSpeed;      // x座標を更新
			mapPosValue.x += cos(((angle.y + 360) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//下
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y) * 3.14f) / -180) * moveSpeed;      // z座標を更新
			mapPosValue.y += sin(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//右
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y) * 3.14f) / -180) * moveSpeed;      // x座標を更新
			mapPosValue.x += cos(((angle.y + 360) * 3.14f) / -180) * (moveSpeed * 2);
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_D))
	{
		pos.x += cos(((angle.y + 90) * 3.14f) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin(((angle.y + 90) * 3.14f) / -180) * moveSpeed;      // z座標を更新
		mapPosValue.x += cos(((angle.y - 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin(((angle.y - 90) * 3.14f) / -180) * (moveSpeed * 2);

		target.x += cos(((angle.y + 90) * 3.14f) / -180) * moveSpeed;      // x座標を更新
		target.z += sin(((angle.y + 90) * 3.14f) / -180) * moveSpeed;      // z座標を更新
		//上
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y + 90 + 180) * 3.14f) / -180) * moveSpeed;      // z座標を更新
			mapPosValue.y += sin(((angle.y - 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//左
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 90 + 180) * 3.14f) / -180) * moveSpeed;      // x座標を更新
			mapPosValue.x += cos(((angle.y - 90 + 180 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//下
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y + 90 + 180) * 3.14f) / -180) * moveSpeed;      // z座標を更新
			mapPosValue.y += sin(((angle.y - 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//右
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 90 + 180) * 3.14f) / -180) * moveSpeed;      // x座標を更新
			mapPosValue.x += cos(((angle.y - 90 + 180 + 180) * 3.14f) / -180) * (moveSpeed*2);
		}
		isWalkShaking = true;
	}
}

void Player::WalkShaking()
{
	if (!shakeFlag)
	{
		pos.y = 2.5;
	}
	else if (shakeFlag) 
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
		pos.y = walkShaking;
		target.y = targetY + walkShaking;
	}
}

void Player::View(bool tutrialFlag)
{
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
	if (tutrialFlag == false)
	{
		if (Input::GetInstance()->KeybordTrigger(DIK_9))
		{
			mouseViewSpeed -= 0.01f;
		}
		if (Input::GetInstance()->KeybordTrigger(DIK_0))
		{
			mouseViewSpeed += 0.01f ;
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