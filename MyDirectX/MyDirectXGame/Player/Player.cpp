#include "Player.h"
#include "../input/Input.h"
using namespace DirectX;

void Player::Initialize()
{
}

void Player::Update()
{
	AngleSearch();
	Move();
	WalkShaking();
	View();
}

void Player::Draw()
{
}

void Player::Move()
{
	if (Input::GetInstance()->KeybordPush(DIK_W))
	{
		pos.x += cos((angle.y * 3.14) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin((angle.y * 3.14) / -180) * moveSpeed;      // z座標を更新
		target.x += cos((angle.y * 3.14) / -180) * moveSpeed;      // x座標を更新
		target.z += sin((angle.y * 3.14) / -180) * moveSpeed;      // z座標を更新
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_A))
	{
		pos.x += cos(((angle.y - 90) * 3.14) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin(((angle.y - 90) * 3.14) / -180) * moveSpeed;      // z座標を更新
		target.x += cos(((angle.y - 90) * 3.14) / -180) * moveSpeed;      // x座標を更新
		target.z += sin(((angle.y - 90) * 3.14) / -180) * moveSpeed;      // z座標を更新
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_S))
	{
		pos.x -= cos((angle.y * 3.14) / -180) * moveSpeed;      // x座標を更新
		pos.z -= sin((angle.y * 3.14) / -180) * moveSpeed;      // z座標を更新
		target.x -= cos((angle.y * 3.14) / -180) * moveSpeed;      // x座標を更新
		target.z -= sin((angle.y * 3.14) / -180) * moveSpeed;      // z座標を更新
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_D))
	{
		pos.x += cos(((angle.y + 90) * 3.14) / -180) * moveSpeed;      // x座標を更新
		pos.z += sin(((angle.y + 90) * 3.14) / -180) * moveSpeed;      // z座標を更新
		target.x += cos(((angle.y + 90) * 3.14) / -180) * moveSpeed;      // x座標を更新
		target.z += sin(((angle.y + 90) * 3.14) / -180) * moveSpeed;      // z座標を更新
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

}

void Player::AngleSearch()
{
	angle.y = XMConvertToDegrees(atan2(pos.x - target.x, pos.z - target.z)) + 90;
}