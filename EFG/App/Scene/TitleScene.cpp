#include "TitleScene.h"
#include "Input.h"
#include "PlayScene.h"
#include"SceneManager.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize(DebugCamera* camera)
{
	//�w�i�X�v���C�g����
	spriteTitle[0] = std::unique_ptr<Sprite>(Sprite::Create(18, { 0.0f,0.0f }));
	spriteTitle[1] = std::unique_ptr<Sprite>(Sprite::Create(21, { 0.0f,0.0f }));
	spriteTitle[2] = std::unique_ptr<Sprite>(Sprite::Create(22, { 0.0f,0.0f }));

	//�J�����̏�����
	camera->SetEye(XMFLOAT3{ -4.0f,3.0f,4.0f });
	camera->SetTarget(XMFLOAT3{ -4.0f,3.0f,-8.0f });
	
}

void TitleScene::Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light)
{
	//�^�C�g���̃f�B���C������
	titleTime = 0;

	//�}�b�v������
	map->InitializeValue();

	//�Z���N�g�֘A
	ButtonSelect(player,map);

	//�J�����̍X�V
	 camera->Update();

	//�v���C���[�̏������Ɣ��f
	player->Update(map, tutrialFlag, enemy1->CatchCollision(player), enemy2->CatchCollision(player), enemy3->CatchCollision(player));
	
	//�}�b�v�̔��f
	light->Update();
	map->Update(player->GetPos(), player->GetMapPos(), enemy1->GetPos(), enemy2->GetPos(), enemy3->GetPos());

	//�G�l�~�[�������Ɣ��f
	InitializeEnemyStatus(player, map, enemy1, enemy2, enemy3);
}

void TitleScene::Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, ID3D12GraphicsCommandList* cmdList)
{
	map->Draw();
}

void TitleScene::DrawPost2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
}

void TitleScene::Draw2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	const int MAXBUTTON = 3;
	for (int i = 0; i < MAXBUTTON; i++)
	{
		if (buttonNo == i)
		{
			spriteTitle[i]->Draw(1.0f);//�^�C�g���̃X�v���C�g
		}
	}
}

void TitleScene::Finalize()
{
}

bool TitleScene::ButtonUp()
{
	if (Input::GetInstance()->KeybordTrigger(DIK_W) && buttonNo != FIRST){
		return true;
	}
	return false;
}

bool TitleScene::ButtonDown()
{
	if (Input::GetInstance()->KeybordTrigger(DIK_S) && buttonNo != THIRD) {
		return true;
	}
	return false;
}

void TitleScene::ButtonSelect(Player* player, MapChip* map)
{
	//�I��
	if (ButtonUp()) {
		buttonNo--;
	}
	else if (ButtonDown()) {
		buttonNo++;
	}

	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE)) {
		if (buttonNo == FIRST)
		{
			player->InitializeValue();
			map->InitializeValue();
			BaseScene* scene = new PlayScene();//�v���C��
			sceneManager_->SetNextScene(scene);
		}
		else if (buttonNo == SECOND){
			BaseScene* scene = new OptionScene();//�I�v�V������
			sceneManager_->SetNextScene(scene);
		}
		
	}
}

void TitleScene::InitializeEnemyStatus(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	enemy1->InitializeValue();
	enemy2->InitializeValue2();
	enemy3->InitializeValue3();
	enemy1->Update(player, map, player->GetMapPos(), XMFLOAT2(0, 0), enemy2->CatchCollision(player), enemy3->CatchCollision(player));
	enemy2->Update(player, map, player->GetMapPos(), player->GetShortCut(map, enemy2->GetPos()), enemy1->CatchCollision(player), enemy3->CatchCollision(player));
	enemy3->Update(player, map, player->GetMapPos(), player->GetShortCut(map, enemy3->GetPos()), enemy1->CatchCollision(player), enemy2->CatchCollision(player));
}
