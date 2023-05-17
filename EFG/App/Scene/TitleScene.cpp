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
	//背景スプライト生成
	spriteTitle[0] = std::unique_ptr<Sprite>(Sprite::Create(18, { 0.0f,0.0f }));
	spriteTitle[1] = std::unique_ptr<Sprite>(Sprite::Create(21, { 0.0f,0.0f }));
	spriteTitle[2] = std::unique_ptr<Sprite>(Sprite::Create(22, { 0.0f,0.0f }));

	//カメラの初期化
	camera->SetEye(XMFLOAT3{ -4.0f,3.0f,4.0f });
	camera->SetTarget(XMFLOAT3{ -4.0f,3.0f,-8.0f });
	
}

void TitleScene::Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light)
{
	//タイトルのディレイ初期化
	titleTime = 0;

	//マップ初期化
	map->InitializeValue();

	//セレクト関連
	ButtonSelect(player,map);

	//カメラの更新
	 camera->Update();

	//プレイヤーの初期化と反映
	player->Update(map, tutrialFlag, enemy1->CatchCollision(player), enemy2->CatchCollision(player), enemy3->CatchCollision(player));
	
	//マップの反映
	light->Update();
	map->Update(player->GetPos(), player->GetMapPos(), enemy1->GetPos(), enemy2->GetPos(), enemy3->GetPos());

	//エネミー初期化と反映
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
			spriteTitle[i]->Draw(1.0f);//タイトルのスプライト
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
	//選択
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
			BaseScene* scene = new PlayScene();//プレイへ
			sceneManager_->SetNextScene(scene);
		}
		else if (buttonNo == SECOND){
			BaseScene* scene = new OptionScene();//オプションへ
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
