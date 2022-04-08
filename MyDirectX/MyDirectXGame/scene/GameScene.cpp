#include "GameScene.h"
#include "Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "../SphereCollider.h"
#include "../CollisionManager.h"
#include "../Player.h"
#include "../3d/FbxLoader.h"
using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteBG);
	safe_delete(particle3d);
	safe_delete(skydomeObj);
	safe_delete(skydomeModel);
	safe_delete(groundObj);
	safe_delete(groundModel);
	safe_delete(carObj);
	safe_delete(carModel);
	safe_delete(light);
	safe_delete(objFighter);
	safe_delete(modelFighter);
	safe_delete(objSphere);
	safe_delete(modelSphere);
}

void GameScene::Initialize(DirectXCommon *dxCommon, Input *input, Audio *audio)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	collisionManager = CollisionManager::GetInstance();

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera);

	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// �f�o�b�O�e�L�X�g������
	debugText.Initialize(debugTextTexNumber);

	particle3d = ParticleManager::Create(dxCommon->GetDevice(), camera);
	
	//�X�v���C�g
	// �e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(1, L"Resources/background.png")) {
		assert(0);
		return;
	}
	//// �w�i�X�v���C�g����
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	
	// 3D�I�u�W�F�N�g����
	skydomeModel = Model::CreateFromObject("skydome", false);
	skydomeObj = Object3d::Create(skydomeModel);
	groundModel = Model::CreateFromObject("ground", true);
	groundObj = Object3d::Create(groundModel);
	modelFighter = Model::CreateFromObject("chr_sword", true);
	objFighter = Player::Create(modelFighter);
	objFighter->SetPosition({ +1, 0, 0 });
	modelSphere = Model::CreateFromObject("sphere", true);
	objSphere->SetCollider(new SphereCollider);
	
	carModel = Model::CreateFromObject("largeCarL", true);
	carObj = Object3d::Create(carModel);
	
	//FbxLoader::GetInstance()->LoadModelFromFile(
	//"cube");
	objSphere->SetPosition({ -1, 1, 0 });
	light = Light::Create();
	light->SetLightColor({ 1.0f,0.8f,0.8f});
	
	Object3d::SetLight(light);

	////�T�E���h�Đ�
	audio->PlayBGM("Resources/Alarm01.wav", true);
	//audio->PlaySE("Resources/Alarm01.wav", false);
	
}

void GameScene::Update()
{
	///�}�E�X�̍��W
	//LONG mouseX = input->GetMousePoint().lX;
	//LONG mouseY = input->GetMousePoint().lY;

	XMFLOAT3 cameraEye = camera->GetEye();
	XMFLOAT3 cameraTarget = camera->GetTarget();

	debugText.Print(20, 20 + 30 * 1, 1.5f, "ObjectMove:ArrowKey");
	debugText.Print(20, 20 + 30 * 2, 1.5f, "EyeMove:Q E SPACE CTRL");
	debugText.Print(20, 20 + 30 * 3, 1.5f, "LClick:PlayBGM  RClick:StopBGM");
	debugText.Print(20, 20 + 30 * 4, 1.5f, "   carPos %f %f %f", carObj->GetPosition().x, carObj->GetPosition().y, carObj->GetPosition().z);
	debugText.Print(20, 20 + 30 * 5, 1.5f, "cameraPos %f %f %f", cameraEye.x, cameraEye.y, cameraEye.z);

	if (input->TriggerMouse(1))
	{
		audio->StopBGM();
	}
	if (input->TriggerMouse(0))
	{
		audio->PlayBGM("Resources/Alarm01.wav", true);
	}
	// �I�u�W�F�N�g�ړ�
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT) /*|| input->PushKey(DIK_SPACE) || input->PushKey(DIK_LCONTROL)*/)
	{
		// ���݂̍��W���擾
		XMFLOAT3 pos = carObj->GetPosition();

		// �ړ���̍��W���v�Z
		/*if (input->PushKey(DIK_SPACE)) { pos.y += 0.1f;}
		else if (input->PushKey(DIK_LCONTROL)) { pos.y -= 0.1f;}*/

		if (input->PushKey(DIK_RIGHT)) { pos.x += 0.1f;}
		else if (input->PushKey(DIK_LEFT)) { pos.x -= 0.1f;}
		
		if (input->PushKey(DIK_UP)) { pos.z += 0.1f; }
		else if (input->PushKey(DIK_DOWN)) { pos.z -= 0.1f; }

		ParticlesCreate({ pos.x - 2.0f,pos.y,pos.z });
		// ���W�̕ύX�𔽉f
		carObj->SetPosition(pos);
	}

	// �J�����ړ�
	/*if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
	{
		if (input->PushKey(DIK_W)) { cameraEye.y += 1.0f; }
		else if (input->PushKey(DIK_S)) { cameraEye.y -= 1.0f; }
		if (input->PushKey(DIK_D)) { cameraEye.x += 1.0f; }
		else if (input->PushKey(DIK_A)) { cameraEye.x -= 1.0f; }

		camera->SetEye(cameraEye);
	}*/

	//// �J�����ړ�
	if (input->PushKey(DIK_Q) || input->PushKey(DIK_E) || input->PushKey(DIK_LCONTROL) || input->PushKey(DIK_SPACE))
	{
		if (input->PushKey(DIK_SPACE)) { camera->CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_LCONTROL)) { camera->CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_E)) { camera->CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_Q)) { camera->CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
	}

	//�J�����p�x�ύX
	/*if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
	{
		if (input->PushKey(DIK_W)) { cameraTarget.y += 1.0f; }
		else if (input->PushKey(DIK_S)) { cameraTarget.y -= 1.0f; }
		if (input->PushKey(DIK_D)) { cameraTarget.x += 1.0f; }
		else if (input->PushKey(DIK_A)) { cameraTarget.x -= 1.0f; }
		camera->SetTarget(cameraTarget);
	}*/
	
	//���C�g
	/*static XMVECTOR lightDir = { 0, 1, 5, 0 };
	if (input->PushKey(DIK_W)) { lightDir.m128_f32[1] += 1.0f; }
	else if (input->PushKey(DIK_S)) { lightDir.m128_f32[1] -= 1.0f; }
	if (input->PushKey(DIK_D)) { lightDir.m128_f32[0] += 1.0f; }
	else if (input->PushKey(DIK_A)) { lightDir.m128_f32[0] -= 1.0f; }
	light->SetLightDir(lightDir);*/

	particle3d->Update();
	camera->Update();
	skydomeObj->Update();
	groundObj->Update();
	carObj->Update();
	light->Update();
	objFighter->Update();
	objSphere->Update();
	collisionManager->CheckAllCollisions();
}

void GameScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList *cmdList = dxCommon->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��
	//-------------------------------------------------------------//


	spriteBG->Draw();


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

	//playerObj->Draw();
	skydomeObj->Draw();
	groundObj->Draw();
	carObj->Draw();
	objFighter->Draw();
	objSphere->Draw();
	//-------------------------------------------------------------//
	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	particle3d->Draw(cmdList);
#pragma endregion

	
#pragma region �O�i�X�v���C�g�`��
	//// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	//-------------------------------------------------------------//




	//-------------------------------------------------------------//
	// �f�o�b�O�e�L�X�g�̕`��
	debugText.DrawAll(cmdList);
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion
}

void GameScene::ParticlesCreate(XMFLOAT3 Pos)
{
	for (int i = 0; i < 1; i++)
	{
		//X,Y,Z�S��{-5.0f,+5.0f}�Ń����_���ɕ��z
		const float md_pos = 0.5f;
		XMFLOAT3 pos = Pos;
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		////X,Y,Z�S��{-0.05f,+0.05f}�Ń����_���ɕ��z
		const float md_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		//�d�͂Ɍ����Ă�Y�̂�{-0.001f,0}�Ń����_�����z
		XMFLOAT3 acc{};
		const float md_acc = 0.001f;
		acc.y = (float)rand() / RAND_MAX * md_acc;

		const float colorR = 1.0f;
		const float colorG = 1.0f;
		const float colorB = 1.0f;
		// �ǉ�
		particle3d->Add(60, pos, vel, acc, 1.0f, 0.0f, { (float)rand() / RAND_MAX * colorR,(float)rand() / RAND_MAX * colorG,(float)rand() / RAND_MAX * colorB,1});
	}
}