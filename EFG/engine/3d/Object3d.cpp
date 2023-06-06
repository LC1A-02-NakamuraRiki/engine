#include "Object3d.h"
#include <d3dcompiler.h>
#include"Input.h"
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;
#include <fstream>	
#include <sstream>	
#include <string>	
#include <vector>

/// <summary>
/// �ÓI�����o�ϐ��̎���
/// </summary>
ID3D12Device *Object3d::device = nullptr;
ID3D12GraphicsCommandList *Object3d::cmdList = nullptr;
Object3d::PipelineSet Object3d::pipelineSet;
Camera *Object3d::camera = nullptr;
LightGroop *Object3d::lightGroup = nullptr;

void Object3d::StaticInitialize(ID3D12Device *device,Camera *camera)
{
	Object3d::device = device;
	Object3d::camera = camera;

	// �p�C�v���C��������
	InitializeGraphicsPipeline();

	Model::StaticInitialize(device);
}

void Object3d::InitializeGraphicsPipeline()
{
	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob> vsBlob; // ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob; // �G���[�I�u�W�F�N�g

	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"Resources/shaders/OBJVS.hlsl",  // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		"main", "vs_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		&vsBlob, &errorBlob);

	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"Resources/shaders/OBJPS.hlsl",   // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		"main", "ps_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		&psBlob, &errorBlob);

	if (FAILED(result)) {
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char *)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}

	// ���_���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{  //xyz���W
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		}, // (1�s�ŏ������ق������₷��)

		{  //�@���x�N�g��
			"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		}, // (1�s�ŏ������ق������₷��)

		{  //uv���W
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		}, // (1�s�ŏ������ق������₷��)
	};

	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

	// �W���ݒ�(�w�ʃJ�����O�A�h��Ԃ��A�[�x�N���b�s���O�L��)
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);

	//�f�v�X�X�e���V���X�e�[�g�̐ݒ�
	//�W���ݒ�(�[�x�e�X�g���s���A�������݋��A��������΍��i)
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);

	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; //�W���ݒ�
	blenddesc.BlendEnable = true;                 //�u�����h��L���ɂ���
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;  //���Z
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;   //�\�[�X�̒l��100%�g��
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; //�f�X�g�̒l��  0%�g��

	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

	gpipeline.BlendState.RenderTarget[0] = blenddesc;
	gpipeline.BlendState.RenderTarget[1] = blenddesc;

	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 2; // �`��Ώۂ�1��
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R16G16B16A16_UNORM; // 0�`255�w���RGBA
	gpipeline.RTVFormats[1] = DXGI_FORMAT_R16G16B16A16_UNORM; // 0�`255�w���RGBA
	gpipeline.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	//�f�X�N���v�^�e�[�u���̐ݒ�
	CD3DX12_DESCRIPTOR_RANGE descTblRangeSRV;
	descTblRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);  //t0 ���W�X�^

	// ���[�g�p�����[�^	
	CD3DX12_ROOT_PARAMETER rootparams[4];
	rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[1].InitAsConstantBufferView(1, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[2].InitAsDescriptorTable(1, &descTblRangeSRV, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[3].InitAsConstantBufferView(2, 0, D3D12_SHADER_VISIBILITY_ALL);
	
	// �X�^�e�B�b�N�T���v���[
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

	// ���[�g�V�O�l�`���̐ݒ�
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob;
	// �o�[�W������������̃V���A���C�Y
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	// ���[�g�V�O�l�`���̐���
	result = device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&pipelineSet.rootsignature));

	gpipeline.pRootSignature = pipelineSet.rootsignature.Get();

	// �O���t�B�b�N�X�p�C�v���C���̐���
	result = device->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineSet.pipelinestate));

}

void Object3d::PreDraw(ID3D12GraphicsCommandList *cmdList)
{
	// �R�}���h���X�g���Z�b�g
	Object3d::cmdList = cmdList;
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Object3d::PostDraw()
{
	Object3d::cmdList = nullptr;
}

Object3d *Object3d::Create(Model *model)
{
	Object3d *object3d = new Object3d();
	if (object3d == nullptr) {
		return nullptr;
	}
	//�X�P�[�����Z�b�g	// ������
	float scale_val = 1;
	object3d->scale = { scale_val, scale_val, scale_val };
	// ������
		if (!object3d->Initialize()) {
			delete object3d;
			assert(0);
		}
		if (model) {
			object3d->LinkModel(model);
		}
	return object3d;
}

bool Object3d::Initialize()
{
	HRESULT result;

	//�萔�o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), //�A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB0));

	constBuffB0->SetName(L"EZEZEZEZEZEZEZEZ");
	return true;
}

void Object3d::Update(XMFLOAT3 objShadowPos, XMFLOAT3 objShadowPos2, XMFLOAT3 objShadowPos3, XMFLOAT3 lightPos, unsigned int lightActive, unsigned int allActive)
{
	assert(camera);

	HRESULT result;
	XMMATRIX matScale, matRot, matTrans;

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(XMConvertToRadians(rotation.z));
	matRot *= XMMatrixRotationX(XMConvertToRadians(rotation.x));
	matRot *= XMMatrixRotationY(XMConvertToRadians(rotation.y));
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);

	// ���[���h�s��̍���
	matWorld = XMMatrixIdentity(); // �ό`�����Z�b�g
	matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
	matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f

	if (isBillboard) {
		const XMMATRIX &matBillboard = camera->GetBillboardMatrix();

		matWorld = XMMatrixIdentity();
		matWorld *= matScale; // ���[���h�s��ɃX�P�[�����O�𔽉f
		matWorld *= matRot; // ���[���h�s��ɉ�]�𔽉f
		matWorld *= matBillboard;
		matWorld *= matTrans; // ���[���h�s��ɕ��s�ړ��𔽉f
	}

	// �e�I�u�W�F�N�g�������
	if (parent != nullptr) {
		// �e�I�u�W�F�N�g�̃��[���h�s����|����
		matWorld *= parent->matWorld;
	}

	const XMMATRIX &matViewProjection = camera->GetViewProjectionMatrix();
	const XMFLOAT3 &cameraPos = camera->GetEye();
	const XMFLOAT3& cameraPos2 = camera->GetEye();
	// �萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataB0 *constMap = nullptr;
	result = constBuffB0->Map(0, nullptr, (void **)&constMap);
	//constMap->mat = matWorld * matViewProjection;	// �s��̍���
	constMap->viewproj = matViewProjection;
	constMap->world = matWorld;
	constMap->cameraPos = cameraPos;
	constMap->shadowPos1 = objShadowPos;
	constMap->shadowPos2 = objShadowPos2;
	constMap->shadowPos3 = objShadowPos3;
	
	lightInfo.lightPos = lightPos;
	lightInfo.lightActive = lightActive;
	lightInfo.allActive = allActive;

	constMap->lightInfo = lightInfo;

	

	constBuffB0->Unmap(0, nullptr);
}

void Object3d::Draw()
{
	// ���f���̊��蓖�Ă��Ȃ���Ε`�悵�Ȃ�
	if (model == nullptr) {
		return;
	}

	// �p�C�v���C���X�e�[�g�̐ݒ�
	cmdList->SetPipelineState(pipelineSet.pipelinestate.Get());
	// ���[�g�V�O�l�`���̐ݒ�
	cmdList->SetGraphicsRootSignature(pipelineSet.rootsignature.Get());
	// �萔�o�b�t�@�r���[���Z�b�g
	cmdList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());

	lightGroup->Draw(cmdList, 3);
	// ���f���`��
	model->Draw(cmdList);
}