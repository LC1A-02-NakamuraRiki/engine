#pragma once
#include <DirectXMath.h>

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
	
	void Update();
	
	void Draw();

	void Move();//����

	void WalkShaking();//�h��

	void View();//���_�̓���

	void AngleSearch();//���������̎Z�o
	
	XMFLOAT3 GetPos() { return pos; }
	XMFLOAT3 GetTarget() { return target; }
private:
	XMFLOAT3 pos = { 0,0.0f,-20 };//�v���C���[�̈ʒu
	float moveSpeed = 0.5f;//�����̑��x
	float viewSpeed = 4.0f;//���_�̑���
	XMFLOAT3 target = { 0,0.0f,0 };//�����_
	float targetY = 0;//�h��̒���
	XMFLOAT3 angle = { 0,0,0 };//��������
	float walkShaking = 2.5;//�����̗h���l
	bool isWalkShaking = false;//�����̗h��̃t���O
	int walkShakingTime = 0;//�����̗h��̃^�C��
	float angleX = 0; //�J����X��
	float angleY = 0; //�J����Y��
};