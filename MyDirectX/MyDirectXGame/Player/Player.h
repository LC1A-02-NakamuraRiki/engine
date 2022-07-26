#pragma once
#include <DirectXMath.h>
#include "../Map/MapChip.h"

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
	void Initialize();
	
	void Update(MapChip* mapChip);
	
	void Draw();

	void Move(MapChip* mapChip);//����

	void WalkShaking();//�h��

	void View();//���_�̓���

	void AngleSearch();//���������̎Z�o
	
	void collisionPosChange();
	XMFLOAT3 GetPos() { return pos; }
	XMFLOAT3 GetTarget() { return target; }
	float GetAngle() { return angle.y; }
private:
	XMFLOAT3 pos = { -8.0f,0.0f,-40.0f };//�v���C���[�̈ʒu
	XMFLOAT3 collisionW = { 0,0,0 };//�v���C���[�̈ʒu
	XMFLOAT3 collisionA = { 0,0,0 };//�v���C���[�̈ʒu
	XMFLOAT3 collisionS = { 0,0,0 };//�v���C���[�̈ʒu
	XMFLOAT3 collisionD = { 0,0,0 };//�v���C���[�̈ʒu
	float r = 0.5;//�v���C���[�̔��a
	float moveSpeed = 0.5f;//�����̑��x
	float viewSpeed = 4.0f;//���_�̑���
	float mouseViewSpeed = 0.1f;//���_�̑���
	XMFLOAT3 target = { 0,0.0f,0 };//�����_
	float targetY = 0;//�h��̒���
	XMFLOAT3 angle = { 0,0,0 };//��������
	float walkShaking = 2.5;//�����̗h���l
	bool isWalkShaking = false;//�����̗h��̃t���O
	int walkShakingTime = 0;//�����̗h��̃^�C��
	float angleX = 0; //�J����X��
	float angleY = 180; //�J����Y��
};