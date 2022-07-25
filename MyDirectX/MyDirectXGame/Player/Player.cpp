#include "Player.h"
#include "../input/Input.h"
using namespace DirectX;

void Player::Initialize()
{
}

void Player::Update(MapChip *mapChip)
{
	AngleSearch();
	Move(mapChip);
	WalkShaking();
	View();
}

void Player::Draw()
{
}

void Player::Move(MapChip *mapChip)
{
	float r = 0.5f;
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

void Player::collisionPosChange()
{
	XMVECTOR v0 = { 0,0,-2.5f, 0 };
	XMMATRIX  rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationY(XMConvertToRadians(angleY));
	XMVECTOR v = XMVector3TransformNormal(v0, rotM);
	XMVECTOR cameraPos = { pos.x,pos.y,pos.z };
	XMVECTOR v3 = cameraPos + v;
	XMFLOAT3 f = { v3.m128_f32[0], v3.m128_f32[1], v3.m128_f32[2] };
	collisionW = f;

	XMVECTOR v02 = { 0,0,-2.5f, 0 };
	XMMATRIX  rotM2 = XMMatrixIdentity();
	rotM2 *= XMMatrixRotationY(XMConvertToRadians(angleY + 90));
	XMVECTOR v2 = XMVector3TransformNormal(v02, rotM2);
	XMVECTOR cameraPos2 = { pos.x,pos.y,pos.z };
	XMVECTOR v32 = cameraPos2 + v2;
	XMFLOAT3 f2 = { v32.m128_f32[0], v32.m128_f32[1], v32.m128_f32[2] };
	collisionD = f2;

	XMVECTOR v05 = { 0,0,-2.5f, 0 };
	XMMATRIX  rotM5 = XMMatrixIdentity();
	rotM5 *= XMMatrixRotationY(XMConvertToRadians(angleY + 180));
	XMVECTOR v5 = XMVector3TransformNormal(v05, rotM5);
	XMVECTOR cameraPos5 = { pos.x,pos.y,pos.z };
	XMVECTOR v35 = cameraPos5 + v5;
	XMFLOAT3 f5 = { v35.m128_f32[0], v35.m128_f32[1], v35.m128_f32[2] };
	collisionS = f5;

	XMVECTOR v04 = { 0,0,-2.5f, 0 };
	XMMATRIX  rotM4 = XMMatrixIdentity();
	rotM4 *= XMMatrixRotationY(XMConvertToRadians(angleY + 270));
	XMVECTOR v4 = XMVector3TransformNormal(v04, rotM4);
	XMVECTOR cameraPos4 = { pos.x,pos.y,pos.z };
	XMVECTOR v34 = cameraPos4 + v4;
	XMFLOAT3 f4 = { v34.m128_f32[0], v34.m128_f32[1], v34.m128_f32[2] };
	collisionA = f4;
}