#pragma once
#include <DirectXMath.h>
#include "../Map/MapChip.h"
#include "../3d/Object3d.h"
#include "../Player/Player.h"
#include "../2d/Sprite.h"

class Enemy
{
	enum MoveVector
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
	void Initialize();//�ŏ��̏�����

	void InitializeValue();//�^�C�g�����̏�����

	void Update(Player* player,MapChip* mapChip);//�A�b�v�f�[�g

	void Draw();

	void DrawSprite(MapChip* mapChip);

	void AI(Player* player,MapChip* mapChip);//����

	void Move(MapChip* mapChip);//����
	
	bool catchCollision(Player* player);//�v���C���[�ƓG�����蔻��

	XMFLOAT3 GetPos() { return pos; };
private:
	Sprite* spriteEnemyDot = nullptr;
	Sprite* spriteEnemyAngle = nullptr;
	XMFLOAT2 miniMapPos = { 100 + (16.0f * 10),650 + (16.0f * 14) };

	Model* modelEnemy = nullptr;
	Object3d* objEnemy;
	XMFLOAT3 pos = { -8.0f,0.0f,+56.0f };//�v���C���[�̈ʒu
	int nowMove = UP;//�ǂ̓��������Ă��邩
	float adjustValueX = 0;//�ʒu�����p�ϐ�X
	float adjustValueZ = 0;//�ʒu�����p�ϐ�Z
	bool vReserveFlag = false;//�c�D��
	bool wallHitFlag = false;
	int adjustmentTime = 0;
	bool adjustmentFlag = false;
};

