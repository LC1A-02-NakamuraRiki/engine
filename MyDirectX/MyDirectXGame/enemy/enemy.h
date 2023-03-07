#pragma once
#include <DirectXMath.h>
#include "MapChip.h"
#include "Object3d.h"
#include "Player.h"
#include "Sprite.h"
#include "SafeDelete.h"
#include "FbxObject3d.h"

class Enemy
{
	enum MoveVector//�ړ�����
	{
		UP,
		DOWN,
		RIGHT,
		LEFT
	};
protected: // �G�C���A�X

	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	~Enemy();
	void Initialize();//�ŏ��̏�����

	void InitializeValue();//�^�C�g�����̏�����
	void InitializeValue2();//�^�C�g�����̏�����
	void InitializeValue3();//�^�C�g�����̏�����

	void Update(Player* player,MapChip* mapChip,XMFLOAT2 mapPos,XMFLOAT2 plusValue, bool catchFlag1, bool catchFlag2);//�A�b�v�f�[�g

	void Draw(Player* player, ID3D12GraphicsCommandList* cmdList);//3d�̕`��

	void DrawSprite(MapChip* mapChip);//2d�̕`��

	void AI(Player* player,MapChip* mapChip, XMFLOAT2 plusValue);//����

	void Move(MapChip* mapChip, XMFLOAT2 mapPos);//����
	
	bool CatchCollision(Player* player);//�v���C���[�ƓG�����蔻��

	bool DeathAnimation(Player* player);//����A�j���[�V����

	XMFLOAT3 GetPos() { return pos; };//���W
	float GetRotation() { return angle; };//�p�x�擾
	int GetStartStopTime() {return startStopTime;}//�X�^�[�g�̍d������
	
private:
	std::unique_ptr<FbxModel> modelWalking;//�������f��
	std::unique_ptr<FbxObject3d> objectWalking;//�����I�u�W�F
	std::unique_ptr<FbxModel> modelAttack;//�U�����f��
	std::unique_ptr<FbxObject3d> objectAttack;//�U���I�u�W�F
	float angle; //����
	std::unique_ptr<Sprite> spriteEnemyDot;//�~�j�}�b�v�̓G
	std::unique_ptr<Sprite> spriteEnemyAngle;//�~�j�}�b�v�̓G�̌���
	std::unique_ptr<Sprite> spriteDeadEffect;//�~�j�}�b�v�̓G�̌���
	XMFLOAT2 miniMapPos = { 100 + (16.0f * 10),650 + (16.0f * 14) };//�~�j�}�b�v�̃h�b�g���W
	float wallSize = 8;//�ǂ̑傫��
	XMFLOAT3 pos = { -8.0f,0.0f,+56.0f };//�ʒu
	float speed = 2.0f;//�X�s�[�h
	int nowMove = UP;//�ǂ̓��������Ă��邩
	float adjustValueX = 0;//�ʒu�����p�ϐ�X
	float adjustValueZ = 0;//�ʒu�����p�ϐ�Z
	bool vReserveFlag = false;//�c�D��
	bool wallHitFlag = false;//��ǂ݂̍��W���ǂɓ������Ă��邩
	int adjustmentTime = 0;//�ʒu�����̎���
	int maxAdjustmentTime = 0;//�ʒu�����̍ő厞��
	bool adjustmentFlag = false;//�ʒu�����t���O

	int killTime = 0;//���胂�[�V�����̎���
	int startStopTime = 0;//�X�^�[�g�܂ł̍d������

	int mapX = int((pos.x / 8) + ((21 + 1) / 2));//�}�b�v�`�b�v�̍��WX
	int mapZ = int((pos.z / 8) + ((21 + 1) / 2));//�}�b�v�`�b�v�̍��WZ

	XMFLOAT3 deadPos = { 0.0f,2.5f,0.0f };//�ߊl���̃|�W�V����
	float deadView = 0.0f;//�ߊl���̎��_
	float deadAlpha = 0.0f;//�ߊl���̃A���t�@
	bool deadAlphaCountFlag = false;//�ߊl���̃A���t�@�̃t���O
};

