#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>

#include "Model.h"
#include "Camera.h"
#include "LightGroop.h"

class Object3d
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	static Light *light;
public: // �T�u�N���X

	struct LightInfo
	{
		XMFLOAT3 lightPos;
		unsigned int lightActive;
		unsigned int allActive;
	};
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataB0
	{
		//XMMATRIX mat;	// �R�c�ϊ��s��
		XMMATRIX viewproj;
		XMMATRIX world;
		XMFLOAT3 cameraPos;
		float pad;
		XMFLOAT3 shadowPos1;
		float pad2;
		XMFLOAT3 shadowPos2;
		float pad3;
		LightInfo lightInfo;
	};
	
	// �p�C�v���C���Z�b�g
	struct PipelineSet
	{
		// ���[�g�V�O�l�`��
		ComPtr<ID3D12RootSignature> rootsignature;
		// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
		ComPtr<ID3D12PipelineState> pipelinestate;
	};
private: // �萔

public: // �ÓI�����o�֐�

	//�ÓI������
	static void StaticInitialize(ID3D12Device *device,Camera *camera = nullptr);

	//�O���t�B�b�N�p�C�v���C���̐���
	static void InitializeGraphicsPipeline();

	//�`��O����
	static void PreDraw(ID3D12GraphicsCommandList *cmdList);

	//�`��㏈��
	static void PostDraw();

	/// �J�����̃Z�b�g
	static void SetCamera(Camera *camera) {
		Object3d::camera = camera;
	}

	//3D�I�u�W�F�N�g����
	static Object3d *Create(Model *model = nullptr);

	//���C�g�̈ʒu�ݒ�
	static void SetLightGroup(LightGroop* light) {
		Object3d::lightGroup = light;
	}
	
private: // �ÓI�����o�ϐ�
// �f�o�C�X
	static ID3D12Device *device;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList *cmdList;
	// �p�C�v���C��
	static PipelineSet pipelineSet;
	// �J����
	static Camera *camera;

	static LightGroop* lightGroup;

private:// �ÓI�����o�֐�
	

public: 
	//�����o�֐�
	bool Initialize();
	
	//���t���[������
	void Update(XMFLOAT3 objShadowPos , XMFLOAT3 objShadowPos2, XMFLOAT3 lightPos,unsigned int lightActive,unsigned int allActive);

	//�`��
	void Draw();

	//���W�̎擾
	const XMFLOAT3 &GetPosition() { return position; }
	//���W�̐ݒ�
	void SetPosition(XMFLOAT3 position) { this->position = position; }

	// ��]�p�̎擾
	const XMFLOAT3 &GetRotation() { return rotation; }
	// ��]�p�̐ݒ�
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }

	// ���f���X�P�[���̎擾
	const XMFLOAT3 &GetScale() { return scale; }
	// ���f���X�P�[���̐ݒ�
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }

	// ���f���Ƃ̘A�g
	void LinkModel(Model *model) { this->model = model; };

	/// �r���{�[�h�t���O�̃Z�b�g
	void SetBillboard(bool isBillboard) { this->isBillboard = isBillboard; }
	
	//void SetLightActive(int no, bool active);
	//unsigned int SetLightAllActive();
	//unsigned int SetLightAllNoActive();

	private: // �����o�ϐ�
	ComPtr<ID3D12Resource> constBuffB0; // �萔�o�b�t�@
		// �F
	XMFLOAT4 color = { 1,1,1,1 };
	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z�����̃��[�J����]�p
	XMFLOAT3 rotation = { 0,0,0 };
	// ���[�J�����W
	XMFLOAT3 position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	// �e�I�u�W�F�N�g
	Object3d *parent = nullptr;
	// ���f��
	Model *model = nullptr;
	// �r���{�[�h
	bool isBillboard = false;
	public:
	LightInfo lightInfo;
};