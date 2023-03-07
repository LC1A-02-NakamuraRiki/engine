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
}

void GameScene::Initialize(DirectXCommon *dxCommon, Sound *audio)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;

	camera = std::make_unique<DebugCamera>(DebugCamera(WinApp::window_width, WinApp::window_height));
	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(camera.get());

	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// �f�o�b�O�e�L�X�g������
	debugText.Initialize(debugTextTexNumber);
	particle3d = std::unique_ptr<ParticleManager>(ParticleManager::Create(dxCommon->GetDevice(), camera.get()));
	
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
	if (!Sprite::LoadTexture(20, L"Resources/GAMEOVER2.png")) {
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
	if (!Sprite::LoadTexture(50, L"Resources/grain.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(51, L"Resources/grain2.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(52, L"Resources/grain3.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(53, L"Resources/grain4.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(54, L"Resources/grain5.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(55, L"Resources/grain6.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(56, L"Resources/grain7.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(57, L"Resources/grain8.png")) {
		assert(0);
		return;
	}


	//// �w�i�X�v���C�g����
	spriteTitle[0] = std::unique_ptr<Sprite>(Sprite::Create(18, {0.0f,0.0f}));
	spriteTitle[1] = std::unique_ptr<Sprite>(Sprite::Create(21, {0.0f,0.0f}));
	spriteTitle[2] = std::unique_ptr<Sprite>(Sprite::Create(22, {0.0f,0.0f}));
	spriteOption[0] = std::unique_ptr<Sprite>(Sprite::Create(23, {0.0f,0.0f}));
	spriteOption[1] = std::unique_ptr<Sprite>(Sprite::Create(24, {0.0f,0.0f}));
	spriteOption[2] = std::unique_ptr<Sprite>(Sprite::Create(25, {0.0f,0.0f}));
	spriteClear = std::unique_ptr<Sprite>(Sprite::Create(19, { 0.0f,0.0f }));
	spriteGAMEOVER = std::unique_ptr<Sprite>(Sprite::Create(20, { 0.0f,0.0f }));
	spriteRule = std::unique_ptr<Sprite>(Sprite::Create(30, { 0.0f,0.0f }));
	for (int i = 0; i < 8; i++)
	{
		spriteGrain[i] = std::unique_ptr<Sprite>(Sprite::Create(50 + i, { 0.0f,0.0f }));
	}
	// �f�o�C�X���Z�b�g
	FbxObject3d::SetDevice(dxCommon->GetDevice());
	// �J�������Z�b�g
	FbxObject3d::SetCamera(camera.get());
	// �O���t�B�b�N�X�p�C�v���C������
	FbxObject3d::CreateGraphicsPipeline();
	light = std::unique_ptr<LightGroop>(LightGroop::Create());
	//���C�g�̃Z�b�g
	Object3d::SetLightGroup(light.get());

	//���C�g�֘A
	light->SetAmbientColor(XMFLOAT3({ ambientColor0[0],ambientColor0[1] ,ambientColor0[2]}));
	light->SetDirLightDir(0, XMVECTOR({ lightDir0[0], lightDir0[1], lightDir0[2], 0 }));
	light->SetDirLightColor(0, XMFLOAT3({ lightColor0[0],lightColor0[1] ,lightColor0[2] }));
	light->SetDirLightDir(1, XMVECTOR({ lightDir1[0], lightDir1[1], lightDir1[2], 0 }));
	light->SetDirLightColor(1, XMFLOAT3({ lightColor1[0],lightColor1[1] ,lightColor1[2] }));
	light->SetDirLightDir(2, XMVECTOR({ lightDir2[0], lightDir2[1], lightDir2[2], 0 }));
	light->SetDirLightColor(2, XMFLOAT3({ lightColor2[0],lightColor2[1] ,lightColor2[2] }));
	light->SetDirLightDir(3, XMVECTOR({ lightDir3[0], lightDir3[1], lightDir3[2], 0 }));
	light->SetDirLightColor(3, XMFLOAT3({ lightColor3[0],lightColor3[1] ,lightColor3[2] }));
	light->SetDirLightDir(4, XMVECTOR({ lightDir4[0], lightDir4[1], lightDir4[2], 0 }));
	light->SetDirLightColor(4, XMFLOAT3({ lightColor4[0],lightColor4[1] ,lightColor4[2] }));
	light->SetDirLightDir(5, XMVECTOR({ lightDir5[0], lightDir5[1], lightDir5[2], 0 }));
	light->SetDirLightColor(5, XMFLOAT3({ lightColor5[0],lightColor5[1] ,lightColor5[2] }));

	//�v���C���[������
	player = std::make_unique<Player>();
	player->Initialize();
	//�}�b�v������
	map = std::make_unique<MapChip>();
	map->Initialize();
	
	//�G������
	for (int i = 0; i < 3; i++){
		enemy[i] = std::make_unique < Enemy>();
		enemy[i]->Initialize();
	}
	

}

void GameScene::Update()
{
	if (scene == TITLE)
	{
		//�^�C�g���̃f�B���C������
		titleTime = 0;
		//�}�b�v������
		map->InitializeValue();
		
		//�I��
		if (Input::GetInstance()->KeybordTrigger(DIK_W) && buttonNo != 0 || Input::GetInstance()->KeybordTrigger(DIK_UP) && buttonNo != 0)
		{
			buttonNo--;
		}
		else if (Input::GetInstance()->KeybordTrigger(DIK_S) && buttonNo != 2 || Input::GetInstance()->KeybordTrigger(DIK_DOWN) && buttonNo != 2)
		{
			buttonNo++;
		}
		
		//�v���C��
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE)&& buttonNo == 0)
		{
			player->InitializeValue();

			map->InitializeValue();
			scene = PLAY;
		}
		//�I�v�V������
		else if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && buttonNo == 1)
		{
			scene = OPTION;
		}

		//�O���C��
		grainCount++;
		if (grainCount > 7)
		{
			grainCount = 0;
		}

		//�v���C���[�̏������Ɣ��f
		camera->SetEye(XMFLOAT3{ -4.0f,3.0f,4.0f });
		camera->SetTarget(XMFLOAT3{ -4.0f,3.0f,-8.0f });
		player->Update(map.get(), tutrialFlag, enemy[0]->CatchCollision(player.get()), enemy[1]->CatchCollision(player.get()), enemy[2]->CatchCollision(player.get()));
		camera->Update();
		//�}�b�v�̔��f
		light->Update();
		map->Update(player->GetPos(), player->GetMapPos(), enemy[0]->GetPos(), enemy[1]->GetPos(), enemy[2]->GetPos());
	
		//�G�l�~�[�������Ɣ��f
		enemy[0]->InitializeValue();
		enemy[1]->InitializeValue2();
		enemy[2]->InitializeValue3();
		enemy[0]->Update(player.get(), map.get(), player->GetMapPos(), XMFLOAT2(0, 0), enemy[1]->CatchCollision(player.get()), enemy[2]->CatchCollision(player.get()));
		enemy[1]->Update(player.get(), map.get(), player->GetMapPos(), player->GetShortCut(map.get(), enemy[1]->GetPos()), enemy[0]->CatchCollision(player.get()), enemy[2]->CatchCollision(player.get()));
		enemy[2]->Update(player.get(), map.get(), player->GetMapPos(), player->GetShortCut(map.get(), enemy[2]->GetPos()), enemy[0]->CatchCollision(player.get()), enemy[1]->CatchCollision(player.get()));
	}
	else if (scene == OPTION)
	{
		//�I��
		if (Input::GetInstance()->KeybordTrigger(DIK_W) && optionButtonNo != 0 || Input::GetInstance()->KeybordTrigger(DIK_UP) && optionButtonNo != 0)
		{
			optionButtonNo--;
		}
		else if (Input::GetInstance()->KeybordTrigger(DIK_S) && optionButtonNo != 2 || Input::GetInstance()->KeybordTrigger(DIK_DOWN) && optionButtonNo != 2)
		{
			optionButtonNo++;
		}

		//���x�ύX
		if (Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == 0)
		{
			player->SetViewSpeedPlus();
		}
		else if (Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == 0&& player->GetViewSpeed() >= 0.05)
		{
			player->SetViewSpeedMinus();
		}

		//�V�F�C�N�I�t
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == 1 && player->GetShakeFlag()||
			Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == 1 && player->GetShakeFlag()||
			Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == 1 && player->GetShakeFlag())
		{
			player->SetShakeFlag(false);
		}
		//�V�F�C�N�I��
		else if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == 1 && !player->GetShakeFlag() ||
			Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == 1 && !player->GetShakeFlag() ||
			Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == 1 && !player->GetShakeFlag())
		{
			player->SetShakeFlag(true);
		}

		//�^�C�g����
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == 2)
		{
			scene = TITLE;
		}
	}
	else if (scene == PLAY)
	{
		titleTime++;//�^�C�g���f�B���C
	
		//�v���C���[�̃J�����ƈړ�
		camera->SetEye(player->GetPos());
		camera->SetTarget(player->GetTarget());
		
		//�`���[�g���A��
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && tutrialFlag == true)
		{
			tutrialFlag = false;
		}

		//�v���C���[�̃A�b�v�f�[�g
		player->Update(map.get(),tutrialFlag,enemy[0]->CatchCollision(player.get()), enemy[1]->CatchCollision(player.get()), enemy[2]->CatchCollision(player.get()));
		
		//�J�����A�b�v�f�[�g
		camera->Update();
		
		//���C�g�A�b�v�f�[�g
		light->Update();
		
		//�}�b�v�A�b�v�f�[�g
		map->Update(player->GetPos(),player->GetMapPos(),enemy[0]->GetPos(), enemy[1]->GetPos(), enemy[2]->GetPos());
		
		//�G�l�~�[�A�b�v�f�[�g
		enemy[0]->Update(player.get(), map.get(), player->GetMapPos(), XMFLOAT2(0,0),enemy[1]->CatchCollision(player.get()), enemy[2]->CatchCollision(player.get()));
		enemy[1]->Update(player.get(), map.get(), player->GetMapPos(), player->GetShortCut(map.get(),enemy[1]->GetPos()), enemy[0]->CatchCollision(player.get()), enemy[2]->CatchCollision(player.get()));
		enemy[2]->Update(player.get(), map.get(), player->GetMapPos(), player->GetShortCut(map.get(), enemy[2]->GetPos()), enemy[0]->CatchCollision(player.get()), enemy[1]->CatchCollision(player.get()));

		//���C�g�_�Ŋ֘A
		for (int i = 0; i < 3; i++)
		{
			if (map->GetGateOpenFlag() && !enemy[0]->CatchCollision(player.get()) && !enemy[1]->CatchCollision(player.get()) && !enemy[2]->CatchCollision(player.get()))
			{
				float aX = enemy[i]->GetPos().x - player->GetPos().x;
				float aZ = enemy[i]->GetPos().z - player->GetPos().z;
				float aXZ = aX * aX + aZ * aZ;
				float axzDistanse = float(sqrt(aXZ));
				if (axzDistanse < 20.0f)
				{
					map->SetLightAction(true);
					i = 3;
				}
				else
				{
					map->SetLightAction(false);
				}
			}
		}

		//���֘A
		if (map->GetGateOpenFlag() && !enemy[0]->CatchCollision(player.get()) && !enemy[1]->CatchCollision(player.get()) && !enemy[2]->CatchCollision(player.get()))
		{
			for (int i = 0; i < 3; i++)
			{
				soundTimer[i]++;
				float vec = SoundVector::VectorSearch(enemy[i]->GetPos().x, enemy[i]->GetPos().z, player->GetPos().x, player->GetPos().z);
				float sideValue = 45;
				if (SoundVector::DistanceSearch(enemy[i]->GetPos().x, enemy[i]->GetPos().z, player->GetPos().x, player->GetPos().z) && soundTimer[i] > 20 && !map->GetStopFlag())
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
					soundTimer[i] = 0;
				}
			}
		}

		//�O���C���֘A
		grainCount++;
		if (grainCount > 7)
		{
			grainCount = 0;
		}

		//���S�A�j���[�V����
		for (int i = 0; i < 3; i++)
		{
			if (enemy[i]->DeathAnimation(player.get()))
			{
				scene = GAMEOVER;
			}
		}

		//�X�g�b�v�t���O
		stopFlag = map->GetStopFlag();

		//�N���X�^���S������
		if (map->GetAllGetFlag())
		{
			scene = CLEAR;//�N���A��
		}
	}
	else if (scene == CLEAR)
	{
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
		{
			//�^�C�g���ɖ߂�
			buttonNo = 0;
			scene = TITLE;
		}
	}
	else if (scene == GAMEOVER)
	{
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
		{
			//�^�C�g���ɖ߂�
			buttonNo = 0;
			scene = TITLE;
		}
	}
}

void GameScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList *cmdList = dxCommon->GetCommandList();

#pragma region �w�i�X�v���C�g�`��g
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
	if (scene == PLAY)
	{
		for (int i = 0; i < 3; i++)
		{
			if (titleTime > 5)
			{
				enemy[i]->Draw(player.get(),cmdList);//�G��3D�`��
			}
		}
		map->Draw();//�}�b�v��3D�`��
	}
	
	if (scene == TITLE)
	{
		map->Draw();//�}�b�v��3D�`��
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
		map->DrawSprite(player->GetPos());//�}�b�v�֘A�̃X�v���C�g
		player->DrawSprite();//�v���C���[�̃X�v���C�g
		for (int i = 0; i < 3; i++)
		{
			enemy[i]->DrawSprite(map.get());//�G�l�~�[�X�v���C�g
		}
		if (tutrialFlag == true) {
			spriteRule->Draw(1.0f);//���[���\���X�v���C�g
		}
		spriteGrain[grainCount]->Draw(0.75f);//�e�N�X�`���X�v���C�g
	}

	if (scene == TITLE)
	{
		spriteGrain[grainCount]->Draw(0.75f);//�e�N�X�`���X�v���C�g
		for (int i = 0; i < 3; i++)
		{
			if (buttonNo == i)
			{
				spriteTitle[i]->Draw(1.0f);//�^�C�g���̃X�v���C�g
			}
		}
	}
	if (scene == OPTION)
	{
		debugText.Print(1300, 390, 2.0f, "%f", player->GetViewSpeed());//�X�s�[�h�̃X�v���C�g
		if (player->GetShakeFlag())
		{
			debugText.Print(1335, 490, 2.0f, "ON");//ON�̃X�v���C�g
		}
		else if (!player->GetShakeFlag())
		{
			debugText.Print(1325, 490, 2.0f, "OFF");//OFF�̃X�v���C�g
		}
		for (int i = 0; i < 3; i++)
		{
			if (optionButtonNo == i)
			{
				spriteOption[i]->Draw(1.0f);//�I�v�V�����̃X�v���C�g
			}
		}
	}
	if (scene == CLEAR)
	{
		spriteClear->Draw(1.0f);//�N���A�̃X�v���C�g
	}
	if (scene == GAMEOVER)
	{
		spriteGAMEOVER->Draw(1.0f);//�Q�[���I�[�o�[�̃X�v���C�g
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
