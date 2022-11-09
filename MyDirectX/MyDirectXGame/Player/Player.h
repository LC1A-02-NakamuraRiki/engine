#pragma once
#include <DirectXMath.h>
#include "MapChip.h"
#include "Sprite.h"
#include "SafeDelete.h"

class Player
{
protected: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	
	~Player();

	void Initialize();//�ŏ��̏�����
	
	void InitializeValue();//�^�C�g�����̏�����

	void Update(MapChip* mapChip,bool tutrialFlag);//�A�b�v�f�[�g
	
	void Draw();
	
	void DrawSprite();

	void Move(MapChip* mapChip);//����

	void WalkShaking();//�h��

	void View(bool tutrialFlag);//���_�̓���

	void AngleSearch();//���������̎Z�o
	
	XMFLOAT3 GetPos() { return pos; }
	XMFLOAT2 GetMapPos() { return mapPosValue; }
	XMFLOAT3 GetTarget() { return target; }
	float GetAngle() { return angle.y; }
	float GetViewSpeed() { return mouseViewSpeed; }
	float SetViewSpeedPlus() { return mouseViewSpeed += 0.05f; }
	float SetViewSpeedMinus() { return mouseViewSpeed -= 0.05f; }
	bool GetShakeFlag() { return shakeFlag; }
	bool SetShakeFlag(bool ShakeFlag) { return shakeFlag = ShakeFlag; }
private:

	Sprite* spritePlayerDot = nullptr;
	Sprite* spritePlayerAngle = nullptr;

	XMFLOAT3 pos = { -8.0f,0.0f,-40.0f };//�v���C���[�̈ʒu
	XMFLOAT2 miniMapPos = { 100 + (16.0f * 10),650 + (16.0f * 8) };
	XMFLOAT2 mapPosValue = { 0,0 };
	float r = 0.5;//�v���C���[�̔��a
	float moveSpeed = 0.2f;//�����̑��x
	float viewSpeed = 4.0f;//���_�̑���
	float mouseViewSpeed = 0.2f;//���_�̑���
	XMFLOAT3 target = { 0,0.0f,0 };//�����_
	float targetY = 0;//�h��̒���
	XMFLOAT3 angle = { 0,0,0 };//��������
	float walkShaking = 2.5;//�����̗h���l
	bool isWalkShaking = false;//�����̗h��̃t���O
	int walkShakingTime = 0;//�����̗h��̃^�C��
	float angleX = 0; //�J����X��
	float angleY = 0; //�J����Y��

	bool shakeFlag = true;
};