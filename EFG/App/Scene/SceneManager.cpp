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
	//値渡し
	this->dxCommon = dxCommon;

	//カメラのステータス初期化
	camera = std::make_unique<DebugCamera>(DebugCamera(WinApp::window_width, WinApp::window_height));
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera.get());

	// テクスチャ読み込み
	TextureManager::LoadTexture();

	//FBXの初期化
	InitializeFBX();
	
	//ライトの初期化
	light = std::unique_ptr<LightGroop>(LightGroop::Create());

	//Objectにライトのセット
	Object3d::SetLightGroup(light.get());

	//アプリ部の初期化
	InitializeAppli();

	//シーンをタイトルに設定
	BaseScene* nowScene = new TitleScene();
	nowScene->InitializeBase();
	SetNextScene(nowScene);
	
}

void SceneManager::Update()
{
	//次のシーンの予約があるなら
	if (nextScene){
		if (nowScene){
			nowScene->Finalize();
			delete nowScene;
		}
		//シーン切り替え
		nowScene = nextScene;
		nextScene = nullptr;

		nowScene->SetSceneManager(this);
		//次のシーンを初期化する
		nowScene->Initialize(camera.get());
		nowScene->InitializeBase();
	}

	//更新
	nowScene->Update(player.get(), map.get(), enemy[0].get(), enemy[1].get(), enemy[2].get(),camera.get(),light.get());
	//グレインのアップデート
	nowScene->UpdateGrain();
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
	nowScene->DrawGrain();
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