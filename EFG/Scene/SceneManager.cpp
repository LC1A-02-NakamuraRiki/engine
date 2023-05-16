#include "SceneManager.h"
#include "Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "Input.h"
#include "SoundVector.h"
#include"TitleScene.h"
using namespace DirectX;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize(DirectXCommon* dxCommon, Sound* audio)
{
	//�l�n��
	this->dxCommon = dxCommon;
	this->audio = audio;

	//�J�����̃X�e�[�^�X������
	camera = std::make_unique<DebugCamera>(DebugCamera(WinApp::window_width, WinApp::window_height));
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera.get());

	// �e�N�X�`���ǂݍ���
	InitializeTexture();

	//�O���C���̏�����
	InitializeGrain();

	//FBX�̏�����
	InitializeFBX();
	
	//���C�g�̏�����
	light = std::unique_ptr<LightGroop>(LightGroop::Create());

	//Object�Ƀ��C�g�̃Z�b�g
	Object3d::SetLightGroup(light.get());

	//�A�v�����̏�����
	InitializeAppli();

	//�V�[�����^�C�g���ɐݒ�
	BaseScene* nowScene = new ClearScene();
	SetNextScene(nowScene);
}

void SceneManager::Update()
{
	//�O���C���̃A�b�v�f�[�g
	UpdateGrain();

	if (Input::GetInstance()->KeybordTrigger(DIK_5))
	{
		BaseScene* nowScene = new OptionScene();
		nowScene->InitializeBase();
		SetNextScene(nowScene);
	}
	//���̃V�[���̗\�񂪂���Ȃ�
	if (nextScene)
	{
		if (nowScene)
		{
			nowScene->Finalize();
			delete nowScene;
		}
		//�V�[���؂�ւ�
		nowScene = nextScene;
		nextScene = nullptr;

		nowScene->SetSceneManager(this);
		//���̃V�[��������������
		nowScene->Initialize();
	}

	//�X�V
	nowScene->Update(player.get(), map.get(), enemy[0].get(), enemy[1].get(), enemy[2].get(),camera.get(),light.get());
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

void SceneManager::InitializeTexture()
{
	Sprite::LoadTexture(18, L"Resources/Title.png");
	Sprite::LoadTexture(21, L"Resources/Title2.png");
	Sprite::LoadTexture(22, L"Resources/Title3.png");
	Sprite::LoadTexture(23, L"Resources/Option.png");
	Sprite::LoadTexture(24, L"Resources/Option2.png");
	Sprite::LoadTexture(25, L"Resources/Option3.png");
	Sprite::LoadTexture(50, L"Resources/grain.png");
	Sprite::LoadTexture(51, L"Resources/grain2.png");
	Sprite::LoadTexture(52, L"Resources/grain3.png");
	Sprite::LoadTexture(53, L"Resources/grain4.png");
	Sprite::LoadTexture(54, L"Resources/grain5.png");
	Sprite::LoadTexture(55, L"Resources/grain6.png");
	Sprite::LoadTexture(56, L"Resources/grain7.png");
	Sprite::LoadTexture(57, L"Resources/grain8.png");
	Sprite::LoadTexture(100, L"Resources/alartGrain.png");
	Sprite::LoadTexture(101, L"Resources/alartGrain2.png");
	Sprite::LoadTexture(102, L"Resources/alartGrain3.png");
	Sprite::LoadTexture(103, L"Resources/alartGrain4.png");
	Sprite::LoadTexture(104, L"Resources/alartGrain5.png");
	Sprite::LoadTexture(105, L"Resources/alartGrain6.png");
	Sprite::LoadTexture(106, L"Resources/alartGrain7.png");
	Sprite::LoadTexture(107, L"Resources/alartGrain8.png");
}

void SceneManager::InitializeGrain()
{
	//�O���C���e�N�X�`���̃X�e�[�^�X������
	const int MAXGRAINVALUE = 8;
	for (int i = 0; i < MAXGRAINVALUE; i++){
		spriteGrain[i] = std::unique_ptr<Sprite>(Sprite::Create(50 + i, { 0.0f,0.0f }));
		spriteGrain[i]->SetSize(XMFLOAT2{ 1920.0f * 1.5f,1080.0f * 1.5f });
		spriteAlartGrain1[i] = std::unique_ptr<Sprite>(Sprite::Create(100 + i, { 0.0f,0.0f }));
		spriteAlartGrain1[i]->SetSize(XMFLOAT2{ 1920.0f * 4.0f,1080.0f * 4.0f });
		spriteAlartGrain2[i] = std::unique_ptr<Sprite>(Sprite::Create(100 + i, { 0.0f,0.0f }));
		spriteAlartGrain2[i]->SetSize(XMFLOAT2{ 1920.0f * 5.0f,1080.0f * 5.0f });
	}
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

void SceneManager::UpdateGrain()
{
	//�O���C��
	const int MAXGARAIN = 7;
	for (int i = 0; i < 3; i++){
		grainCount[i]++;
		if (grainCount[i] > MAXGARAIN){
			grainCount[i] = 0;
		}
	}
}
