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

	void Update(MapChip* mapChip,bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3);//�A�b�v�f�[�g
	
	void DrawSprite();//2D�`��

	void Move(MapChip* mapChip);//����

	void WalkShaking();//�h��

	void View(bool tutrialFlag, bool catchFlag,bool catchFlag2, bool catchFlag3);//���_�̓���

	void AngleSearch();//���������̎Z�o

	XMFLOAT2 GetShortCut(MapChip* mapChip,XMFLOAT3 enemyPos);//�v���C���[��4�}�X��ǂ�
	
	XMFLOAT3 GetPos() { return pos; }//3D���W�̎擾
	XMFLOAT3 SetPos(XMFLOAT3 pos) { return this->pos = pos; }//3D���W�̎w��
	XMFLOAT2 GetMapPos() { return mapPosValue; }//2D���W�̎擾
	XMFLOAT3 GetTarget() { return target; }//�����_�̎擾
	float GetAngle() { return angle.y; }//���Ă�������̎擾
	float GetViewAngle() { return angleY; }//���Ă�������̎擾
	float SetViewAngleY(float value) { return angleY += value; }//���Ă�������̎w��
	float SetViewAngleY2(float value) { return angleY = value; }//���Ă�������̎w��
	float SetViewAngleX(float value) { return angleX += value; }//���Ă�������̎w��
	float SetViewAngleX2(float value) { return angleX = value; }//���Ă�������̎w��
	float GetViewSpeed() { return mouseViewSpeed; }//���_���x�̎擾
	float SetViewSpeedPlus() { return mouseViewSpeed += 0.05f; }//���_���x�̎w��
	float SetViewSpeedMinus() { return mouseViewSpeed -= 0.05f; }//���_���x�̎w��
	bool GetShakeFlag() { return shakeFlag; }//�V�F�C�N�t���O�̎擾
	bool SetShakeFlag(bool ShakeFlag) { return shakeFlag = ShakeFlag; }//�V�F�C�N�t���O�̎w��
private:

	Sprite* spritePlayerDot = nullptr;//�~�j�}�b�v�̃h�b�g
	Sprite* spritePlayerAngle = nullptr;//�~�j�}�b�v�̌��Ă���ʒu
	Sprite* spriteMoveUI = nullptr;//�ړ���UI
	Sprite* spriteViewUI = nullptr;//���_��UI
	Sprite* spriteOpenUI = nullptr;//�J����UI
	XMFLOAT3 pos = { -8.0f,0.0f,-40.0f };//�v���C���[�̈ʒu
	XMFLOAT2 miniMapPos = { 100 + (16.0f * 10),650 + (16.0f * 8) };//�~�j�}�b�v�����l
	XMFLOAT2 mapPosValue = { 0,0 };//�}�b�v�̍��W
	float r = 0.5;//�v���C���[�̔��a
	float moveSpeed = 0.18f;//�����̑��x
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

	bool shakeFlag = true;//�V�F�C�N��ON/OFF

	float moveTutorial = 1.0f;//�ړ��`���[�g���A���A���t�@
	bool moveTutorialFlag = false;//�ړ��`���[�g���A���t���O
	float viewTutorial = 1.0f;//���_�`���[�g���A���A���t�@
	bool viewTutorialFlag = false;//���_�`���[�g���A���t���O
	float openTutorial = 1.0f;//�J����`���[�g���A���A���t�@
	bool openTutorialFlag = false;//�J����`���[�g���A���t���O
};