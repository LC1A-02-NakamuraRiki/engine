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
	camera = std::make_unique<DebugCamera>(DebugCamera(WinApp::window_width, WinApp::window_height));
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera.get());

	light = std::unique_ptr<LightGroop>(LightGroop::Create());
	//ライトのセット
	Object3d::SetLightGroup(light.get());
	
	//ライト関連
	light->SetAmbientColor(XMFLOAT3({ ambientColor0[0],ambientColor0[1] ,ambientColor0[2] }));
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
	//プレイヤー初期化
	player = std::make_unique<Player>();
	player->Initialize();
	//マップ初期化
	map = std::make_unique<MapChip>();
	map->Initialize();

	//敵初期化
	const int MAXENEMYNUM = 3;
	for (int i = 0; i < MAXENEMYNUM; i++) {
		enemy[i] = std::make_unique <Enemy>();
		enemy[i]->Initialize();
	}

	//// 背景スプライト生成
	spriteTitle[0] = std::unique_ptr<Sprite>(Sprite::Create(18, { 0.0f,0.0f }));
	spriteTitle[1] = std::unique_ptr<Sprite>(Sprite::Create(21, { 0.0f,0.0f }));
	spriteTitle[2] = std::unique_ptr<Sprite>(Sprite::Create(22, { 0.0f,0.0f }));

	map = std::make_unique<MapChip>();
	map->Initialize();

	player->InitializeValue();
	map->InitializeValue();

}

void TitleScene::Update()
{
	////選択
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
	player->Update(map.get(), tutrialFlag, enemy[0]->CatchCollision(player.get()), enemy[1]->CatchCollision(player.get()), enemy[2]->CatchCollision(player.get()));
	camera->Update();
	//マップの反映
	light->Update();
	map->Update(player->GetPos(), player->GetMapPos(), enemy[0]->GetPos(), enemy[1]->GetPos(), enemy[2]->GetPos());

	//エネミー初期化と反映
	enemy[0]->InitializeValue();
	enemy[1]->InitializeValue2();
	enemy[2]->InitializeValue3();
	enemy[0]->Update(player.get(), map.get(), player->GetMapPos(), XMFLOAT2(0, 0), enemy[1]->CatchCollision(player.get()), enemy[2]->CatchCollision(player.get()));
	enemy[1]->Update(player.get(), map.get(), player->GetMapPos(), player->GetShortCut(map.get(), enemy[1]->GetPos()), enemy[0]->CatchCollision(player.get()), enemy[2]->CatchCollision(player.get()));
	enemy[2]->Update(player.get(), map.get(), player->GetMapPos(), player->GetShortCut(map.get(), enemy[2]->GetPos()), enemy[0]->CatchCollision(player.get()), enemy[1]->CatchCollision(player.get()));
}

void TitleScene::Draw(ID3D12GraphicsCommandList* cmdList)
{
	map->Draw();//マップの3D描画
}

void TitleScene::SpriteDraw()
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
