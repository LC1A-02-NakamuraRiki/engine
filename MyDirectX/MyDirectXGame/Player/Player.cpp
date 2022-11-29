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
	miniMapPos = { 100 + (16.0f * 11),650 + (16.0f * 11) };
	pos = { -4.0f,0.0f,-4.0f };//�v���C���[�̈ʒu
	mapPosValue = {0,0};
	r = 0.5;//�v���C���[�̔��a
	moveSpeed = 0.2f;//�����̑��x
	viewSpeed = 4.0f;//���_�̑���
	target = { 0,0.0f,0 };//�����_
	targetY = 0;//�h��̒���
	angle = { 0,0,0 };//��������
	walkShaking = 2.5;//�����̗h���l
	isWalkShaking = false;//�����̗h��̃t���O
	walkShakingTime = 0;//�����̗h��̃^�C��
	angleX = 0; //�J����X��
	angleY = 90; //�J����Y��
}

void Player::Update(MapChip *mapChip,bool tutrialFlag,bool catchFlag, bool catchFlag2)
{
	AngleSearch();//�v���C���[�̌����̎Z�o
	if (tutrialFlag == false && catchFlag == false && catchFlag2 == false)
	{
		Move(mapChip);//�ړ�
	}
	WalkShaking();//�����̗h��
	View(tutrialFlag,catchFlag, catchFlag2);//���_����

	spritePlayerDot->SetPosition({ 100 + (16.0f * 10), 634 + (16.0f * 11) });
	spritePlayerAngle->SetPosition({ 100 + (16.0f * 10) + 8, 634 + (16.0f * 11) + 8 });
	spritePlayerAngle->SetRotation(angle.y + 135);
}

void Player::Draw()
{
}

void Player::DrawSprite()
{
	spritePlayerAngle->Draw(1.0f);
	spritePlayerDot->Draw(1.0f);
}

void Player::Move(MapChip *mapChip)
{
	float r = 0.5f;
	float cornerR = 0.35f;
	if (mapChip->ArrayValue(pos.x - cornerR, pos.z + cornerR) == 1)
	{
		pos.x += cos((45 * 3.14f) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin((45 * 3.14f) / -180) * moveSpeed;      // z���W���X�V
		mapPosValue.x += cos((45 * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((45 * 3.14f) / -180) * (moveSpeed * 2);
	}
	else if (mapChip->ArrayValue(pos.x + cornerR, pos.z + cornerR) == 1)
	{
		pos.x += cos((135 * 3.14f) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin((135 * 3.14f) / -180) * moveSpeed;      // z���W���X�V
		mapPosValue.x += cos((135 * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((135 * 3.14f) / -180) * (moveSpeed * 2);

	}
	else if (mapChip->ArrayValue(pos.x - cornerR, pos.z - cornerR) == 1)
	{
		pos.x += cos((-45 * 3.14f) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin((-45 * 3.14f) / -180) * moveSpeed;      // z���W���X�V
		mapPosValue.x += cos((-45 * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((-45 * 3.14f) / -180) * (moveSpeed * 2);
	}
	else if (mapChip->ArrayValue(pos.x + cornerR, pos.z - cornerR) == 1)
	{
		pos.x += cos((225 * 3.14f) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin((225 * 3.14f) / -180) * moveSpeed;      // z���W���X�V
		mapPosValue.x += cos((225 * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((225 * 3.14f) / -180) * (moveSpeed * 2);
	}

	if (Input::GetInstance()->KeybordPush(DIK_W))
	{
		pos.x += cos((angle.y * 3.14f) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin((angle.y * 3.14f) / -180) * moveSpeed;      // z���W���X�V

		mapPosValue.x += cos(((angle.y + 180 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);

		target.x += cos((angle.y * 3.14f) / -180) * moveSpeed;      // x���W���X�V
		target.z += sin((angle.y * 3.14f) / -180) * moveSpeed;      // z���W���X�V
		//��
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // z���W���X�V

			mapPosValue.y += sin(((angle.y) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//��
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // x���W���X�V

			mapPosValue.x += cos(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//��
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // z���W���X�V
			mapPosValue.y += sin(((angle.y) * 3.14f) / -180) * (moveSpeed * 2);
			
		}
		//�E
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // x���W���X�V

			mapPosValue.x += cos(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_A))
	{
		pos.x += cos(((angle.y - 90) * 3.14f) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin(((angle.y - 90) * 3.14f) / -180) * moveSpeed;      // z���W���X�V

		mapPosValue.x += cos(((angle.y + 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin(((angle.y + 90) * 3.14f) / -180) * (moveSpeed * 2);

		target.x += cos(((angle.y - 90) * 3.14f) / -180) * moveSpeed;      // x���W���X�V
		target.z += sin(((angle.y - 90) * 3.14f) / -180) * moveSpeed;      // z���W���X�V
		//��
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y - 90 + 180) * 3.14f) / -180) * moveSpeed;      // z���W���X�V
			mapPosValue.y += sin(((angle.y + 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
			
		}
		//��
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y - 90 + 180) * 3.14f) / -180) * moveSpeed;      // x���W���X�V

			mapPosValue.x += cos(((angle.y + 90 + 180 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//��
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y - 90 + 180) * 3.14f) / -180) * moveSpeed;      // z���W���X�V

			mapPosValue.y += sin(((angle.y + 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//�E
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y - 90 + 180) * 3.14f) / -180) * moveSpeed;      // x���W���X�V

			mapPosValue.x += cos(((angle.y + 90 + 180 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_S))
	{
		pos.x += cos(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin(((angle.y + 180) * 3.14f) / -180) * moveSpeed;      // z���W���X�V
		mapPosValue.x += cos(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin((angle.y * 3.14f) / -180) * (moveSpeed * 2);

		target.x -= cos((angle.y * 3.14f) / -180) * moveSpeed;      // x���W���X�V
		target.z -= sin((angle.y * 3.14f) / -180) * moveSpeed;      // z���W���X�V
		//��
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y) * 3.14f) / -180) * moveSpeed;      // z���W���X�V
			mapPosValue.y += sin(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//��
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y) * 3.14f) / -180) * moveSpeed;      // x���W���X�V
			mapPosValue.x += cos(((angle.y + 360) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//��
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y) * 3.14f) / -180) * moveSpeed;      // z���W���X�V
			mapPosValue.y += sin(((angle.y + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//�E
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y) * 3.14f) / -180) * moveSpeed;      // x���W���X�V
			mapPosValue.x += cos(((angle.y + 360) * 3.14f) / -180) * (moveSpeed * 2);
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_D))
	{
		pos.x += cos(((angle.y + 90) * 3.14f) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin(((angle.y + 90) * 3.14f) / -180) * moveSpeed;      // z���W���X�V
		mapPosValue.x += cos(((angle.y - 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		mapPosValue.y += sin(((angle.y - 90) * 3.14f) / -180) * (moveSpeed * 2);

		target.x += cos(((angle.y + 90) * 3.14f) / -180) * moveSpeed;      // x���W���X�V
		target.z += sin(((angle.y + 90) * 3.14f) / -180) * moveSpeed;      // z���W���X�V
		//��
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y + 90 + 180) * 3.14f) / -180) * moveSpeed;      // z���W���X�V
			mapPosValue.y += sin(((angle.y - 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//��
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 90 + 180) * 3.14f) / -180) * moveSpeed;      // x���W���X�V
			mapPosValue.x += cos(((angle.y - 90 + 180 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//��
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y + 90 + 180) * 3.14f) / -180) * moveSpeed;      // z���W���X�V
			mapPosValue.y += sin(((angle.y - 90 + 180) * 3.14f) / -180) * (moveSpeed * 2);
		}
		//�E
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 90 + 180) * 3.14f) / -180) * moveSpeed;      // x���W���X�V
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

void Player::View(bool tutrialFlag, bool catchFlag,bool catchFlag2)
{
	XMVECTOR v0 = { 0,0,-10, 0 };
	//angle���W�A������y���܂��ɉ�]�B���a��-100
	XMMATRIX  rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationX(XMConvertToRadians(angleX));
	rotM *= XMMatrixRotationY(XMConvertToRadians(angleY));
	XMVECTOR v = XMVector3TransformNormal(v0, rotM);
	XMVECTOR cameraPos = { pos.x,pos.y,pos.z };
	XMVECTOR v3 = cameraPos + v;
	XMFLOAT3 f = { v3.m128_f32[0], v3.m128_f32[1], v3.m128_f32[2] };
	pos = { cameraPos.m128_f32[0], cameraPos.m128_f32[1], cameraPos.m128_f32[2] };
	target = f;
	if (tutrialFlag == false&&catchFlag==false && catchFlag2 == false)
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
