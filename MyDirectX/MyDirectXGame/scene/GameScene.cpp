#include "GameScene.h"
#include "Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "Input.h"
#include "SoundVector.h"

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteTitle);
	safe_delete(spriteTitle2);
	safe_delete(spriteTitle3);
	safe_delete(spriteOption);
	safe_delete(spriteOption2);
	safe_delete(spriteOption3);
	safe_delete(spriteClear);
	safe_delete(spriteGAMEOVER);
	safe_delete(spriteRule);
	safe_delete(particle3d);
	safe_delete(light);
	safe_delete(player);
	safe_delete(enemy);
	safe_delete(map);
}

void GameScene::Initialize(DirectXCommon *dxCommon, Sound *audio)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
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
	if (!Sprite::LoadTexture(18, L"Resources/Title.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(21, L"Resources/Title2.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(22, L"Resources/Title3.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(19, L"Resources/Clear.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(20, L"Resources/GAMEOVER.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(23, L"Resources/Option.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(24, L"Resources/Option2.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(25, L"Resources/Option3.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(30, L"Resources/tutrial.png")) {
		assert(0);
		return;
	}
	//// �w�i�X�v���C�g����
	spriteTitle = Sprite::Create(18, { 0.0f,0.0f });
	spriteTitle2 = Sprite::Create(21, { 0.0f,0.0f });
	spriteTitle3 = Sprite::Create(22, { 0.0f,0.0f });
	spriteOption = Sprite::Create(23, { 0.0f,0.0f });
	spriteOption2 = Sprite::Create(24, { 0.0f,0.0f });
	spriteOption3 = Sprite::Create(25, { 0.0f,0.0f });
	spriteClear = Sprite::Create(19, { 0.0f,0.0f });
	spriteGAMEOVER = Sprite::Create(20, { 0.0f,0.0f });
	spriteRule = Sprite::Create(30, { 0.0f,0.0f });

	// 3D�I�u�W�F�N�g����

	// �f�o�C�X���Z�b�g
	FbxObject3d::SetDevice(dxCommon->GetDevice());
	// �J�������Z�b�g
	FbxObject3d::SetCamera(camera);
	// �O���t�B�b�N�X�p�C�v���C������
	FbxObject3d::CreateGraphicsPipeline();
	light = LightGroop::Create();
	
	Object3d::SetLightGroup(light);

	player = new Player;
	player->Initialize();
	map = new MapChip;
	map->Initialize();
	
	enemy = new Enemy;
	enemy->Initialize();
}

void GameScene::Update()
{
	int mapY = int((player->GetPos().z / 8) + ((21 + 1) / 2));
	int mapX = int((player->GetPos().x / 8) + ((21 + 1) / 2));
	//debugText.Print(20.0f, 20.0f, 2.0f, "%d %d", mapX,mapY);
	debugText.Print(20.0f, 20.0f, 2.0f, "%f %f", player->GetPos().x - enemy->GetPos().x, player->GetPos().z - enemy->GetPos().z);
	debugText.Print(20.0f, 40.0f, 2.0f, "%d",map->GetArrayValue(mapX,mapY));
	float vec = SoundVector::VectorSearch(enemy->GetPos().x, enemy->GetPos().z, player->GetPos().x, player->GetPos().z);
	float sideValue = 45;
	if(SoundVector::DistanceSearch(enemy->GetPos().x, enemy->GetPos().z, player->GetPos().x, player->GetPos().z))
	{
		if (-vec + player->GetAngle() - 90 < -90 + sideValue && -vec + player->GetAngle() - 90 > -90 - sideValue || -vec + player->GetAngle() - 90 > 270 - sideValue && -vec + player->GetAngle() - 90 < 270 + sideValue)
		{
			audio->PlaySE("Resources/seR.wav", false);
		}
		else if (-vec + player->GetAngle() - 90 > 90 - sideValue && -vec + player->GetAngle() - 90 < 90 + sideValue || -vec + player->GetAngle() - 90 < -270 + sideValue && -vec + player->GetAngle() - 90 > -270 - sideValue)
		{
			audio->PlaySE("Resources/seL.wav", false);
		}
		else
		{
			audio->PlaySE("Resources/seL.wav", false);
			audio->PlaySE("Resources/seR.wav", false);
		}
	}

	if (scene == TITLE)
	{	
		if (Input::GetInstance()->KeybordTrigger(DIK_W) && buttonNo != 0 || Input::GetInstance()->KeybordTrigger(DIK_UP) && buttonNo != 0)
		{
			buttonNo--;
		}

		else if (Input::GetInstance()->KeybordTrigger(DIK_S) && buttonNo != 2 || Input::GetInstance()->KeybordTrigger(DIK_DOWN) && buttonNo != 2)
		{
			buttonNo++;
		}
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE)&& buttonNo == 0)
		{
			player->InitializeValue();
			enemy->InitializeValue();
			map->InitializeValue();
			scene = PLAY;
		}
		else if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && buttonNo == 1)
		{
			scene = OPTION;
		}
	}
	else if (scene == OPTION)
	{
		if (Input::GetInstance()->KeybordTrigger(DIK_W) && optionButtonNo != 0 || Input::GetInstance()->KeybordTrigger(DIK_UP) && optionButtonNo != 0)
		{
			optionButtonNo--;
		}

		else if (Input::GetInstance()->KeybordTrigger(DIK_S) && optionButtonNo != 2 || Input::GetInstance()->KeybordTrigger(DIK_DOWN) && optionButtonNo != 2)
		{
			optionButtonNo++;
		}

		if (Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == 0)
		{
			player->SetViewSpeedPlus();
		}
		else if (Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == 0&& player->GetViewSpeed() >= 0.05)
		{
			player->SetViewSpeedMinus();
		}

		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == 1 && player->GetShakeFlag()||
			Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == 1 && player->GetShakeFlag()||
			Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == 1 && player->GetShakeFlag())
		{
			player->SetShakeFlag(false);
		}
		else if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == 1 && !player->GetShakeFlag() ||
			Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == 1 && !player->GetShakeFlag() ||
			Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == 1 && !player->GetShakeFlag())
		{
			player->SetShakeFlag(true);
		}

		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == 2)
		{
			scene = TITLE;
		}
	}
	else if (scene == PLAY)
	{
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && tutrialFlag == true)
		{
			tutrialFlag = false;
		}
		//�v���C���[�n
		camera->SetEye(player->GetPos());
		camera->SetTarget(player->GetTarget());

		//���C�g
		light->SetAmbientColor(XMFLOAT3(ambientColor0));

		light->SetDirLightDir(0, XMVECTOR({ lightDir0[0], lightDir0[1], lightDir0[2], 0 }));
		light->SetDirLightColor(0, XMFLOAT3(lightColor0));

		light->SetDirLightDir(1, XMVECTOR({ lightDir1[0], lightDir1[1], lightDir1[2], 0 }));
		light->SetDirLightColor(1, XMFLOAT3(lightColor1));

		light->SetDirLightDir(2, XMVECTOR({ lightDir2[0], lightDir2[1], lightDir2[2], 0 }));
		light->SetDirLightColor(2, XMFLOAT3(lightColor2));

		light->SetDirLightDir(3, XMVECTOR({ lightDir3[0], lightDir3[1], lightDir3[2], 0 }));
		light->SetDirLightColor(3, XMFLOAT3(lightColor3));

		light->SetDirLightDir(4, XMVECTOR({ lightDir4[0], lightDir4[1], lightDir4[2], 0 }));
		light->SetDirLightColor(4, XMFLOAT3(lightColor4));
		
		light->SetDirLightDir(5, XMVECTOR({ lightDir5[0], lightDir5[1], lightDir5[2], 0 }));
		light->SetDirLightColor(5, XMFLOAT3(lightColor5));
		player->Update(map,tutrialFlag,enemy->CatchCollision(player) == true);
		particle3d->Update();
		camera->Update();
		light->Update();
		map->Update(player->GetPos(),player->GetMapPos(),enemy->GetPos());
		stopFlag = map->GetStopFlag();
		enemy->Update(player, map,player->GetMapPos());
		if (enemy->DeathAnimation(player))
		{
			scene = GAMEOVER;
		}
		if (map->GetAllGetFlag())
		{
			scene = CLEAR;
		}
	}
	else if (scene == CLEAR)
	{
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
		{
			buttonNo = 0;
			scene = TITLE;
		}
	}
	else if (scene == GAMEOVER)
	{
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
		{
			buttonNo = 0;
			scene = TITLE;
		}
	}
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
	if (scene == TITLE || scene == PLAY)
	{

		map->Draw();
		enemy->Draw();
	}
	//-------------------------------------------------------------//
	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	particle3d->Draw(cmdList);
#pragma endregion

	
#pragma region �O�i�X�v���C�g�`��
	//// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	//-------------------------------------------------------------//
	if (scene == TITLE)
	{
		if (buttonNo == 0)
		{
			spriteTitle->Draw(1.0f);
		}
		else if (buttonNo == 1)
		{
			spriteTitle2->Draw(1.0f);
		}
		else if (buttonNo == 2)
		{
			spriteTitle3->Draw(1.0f);
		}
	}
	if (scene == OPTION)
	{
		debugText.Print(1300, 390, 2.0f, "%f", player->GetViewSpeed());
		if (player->GetShakeFlag())
		{
			debugText.Print(1335, 490, 2.0f, "ON");
		}
		else if (!player->GetShakeFlag())
		{
			debugText.Print(1325, 490, 2.0f, "OFF");
		}
		if (optionButtonNo == 0)
		{
			spriteOption->Draw(1.0f);
		}
		else if (optionButtonNo == 1)
		{
			spriteOption2->Draw(1.0f);
		}
		else if (optionButtonNo == 2)
		{
			spriteOption3->Draw(1.0f);
		}
	}
	if (scene == CLEAR)
	{
		spriteClear->Draw(1.0f);
	}
	if (scene == GAMEOVER)
	{
		spriteGAMEOVER->Draw(1.0f);
	}
	if (scene == PLAY)
	{
		
	}

	//-------------------------------------------------------------//
	// �f�o�b�O�e�L�X�g�̕`��
	debugText.DrawAll(cmdList);
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
#pragma endregion
}

void GameScene::PostOffDraw()
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

	particle3d->Draw(cmdList);
#pragma endregion


#pragma region �O�i�X�v���C�g�`��
	//// �O�i�X�v���C�g�`��O����
	Sprite::PreDraw(cmdList);
	//-------------------------------------------------------------//
	if (scene == PLAY)
	{
		map->DrawSprite();
		player->DrawSprite();
		enemy->DrawSprite(map);
		if (tutrialFlag == true) {
			spriteRule->Draw(1.0f);
		}
	}

	//-------------------------------------------------------------//
	// �f�o�b�O�e�L�X�g�̕`��
	debugText.DrawAll(cmdList);
	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();
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

		int time = 60;
		float s_scale = 1.0f;
		float e_scale = 1.0f;
		XMFLOAT4 color = { 1,1,1,1 };
		// �ǉ�
		particle3d->Add(time, pos, vel, acc, s_scale, e_scale, color);
	}
}
