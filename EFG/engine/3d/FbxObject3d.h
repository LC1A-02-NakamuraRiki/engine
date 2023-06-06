#pragma once

#include "FbxModel.h"
#include "Camera.h"

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>
#include "LightGroop.h"

class FbxObject3d
{
protected: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �T�u�N���X

	// �萔�o�b�t�@�p�f�[�^�\���́i���W�ϊ��s��p�j
	struct ConstBufferDataTransform
	{
		XMMATRIX viewproj;    // �r���[�v���W�F�N�V�����s��
		XMMATRIX world; // ���[���h�s��
		XMFLOAT3 cameraPos; // �J�������W�i���[���h���W�j
		unsigned int lightActive;
	};

	static const int MAX_BONES = 32;

	struct ConstBuffeerDataSkin
	{
		XMMATRIX bones[MAX_BONES];
	};
public: // �ÓI�����o�֐�
	/// <summary>
	/// �O���t�B�b�N�p�C�v���C���̐���
	/// </summary>
	static void CreateGraphicsPipeline();
	// setter
	static void SetDevice(ID3D12Device* device) { FbxObject3d::device = device; }
	static void SetCamera(Camera* camera) { FbxObject3d::camera = camera; }

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;
	// �J����
	static Camera* camera;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;

public: // �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update(bool lightActive);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	void SetModel(FbxModel* model) { this->model = model; }

	void PlayAnimation();

	//���W�̎擾
	const XMFLOAT3& GetPosition() { return position; }

	XMFLOAT3 SetPosition(XMFLOAT3 position) { return this->position = position;}
	XMFLOAT3 SetScale(XMFLOAT3 scale) { return this->scale = scale;}
	XMFLOAT3 SetRotation(XMFLOAT3 rotation) { return this->rotation = rotation; }
	void StopAnimation() { isPlay = false; }
	void playAnimation() { isPlay = true; }
	void AnimationReset() { currentTime = startTime;}
protected: // �����o�ϐ�
	ComPtr<ID3D12Resource> constBuffSkin;
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffTransform;
	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 0.35f,0.35f,0.35f };
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0,3,0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	// ���f��
	FbxModel* model = nullptr;

	FbxTime frameTime;
	FbxTime startTime;
	FbxTime endTime;
	FbxTime currentTime;
	bool isPlay = false;

	bool isLoop = true;
};
