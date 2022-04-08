#pragma once

#include <DirectXMath.h>

/// <summary>
/// �J������{�@�\
/// </summary>
class Camera
{
protected: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �����o�֐�

	/// �R���X�g���N�^
	Camera(int window_width, int window_height);

	/// �f�X�g���N�^
	virtual ~Camera() = default;

	/// ���t���[���X�V
	virtual void Update();

	/// �r���[�s����X�V
	void UpdateViewMatrix();

	/// �ˉe�s����X�V
	void UpdateProjectionMatrix();

	/// �r���[�s��̎擾
	inline const XMMATRIX &GetViewMatrix() { return matView; }

	/// �ˉe�s��̎擾
	inline const XMMATRIX &GetProjectionMatrix() { return matProjection; }

	/// �r���[�ˉe�s��̎擾
	inline const XMMATRIX &GetViewProjectionMatrix() { return matViewProjection; }

	/// �r���{�[�h�s��̎擾
	inline const XMMATRIX &GetBillboardMatrix() { return matBillboard; }


	/// ���_���W�̎擾
	inline const XMFLOAT3 &GetEye() { return eye; }

	/// ���_���W�̐ݒ�
	inline void SetEye(XMFLOAT3 eye) { this->eye = eye; viewDirty = true; }

	/// �����_���W�̎擾
	inline const XMFLOAT3 &GetTarget() { return target; }

	/// �����_���W�̐ݒ�
	inline void SetTarget(XMFLOAT3 target) { this->target = target; viewDirty = true; }

	/// ������x�N�g���̎擾
	inline const XMFLOAT3 &GetUp() { return up; }

	/// ������x�N�g���̐ݒ�
	inline void SetUp(XMFLOAT3 up) { this->up = up; viewDirty = true; }

	/// �x�N�g���ɂ�鎋�_�ړ�
	void CameraMoveEyeVector(const XMFLOAT3 &move);

	/// �x�N�g���ɂ��ړ�
	void CameraMoveVector(const XMFLOAT3 &move);


protected: // �����o�ϐ�
	// �r���[�s��
	XMMATRIX matView = DirectX::XMMatrixIdentity();
	// �r���{�[�h�s��
	XMMATRIX matBillboard = DirectX::XMMatrixIdentity();
	// Y�����r���{�[�h�s��
	XMMATRIX matBillboardY = DirectX::XMMatrixIdentity();
	// �ˉe�s��
	XMMATRIX matProjection = DirectX::XMMatrixIdentity();
	// �r���[�ˉe�s��
	XMMATRIX matViewProjection = DirectX::XMMatrixIdentity();
	// �r���[�s��_�[�e�B�t���O
	bool viewDirty = false;
	// �ˉe�s��_�[�e�B�t���O
	bool projectionDirty = false;
	// ���_���W
	static XMFLOAT3 eye;
	// �����_���W
	static XMFLOAT3 target;
	// ������x�N�g��
	static XMFLOAT3 up;
	//�A�X��
	float aspectRatio = 1.0f;
};