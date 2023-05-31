#pragma once
#include <DirectXMath.h>
#include "MapChip.h"
#include "Sprite.h"

class Player
{
	enum class CollisionDirection//�ړ�����
	{
		FRONT,
		BACK,
		RIGHT,
		LEFT
	};
	enum class VerticalOrHorizontal//�ړ�����
	{
		VERTICAL,
		HORIZONTAL
	};

	enum class CHECKVECTOR//�ړ�����
	{
		ZPLUS,
		ZMINUS,
		XPLUS,
		XMINUS,
	};
private: // �G�C���A�X
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

	void Move(MapChip* mapChip, bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3);//����

	void MoveValue(float vec);

	void MoveCollision(MapChip* mapChip, float vec);

	

	bool TouchWall(MapChip* mapChip, CollisionDirection direction);

	void PushBack(VerticalOrHorizontal VerOrHor, float vec);

	void WalkShaking();//�h��

	void View(bool tutrialFlag, bool catchFlag,bool catchFlag2, bool catchFlag3);//���_�̓���

	void AngleSearch();//���������̎Z�o

	void TutorialAlpha(MapChip* mapChip);

	void UiUpdate();

	void MapDraw();

	void UiDraw();

	bool AlartFlag(MapChip* mapChip, XMFLOAT3 enemyPos);

	int ShortCutFlag(MapChip* mapChip, XMFLOAT3 enemyPos, int X, int Z);

	XMFLOAT2 ShortCutValue(MapChip* mapChip, XMFLOAT3 enemyPos, float X, float Z,CHECKVECTOR vector);

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
	const float WALLSIZE = 8.0f;//�ǂ̑傫��
	const float MAPWALLSIZE = 16.0f;//�~�j�}�b�v�̕ǂ̑傫��
	const int MAPVALUE = 21;//�}�b�v�̍ő�T�C�Y
	const float MOVESPEED = 0.18f;//�����̑��x
	const float PI = 3.141592f;
	const float INVERSEVECTOR = 180;
	const float R = 0.5f;//���a
	const float CORNER = 0.35f;//�p�܂ł̋���
	std::unique_ptr<Sprite> spritePlayerDot;//�~�j�}�b�v�̃h�b�g
	std::unique_ptr<Sprite> spritePlayerAngle;//�~�j�}�b�v�̌��Ă���ʒu
	std::unique_ptr<Sprite> spriteMoveUI;//�ړ���UI
	std::unique_ptr<Sprite> spriteViewUI;//���_��UI
	std::unique_ptr<Sprite> spriteOpenUI;//�J����UI
	XMFLOAT3 pos = { -8.0f,0.0f,-40.0f };//�v���C���[�̈ʒu
	XMFLOAT2 miniMapPos = { 100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 8) };//�~�j�}�b�v�����l
	XMFLOAT2 mapPosValue = { 0,0 };//�}�b�v�̍��W
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