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
	//値渡し
	this->dxCommon = dxCommon;
	this->audio = audio;

	//カメラのステータス初期化
	camera = std::make_unique<DebugCamera>(DebugCamera(WinApp::window_width, WinApp::window_height));
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera.get());

	// テクスチャ読み込み
	InitializeTexture();

	//グレインの初期化
	InitializeGrain();

	//FBXの初期化
	InitializeFBX();
	
	//ライトの初期化
	light = std::unique_ptr<LightGroop>(LightGroop::Create());

	//Objectにライトのセット
	Object3d::SetLightGroup(light.get());

	//アプリ部の初期化
	InitializeAppli();

	//シーンをタイトルに設定
	BaseScene* nowScene = new ClearScene();
	SetNextScene(nowScene);
}

void SceneManager::Update()
{
	//グレインのアップデート
	UpdateGrain();

	if (Input::GetInstance()->KeybordTrigger(DIK_5))
	{
		BaseScene* nowScene = new OptionScene();
		nowScene->InitializeBase();
		SetNextScene(nowScene);
	}
	//次のシーンの予約があるなら
	if (nextScene)
	{
		if (nowScene)
		{
			nowScene->Finalize();
			delete nowScene;
		}
		//シーン切り替え
		nowScene = nextScene;
		nextScene = nullptr;

		nowScene->SetSceneManager(this);
		//次のシーンを初期化する
		nowScene->Initialize();
	}

	//更新
	nowScene->Update(player.get(), map.get(), enemy[0].get(), enemy[1].get(), enemy[2].get(),camera.get(),light.get());
}

void SceneManager::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
#pragma region 背景スプライト描画g
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//-------------------------------------------------------------//
	nowScene->DrawPost2D(player.get(), map.get(), enemy[0].get(), enemy[1].get(), enemy[2].get());
	//-------------------------------------------------------------//
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion
#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);
	//-------------------------------------------------------------//
	nowScene->Draw3D(player.get(), map.get(), enemy[0].get(), enemy[1].get(), enemy[2].get(),cmdList);
	//-------------------------------------------------------------//
	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion
#pragma region 前景スプライト描画
	//// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	//-------------------------------------------------------------//
	//-------------------------------------------------------------//
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}

void SceneManager::PostOffDraw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//-------------------------------------------------------------//
	//-------------------------------------------------------------//
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);
	//-------------------------------------------------------------//
	//-------------------------------------------------------------//
	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion
#pragma region 前景スプライト描画
	//// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	//-------------------------------------------------------------//
	nowScene->Draw2D(player.get(), map.get(), enemy[0].get(), enemy[1].get(), enemy[2].get());
	//-------------------------------------------------------------//
	// デバッグテキストの描画
	nowScene->DrawDebugText(cmdList);
	// スプライト描画後処理
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
	//グレインテクスチャのステータス初期化
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
	// デバイスをセット
	FbxObject3d::SetDevice(dxCommon->GetDevice());
	// カメラをセット
	FbxObject3d::SetCamera(camera.get());
	// グラフィックスパイプライン生成
	FbxObject3d::CreateGraphicsPipeline();
}

void SceneManager::InitializeAppli()
{
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
}

void SceneManager::UpdateGrain()
{
	//グレイン
	const int MAXGARAIN = 7;
	for (int i = 0; i < 3; i++){
		grainCount[i]++;
		if (grainCount[i] > MAXGARAIN){
			grainCount[i] = 0;
		}
	}
}
