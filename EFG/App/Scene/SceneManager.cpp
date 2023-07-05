#include "SceneManager.h"
#include "Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "Input.h"
#include "SoundVector.h"
#include "TitleScene.h"
#include "TextureManager.h"

using namespace DirectX;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize(DirectXCommon* dxCommon)
{
	//�l�n��
	this->dxCommon = dxCommon;

	//�J�����̃X�e�[�^�X������
	camera = std::make_unique<DebugCamera>(DebugCamera(WinApp::window_width, WinApp::window_height));
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera.get());

	// �e�N�X�`���ǂݍ���
	TextureManager::LoadTexture();

	//FBX�̏�����
	InitializeFBX();
	
	//���C�g�̏�����
	light = std::unique_ptr<LightGroop>(LightGroop::Create());

	//Object�Ƀ��C�g�̃Z�b�g
	Object3d::SetLightGroup(light.get());

	//�A�v�����̏�����
	InitializeAppli();

	//�V�[�����^�C�g���ɐݒ�
	BaseScene* nowScene = new TitleScene();
	nowScene->InitializeBase();
	SetNextScene(nowScene);
	
}

void SceneManager::Update()
{
	//���̃V�[���̗\�񂪂���Ȃ�
	if (nextScene){
		if (nowScene){
			nowScene->Finalize();
			delete nowScene;
		}
		//�V�[���؂�ւ�
		nowScene = nextScene;
		nextScene = nullptr;

		nowScene->SetSceneManager(this);
		//���̃V�[��������������
		nowScene->Initialize(camera.get());
		nowScene->InitializeBase();
	}

	//�X�V
	nowScene->Update(player.get(), map.get(), enemy[0].get(), enemy[1].get(), enemy[2].get(),camera.get(),light.get());
	//�O���C���̃A�b�v�f�[�g
	nowScene->UpdateGrain();
}

void SceneManager::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
#pragma region �w�i�X�v���C�g�`��g
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��
	//-------------------------------------------------------------//
	nowScene->DrawPost2D(player.get(), map.get(), enemy[0].get(), enemy[1].get(), enemy[2].get());
	//-------------------------------------------------------------//
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCommon->ClearDepthBuffer();
#pragma endregion
#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(cmdList);
	//-------------------------------------------------------------//
	nowScene->Draw3D(player.get(), map.get(), enemy[0].get(), enemy[1].get(), enemy[2].get(),cmdList);
	//-------------------------------------------------------------//
	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
#pragma endregion
#pragma region �O�i�X�v���C�g�`��
	//// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	//-------------------------------------------------------------//
	//-------------------------------------------------------------//
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion
}

void SceneManager::PostOffDraw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��
	//-------------------------------------------------------------//
	nowScene->DrawGrain();
	//-------------------------------------------------------------//
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(cmdList);
	//-------------------------------------------------------------//
	//-------------------------------------------------------------//
	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
#pragma endregion
#pragma region �O�i�X�v���C�g�`��
	//// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	//-------------------------------------------------------------//
	nowScene->Draw2D(player.get(), map.get(), enemy[0].get(), enemy[1].get(), enemy[2].get());
	//-------------------------------------------------------------//
	// �f�o�b�O�e�L�X�g�̕`��
	nowScene->DrawDebugText(cmdList);
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
}

void SceneManager::InitializeFBX()
{
	// �f�o�C�X���Z�b�g
	FbxObject3d::SetDevice(dxCommon->GetDevice());
	// �J�������Z�b�g
	FbxObject3d::SetCamera(camera.get());
	// �O���t�B�b�N�X�p�C�v���C������
	FbxObject3d::CreateGraphicsPipeline();
}

void SceneManager::InitializeAppli()
{
	//�v���C���[������
	player = std::make_unique<Player>();
	player->Initialize();
	
	//�}�b�v������
	map = std::make_unique<MapChip>();
	map->Initialize();

	//�G������
	const int MAXENEMYNUM = 3;
	for (int i = 0; i < MAXENEMYNUM; i++) {
		enemy[i] = std::make_unique <Enemy>();
		enemy[i]->Initialize();
	}
}