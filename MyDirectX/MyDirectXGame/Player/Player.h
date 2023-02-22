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
	
	void Draw();
	
	void DrawSprite();

	void Move(MapChip* mapChip);//����

	void WalkShaking();//�h��

	void View(bool tutrialFlag, bool catchFlag,bool catchFlag2, bool catchFlag3);//���_�̓���

	void AngleSearch();//���������̎Z�o

	XMFLOAT2 GetShortCut(MapChip* mapChip,XMFLOAT3 enemyPos);
	
	XMFLOAT3 GetPos() { return pos; }
	XMFLOAT2 GetMapPos() { return mapPosValue; }
	XMFLOAT3 GetTarget() { return target; }
	float GetAngle() { return angle.y; }
	float GetViewAngle() { return angleY; }
	float SetViewAngleY(float value) { return angleY += value; }
	float SetViewAngleY2(float value) { return angleY = value; }
	float SetViewAngleX(float value) { return angleX += value; }
	float SetViewAngleX2(float value) { return angleX = value; }
	float GetViewSpeed() { return mouseViewSpeed; }
	float SetViewSpeedPlus() { return mouseViewSpeed += 0.05f; }
	float SetViewSpeedMinus() { return mouseViewSpeed -= 0.05f; }
	bool GetShakeFlag() { return shakeFlag; }
	bool SetShakeFlag(bool ShakeFlag) { return shakeFlag = ShakeFlag; }
	XMFLOAT3 SetPos(XMFLOAT3 pos) { return this->pos = pos; }
private:

	Sprite* spritePlayerDot = nullptr;
	Sprite* spritePlayerAngle = nullptr;
	Sprite* spriteMoveUI = nullptr;
	Sprite* spriteViewUI = nullptr;
	Sprite* spriteOpenUI = nullptr;
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

	float moveTutorial = 1.0f;
	bool moveTutorialFlag = false;
	float viewTutorial = 1.0f;
	bool viewTutorialFlag = false;
	float openTutorial = 1.0f;
	bool openTutorialFlag = false;

};