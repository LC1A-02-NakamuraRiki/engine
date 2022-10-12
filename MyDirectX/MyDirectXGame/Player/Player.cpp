#include "Player.h"
#include "../input/Input.h"
using namespace DirectX;

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
	miniMapPos = { 100 + (16.0f * 10),650 + (16.0f * 7) };
	pos = { -8.0f,0.0f,-56.0f };//�v���C���[�̈ʒu
	mapPosValue = {0,0};
	r = 0.5;//�v���C���[�̔��a
	moveSpeed = 0.4f;//�����̑��x
	viewSpeed = 4.0f;//���_�̑���
	target = { 0,0.0f,0 };//�����_
	targetY = 0;//�h��̒���
	angle = { 0,0,0 };//��������
	walkShaking = 2.5;//�����̗h���l
	isWalkShaking = false;//�����̗h��̃t���O
	walkShakingTime = 0;//�����̗h��̃^�C��
	angleX = 0; //�J����X��
	angleY = 0; //�J����Y��
}

void Player::Update(MapChip *mapChip)
{
	AngleSearch();//�v���C���[�̌����̎Z�o
	Move(mapChip);//�ړ�
	WalkShaking();//�����̗h��
	View();//���_����
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
	float cornerR = 0.35;
	if (mapChip->ArrayValue(pos.x - cornerR, pos.z + cornerR) == 1)
	{
		pos.x += cos((45 * 3.14) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin((45 * 3.14) / -180) * moveSpeed;      // z���W���X�V
		mapPosValue.x += cos((45 * 3.14) / -180) * moveSpeed;
		mapPosValue.y += sin((45 * 3.14) / -180) * moveSpeed;
	}
	else if (mapChip->ArrayValue(pos.x + cornerR, pos.z + cornerR) == 1)
	{
		pos.x += cos((135 * 3.14) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin((135 * 3.14) / -180) * moveSpeed;      // z���W���X�V
		mapPosValue.x += cos((135 * 3.14) / -180) * moveSpeed;
		mapPosValue.y += sin((135 * 3.14) / -180) * moveSpeed;

	}
	else if (mapChip->ArrayValue(pos.x - cornerR, pos.z - cornerR) == 1)
	{
		pos.x += cos((-45 * 3.14) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin((-45 * 3.14) / -180) * moveSpeed;      // z���W���X�V
		mapPosValue.x += cos((-45 * 3.14) / -180) * moveSpeed;
		mapPosValue.y += sin((-45 * 3.14) / -180) * moveSpeed;
	}
	else if (mapChip->ArrayValue(pos.x + cornerR, pos.z - cornerR) == 1)
	{
		pos.x += cos((225 * 3.14) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin((225 * 3.14) / -180) * moveSpeed;      // z���W���X�V
		mapPosValue.x += cos((225 * 3.14) / -180) * moveSpeed;
		mapPosValue.y += sin((225 * 3.14) / -180) * moveSpeed;
	}

	if (Input::GetInstance()->KeybordPush(DIK_W))
	{
		pos.x += cos((angle.y * 3.14) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin((angle.y * 3.14) / -180) * moveSpeed;      // z���W���X�V

		mapPosValue.x += cos(((angle.y + 180 + 180) * 3.14) / -180) * moveSpeed;
		mapPosValue.y += sin(((angle.y + 180) * 3.14) / -180) * moveSpeed;

		target.x += cos((angle.y * 3.14) / -180) * moveSpeed;      // x���W���X�V
		target.z += sin((angle.y * 3.14) / -180) * moveSpeed;      // z���W���X�V
		//��
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y + 180) * 3.14) / -180) * moveSpeed;      // z���W���X�V

			mapPosValue.y += sin(((angle.y) * 3.14) / -180) * moveSpeed;
		}
		//��
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 180) * 3.14) / -180) * moveSpeed;      // x���W���X�V

			mapPosValue.x += cos(((angle.y + 180) * 3.14) / -180) * moveSpeed;
		}
		//��
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y + 180) * 3.14) / -180) * moveSpeed;      // z���W���X�V
			mapPosValue.y += sin(((angle.y) * 3.14) / -180) * moveSpeed;
			
		}
		//�E
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 180) * 3.14) / -180) * moveSpeed;      // x���W���X�V

			mapPosValue.x += cos(((angle.y + 180) * 3.14) / -180) * moveSpeed;
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_A))
	{
		pos.x += cos(((angle.y - 90) * 3.14) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin(((angle.y - 90) * 3.14) / -180) * moveSpeed;      // z���W���X�V

		mapPosValue.x += cos(((angle.y + 90 + 180) * 3.14) / -180) * moveSpeed;
		mapPosValue.y += sin(((angle.y + 90) * 3.14) / -180) * moveSpeed;

		target.x += cos(((angle.y - 90) * 3.14) / -180) * moveSpeed;      // x���W���X�V
		target.z += sin(((angle.y - 90) * 3.14) / -180) * moveSpeed;      // z���W���X�V
		//��
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y - 90 + 180) * 3.14) / -180) * moveSpeed;      // z���W���X�V
			mapPosValue.y += sin(((angle.y + 90 + 180) * 3.14) / -180) * moveSpeed;
			
		}
		//��
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y - 90 + 180) * 3.14) / -180) * moveSpeed;      // x���W���X�V

			mapPosValue.x += cos(((angle.y + 90 + 180 + 180) * 3.14) / -180) * moveSpeed;
		}
		//��
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y - 90 + 180) * 3.14) / -180) * moveSpeed;      // z���W���X�V

			mapPosValue.y += sin(((angle.y + 90 + 180) * 3.14) / -180) * moveSpeed;
		}
		//�E
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y - 90 + 180) * 3.14) / -180) * moveSpeed;      // x���W���X�V

			mapPosValue.x += cos(((angle.y + 90 + 180 + 180) * 3.14) / -180) * moveSpeed;
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_S))
	{
		pos.x += cos(((angle.y + 180) * 3.14) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin(((angle.y + 180) * 3.14) / -180) * moveSpeed;      // z���W���X�V
		mapPosValue.x += cos(((angle.y + 180) * 3.14) / -180) * moveSpeed;
		mapPosValue.y += sin((angle.y * 3.14) / -180) * moveSpeed;

		target.x -= cos((angle.y * 3.14) / -180) * moveSpeed;      // x���W���X�V
		target.z -= sin((angle.y * 3.14) / -180) * moveSpeed;      // z���W���X�V
		//��
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y) * 3.14) / -180) * moveSpeed;      // z���W���X�V
			mapPosValue.y += sin(((angle.y + 180) * 3.14) / -180) * moveSpeed;
		}
		//��
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y) * 3.14) / -180) * moveSpeed;      // x���W���X�V
			mapPosValue.x += cos(((angle.y + 360) * 3.14) / -180) * moveSpeed;
		}
		//��
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y) * 3.14) / -180) * moveSpeed;      // z���W���X�V
			mapPosValue.y += sin(((angle.y + 180) * 3.14) / -180) * moveSpeed;
		}
		//�E
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y) * 3.14) / -180) * moveSpeed;      // x���W���X�V
			mapPosValue.x += cos(((angle.y + 360) * 3.14) / -180) * moveSpeed;
		}
		isWalkShaking = true;
	}
	if (Input::GetInstance()->KeybordPush(DIK_D))
	{
		pos.x += cos(((angle.y + 90) * 3.14) / -180) * moveSpeed;      // x���W���X�V
		pos.z += sin(((angle.y + 90) * 3.14) / -180) * moveSpeed;      // z���W���X�V
		mapPosValue.x += cos(((angle.y - 90 + 180) * 3.14) / -180) * moveSpeed;
		mapPosValue.y += sin(((angle.y - 90) * 3.14) / -180) * moveSpeed;

		target.x += cos(((angle.y + 90) * 3.14) / -180) * moveSpeed;      // x���W���X�V
		target.z += sin(((angle.y + 90) * 3.14) / -180) * moveSpeed;      // z���W���X�V
		//��
		if (mapChip->ArrayValue(pos.x, pos.z + r) == 1)
		{
			pos.z += sin(((angle.y + 90 + 180) * 3.14) / -180) * moveSpeed;      // z���W���X�V
			mapPosValue.y += sin(((angle.y - 90 + 180) * 3.14) / -180) * moveSpeed;
		}
		//��
		if (mapChip->ArrayValue(pos.x - r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 90 + 180) * 3.14) / -180) * moveSpeed;      // x���W���X�V
			mapPosValue.x += cos(((angle.y - 90 + 180 + 180) * 3.14) / -180) * moveSpeed;
		}
		//��
		if (mapChip->ArrayValue(pos.x, pos.z - r) == 1)
		{
			pos.z += sin(((angle.y + 90 + 180) * 3.14) / -180) * moveSpeed;      // z���W���X�V
			mapPosValue.y += sin(((angle.y - 90 + 180) * 3.14) / -180) * moveSpeed;
		}
		//�E
		if (mapChip->ArrayValue(pos.x + r, pos.z) == 1)
		{
			pos.x += cos(((angle.y + 90 + 180) * 3.14) / -180) * moveSpeed;      // x���W���X�V
			mapPosValue.x += cos(((angle.y - 90 + 180 + 180) * 3.14) / -180) * moveSpeed;
		}
		isWalkShaking = true;
	}
	spritePlayerDot->SetPosition({ 100 + (16.0f * 10), 634 + (16.0f * 8) });
	spritePlayerAngle->SetPosition({ 100 + (16.0f * 10) + 8, 634 + (16.0f * 8) +8});
	spritePlayerAngle->SetRotation(angle.y + 135);
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
			if (walkShakingTime <= 10)
			{
				walkShaking += 0.1;
			}
			else if (walkShakingTime >= 10 && walkShakingTime <= 20)
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
}

void Player::View()
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