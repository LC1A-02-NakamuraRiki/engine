#pragma once
#include <DirectXMath.h>
#include "../Map/MapChip.h"
#include "../2d/Sprite.h"
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
	
	void Initialize();//�ŏ��̏�����
	
	void InitializeValue();//�^�C�g�����̏�����

	void Update(MapChip* mapChip);//�A�b�v�f�[�g
	
	void Draw();
	
	void DrawSprite();

	void Move(MapChip* mapChip);//����

	void WalkShaking();//�h��

	void View();//���_�̓���

	void AngleSearch();//���������̎Z�o
	
	XMFLOAT3 GetPos() { return pos; }
	XMFLOAT3 GetTarget() { return target; }
	float GetAngle() { return angle.y; }
	float GetViewSpeed() { return mouseViewSpeed; }
private:

	Sprite* spritePlayerDot = nullptr;
	Sprite* spritePlayerAngle = nullptr;

	XMFLOAT3 pos = { -8.0f,0.0f,-40.0f };//�v���C���[�̈ʒu
	XMFLOAT2 miniMapPos = { 100 + (16.0f * 10),650 + (16.0f * 8) };
	float r = 0.5;//�v���C���[�̔��a
	float moveSpeed = 0.4f;//�����̑��x
	float viewSpeed = 4.0f;//���_�̑���
	float mouseViewSpeed = 0.3f;//���_�̑���
	XMFLOAT3 target = { 0,0.0f,0 };//�����_
	float targetY = 0;//�h��̒���
	XMFLOAT3 angle = { 0,0,0 };//��������
	float walkShaking = 2.5;//�����̗h���l
	bool isWalkShaking = false;//�����̗h��̃t���O
	int walkShakingTime = 0;//�����̗h��̃^�C��
	float angleX = 0; //�J����X��
	float angleY = 0; //�J����Y��


};