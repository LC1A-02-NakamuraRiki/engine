#include "TitleScene.h"
#include "Input.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//// 背景スプライト生成
	spriteTitle[0] = std::unique_ptr<Sprite>(Sprite::Create(18, { 0.0f,0.0f }));
	spriteTitle[1] = std::unique_ptr<Sprite>(Sprite::Create(21, { 0.0f,0.0f }));
	spriteTitle[2] = std::unique_ptr<Sprite>(Sprite::Create(22, { 0.0f,0.0f }));
}

void TitleScene::Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light)
{
	//タイトルのディレイ初期化
	titleTime = 0;
	//マップ初期化
	map->InitializeValue();

	//選択
	if (Input::GetInstance()->KeybordTrigger(DIK_W) && buttonNo != FIRST || Input::GetInstance()->KeybordTrigger(DIK_UP) && buttonNo != FIRST)
	{
		buttonNo--;
	}
	else if (Input::GetInstance()->KeybordTrigger(DIK_S) && buttonNo != THIRD || Input::GetInstance()->KeybordTrigger(DIK_DOWN) && buttonNo != THIRD)
	{
		buttonNo++;
	}

	//プレイへ
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && buttonNo == FIRST)
	{
		player->InitializeValue();
		map->InitializeValue();
		playFlag = true;
	}
	//オプションへ
	else if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && buttonNo == SECOND)
	{
		optionFlag = true;
	}
	//プレイヤーの初期化と反映
	camera->SetEye(XMFLOAT3{ -4.0f,3.0f,4.0f });
	camera->SetTarget(XMFLOAT3{ -4.0f,3.0f,-8.0f });
	player->Update(map, tutrialFlag, enemy1->CatchCollision(player), enemy2->CatchCollision(player), enemy3->CatchCollision(player));
	camera->Update();
	//マップの反映
	light->Update();
	map->Update(player->GetPos(), player->GetMapPos(), enemy1->GetPos(), enemy2->GetPos(), enemy3->GetPos());

	//エネミー初期化と反映
	enemy1->InitializeValue();
	enemy2->InitializeValue2();
	enemy3->InitializeValue3();
	enemy1->Update(player, map, player->GetMapPos(), XMFLOAT2(0, 0), enemy2->CatchCollision(player), enemy3->CatchCollision(player));
	enemy2->Update(player, map, player->GetMapPos(), player->GetShortCut(map, enemy2->GetPos()), enemy1->CatchCollision(player), enemy3->CatchCollision(player));
	enemy3->Update(player, map, player->GetMapPos(), player->GetShortCut(map, enemy3->GetPos()), enemy1->CatchCollision(player), enemy2->CatchCollision(player));
}

void TitleScene::Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
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
			spriteTitle[i]->Draw(1.0f);//タイトルのスプライト
		}
	}
}

void TitleScene::Finalize()
{
}
