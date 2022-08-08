#include "Player.h"
#include "../input/Input.h"
using namespace DirectX;

void Player::Initialize()
{
}

void Player::InitializeValue()
{
	pos = { -8.0f,0.0f,-40.0f };//プレイヤーの位置
	r = 0.5;//プレイヤーの半径
	moveSpeed = 0.4f;//歩きの速度
	viewSpeed = 4.0f;//視点の速さ
	mouseViewSpeed = 0.3f;//視点の速さ
	target = { 0,0.0f,0 };//注視点
	targetY = 0;//揺れの調整
	angle = { 0,0,0 };//歩く方向
	walkShaking = 2.5;//歩きの揺れる値
	isWalkShaking = false;//歩きの揺れのフラグ
	walkShakingTime = 0;//歩きの揺れのタイム
	angleX = 0; //カメラX軸
	angleY = 180; //カメラY軸
}

void Player::Update(MapChip *mapChip)
{
	AngleSearch();//プレイヤーの向きの算出
	Move(mapChip);//移動
	WalkShaking();//歩きの揺れ
	View();//視点制御
}

void Player::Draw()
{
}

void Player::Move(MapChip *mapChip)
{
	//pos.x += cos((angle.y * 3.14) / -180) * moveSpeed;      // x座標を更新
	//pos.z += sin((angle.y * 3.14) / -180) * moveSpeed;      // z座標を更新
	float r = 0.5f;
	float cornerR = 0.35;
	if (mapChip->ArrayValue(pos.x - cornerR, pos.z + cornerR) == 1)
	{
		pos.x += cos((45 * 3.14) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((45 * 3.14) / -180) * moveSpeed;      // z座標を更新
	}
	else if (mapChip->ArrayValue(pos.x + cornerR, pos.z + cornerR) == 1)
	{
		pos.x += cos((135 * 3.14) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((135 * 3.14) / -180) * moveSpeed;      // z座標を更新
	}
	else if (mapChip->ArrayValue(pos.x - cornerR, pos.z - cornerR) == 1)
	{
		pos.x += cos((-45 * 3.14) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((-45 * 3.14) / -180) * moveSpeed;      // z座標を更新
	}
	else if (mapChip->ArrayValue(pos.x + cornerR, pos.z - cornerR) == 1)
	{
		pos.x += cos((225 * 3.14) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((225 * 3.14) / -180) * moveSpeed;      // z座標を更新
	}

	if (Input::GetInstance()->KeybordPush(DIK_W))
	{
		pos.x += cos((angle.y * 3.14) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((angle.y * 3.14) / -180) * moveSpeed;      // z座標を更新
		target.x += cos((angle.y * 3.14) / -180) * moveSpeed;      // x座標を更新
		target.z += sin((angle.y * 3.14) / -180) * moveSpeed;      // z座標を更新
		//上
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y + 180) * 3.14) / -180) * moveSpeed;      // z座標を更新
		}
		//左
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 180) * 3.14) / -180) * moveSpeed;      // x座標を更新
		}
		//下
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y + 180) * 3.14) / -180) * moveSpeed;      // z座標を更新
		}
		//右
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 180) * 3.14) / -180) * moveSpeed;      // x座標を更新
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_A))
	{
		pos.x += cos(((angle.y - 90) * 3.14) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin(((angle.y - 90) * 3.14) / -180) * moveSpeed;      // z座標を更新
		target.x += cos(((angle.y - 90) * 3.14) / -180) * moveSpeed;      // x座標を更新
		target.z += sin(((angle.y - 90) * 3.14) / -180) * moveSpeed;      // z座標を更新
		//上
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y - 90 + 180) * 3.14) / -180) * moveSpeed;      // z座標を更新
		}
		//左
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y - 90 + 180) * 3.14) / -180) * moveSpeed;      // x座標を更新
		}
		//下
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y - 90 + 180) * 3.14) / -180) * moveSpeed;      // z座標を更新
		}
		//右
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y - 90 + 180) * 3.14) / -180) * moveSpeed;      // x座標を更新
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_S))
	{
		pos.x += cos(((angle.y + 180) * 3.14) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin(((angle.y + 180) * 3.14) / -180) * moveSpeed;      // z座標を更新
		target.x -= cos((angle.y * 3.14) / -180) * moveSpeed;      // x座標を更新
		target.z -= sin((angle.y * 3.14) / -180) * moveSpeed;      // z座標を更新
		//上
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y) * 3.14) / -180) * moveSpeed;      // z座標を更新
		}
		//左
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y) * 3.14) / -180) * moveSpeed;      // x座標を更新
		}
		//下
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y) * 3.14) / -180) * moveSpeed;      // z座標を更新
		}
		//右
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y) * 3.14) / -180) * moveSpeed;      // x座標を更新
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_D))
	{
		pos.x += cos(((angle.y + 90) * 3.14) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin(((angle.y + 90) * 3.14) / -180) * moveSpeed;      // z座標を更新
		target.x += cos(((angle.y + 90) * 3.14) / -180) * moveSpeed;      // x座標を更新
		target.z += sin(((angle.y + 90) * 3.14) / -180) * moveSpeed;      // z座標を更新
		//上
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y + 90 + 180) * 3.14) / -180) * moveSpeed;      // z座標を更新
		}
		//左
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 90 + 180) * 3.14) / -180) * moveSpeed;      // x座標を更新
		}
		//下
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y + 90 + 180) * 3.14) / -180) * moveSpeed;      // z座標を更新
		}
		//右
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 90 + 180) * 3.14) / -180) * moveSpeed;      // x座標を更新
		}
		isWalkShaking = true;
	}
}

void Player::WalkShaking()
{
	if (isWalkShaking == true)
	{
		walkShakingTime++;
		if (walkShakingTime <= 10)
		{
			walkShaking += 0.1;
		}
		else if(walkShakingTime >= 10 && walkShakingTime <= 20)
		{
			walkShaking -= 0.1;
		}
		else if (walkShakingTime > 20)
		{
			walkShaking = 2.5;
			walkShakingTime = 0;
			isWalkShaking = false;
		}
	}
	pos.y = walkShaking;
	target.y = targetY + walkShaking;
}

void Player::View()
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

	if (Input::GetInstance()->KeybordTrigger(DIK_9))
	{
		mouseViewSpeed -= 0.01;
	}
	if (Input::GetInstance()->KeybordTrigger(DIK_0))
	{
		mouseViewSpeed += 0.01;
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
	angleY += Input::GetInstance()->GetMouseMove().lX * mouseViewSpeed;
	angleX -= Input::GetInstance()->GetMouseMove().lY * mouseViewSpeed;
}

void Player::AngleSearch()
{
	angle.y = XMConvertToDegrees(atan2(pos.x - target.x, pos.z - target.z)) + 90;
}