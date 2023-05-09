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
#include "OptionScene.h"
#include "PlayScene.h"
#include "ClearScene.h"
#include "GameOverScene.h"

using namespace DirectX;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	scene_->Finalize();
	delete scene_;
}

void SceneManager::Initialize(DirectXCommon* dxCommon, Sound* audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;

	camera = std::make_unique<DebugCamera>(DebugCamera(WinApp::window_width, WinApp::window_height));
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera.get());

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);
	particle3d = std::unique_ptr<ParticleManager>(ParticleManager::Create(dxCommon->GetDevice(), camera.get()));

	//スプライト
	// テクスチャ読み込み
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

	if (!Sprite::LoadTexture(100, L"Resources/alartGrain.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(101, L"Resources/alartGrain2.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(102, L"Resources/alartGrain3.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(103, L"Resources/alartGrain4.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(104, L"Resources/alartGrain5.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(105, L"Resources/alartGrain6.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(106, L"Resources/alartGrain7.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(107, L"Resources/alartGrain8.png")) {
		assert(0);
		return;
	}
	const int MAXGRAINVALUE = 8;
	for (int i = 0; i < MAXGRAINVALUE; i++)
	{
		spriteGrain[i] = std::unique_ptr<Sprite>(Sprite::Create(50 + i, { 0.0f,0.0f }));
		spriteGrain[i]->SetSize(XMFLOAT2{ 1920.0f * 1.5f,1080.0f * 1.5f });
		spriteAlartGrain1[i] = std::unique_ptr<Sprite>(Sprite::Create(100 + i, { 0.0f,0.0f }));
		spriteAlartGrain1[i]->SetSize(XMFLOAT2{ 1920.0f * 4.0f,1080.0f * 4.0f });
		spriteAlartGrain2[i] = std::unique_ptr<Sprite>(Sprite::Create(100 + i, { 0.0f,0.0f }));
		spriteAlartGrain2[i]->SetSize(XMFLOAT2{ 1920.0f * 5.0f,1080.0f * 5.0f });
	}
	// デバイスをセット
	FbxObject3d::SetDevice(dxCommon->GetDevice());
	// カメラをセット
	FbxObject3d::SetCamera(camera.get());
	// グラフィックスパイプライン生成
	FbxObject3d::CreateGraphicsPipeline();
	
	titleScene = std::make_unique<TitleScene>();
	titleScene->Initialize();

	optionScene = std::make_unique<OptionScene>();
	optionScene->Initialize();

	playScene = std::make_unique<PlayScene>();
	playScene->Initialize();

	clearScene = std::make_unique<ClearScene>();
	clearScene->Initialize();

	gameOverScene = std::make_unique<GameOverScene>();
	gameOverScene->Initialize();



	//シーンをタイトルに設定
	BaseScene* scene = new PlayScene();
	SetNextScene(scene);
}

void SceneManager::Update()
{
	/*float mapY = player->GetShortCut(map.get(), enemy[1]->GetPos()).y;
	float mapX = player->GetShortCut(map.get(), enemy[1]->GetPos()).x;
	debugText.Print(20.0f, 20.0f, 2.0f, "%f", mapX);
	debugText.Print(20.0f, 60.0f, 2.0f, "%f", mapY);*/

	//グレイン
	const int MAXGARAIN = 7;
	grainCount++;
	if (grainCount > MAXGARAIN)
	{
		grainCount = 0;
	}

	grainCount2++;
	if (grainCount2 > MAXGARAIN)
	{
		grainCount2 = 0;
	}
	grainCount3++;
	if (grainCount3 > MAXGARAIN)
	{
		grainCount3 = 0;
	}

	//次のシーンの予約があるなら
	if (nextScene_)
	{
		if (scene_)
		{
			scene_->Finalize();
			delete scene_;
		}
		//シーン切り替え
		scene_ = nextScene_;
		nextScene_ = nullptr;

		scene_->SetSceneManager(this);
		//次のシーンを初期化する
		scene_->Initialize();
	}

	//更新
	scene_->Update();
	
	//scene_->Update(player.get(), map.get(), enemy[0].get(), enemy[1].get(), enemy[2].get(), camera.get(), light.get(), playScene->GetTutrialFlag(), audio);
	

	/*if (scene == TITLE)
	{
		titleScene->Update(player.get(), map.get(), enemy[0].get(),enemy[1].get(),enemy[2].get(),camera.get(),light.get(),playScene->GetTutrialFlag(), audio);
		if (titleScene->GetPlayScene()){
			scene = PLAY;
		}
		else if (titleScene->GetOptionScene()){
			optionScene->SetTitleScene();
			scene = OPTION;
		}
		alartValue = 0;
	}
	else if (scene == OPTION)
	{
		optionScene->Update(player.get());
		if (optionScene->GetTitleScene()) {
			titleScene->SetOptionScene();
			scene = TITLE;
		}
	}
	else if (scene == PLAY)
	{
		alartValue = playScene->GetArartValue();
		titleScene->SetPlayScene();
		playScene->Update(player.get(), map.get(), enemy[0].get(), enemy[1].get(), enemy[2].get(), camera.get(), light.get(), playScene->GetTutrialFlag(), audio);
		
		if (playScene->GetClearScene()) {
			titleScene->SetPlayScene();
			scene = CLEAR;
		}

		if (playScene->GetGameOverScene()) {
			titleScene->SetPlayScene();
			scene = GAMEOVER;
		}
		stopFlag = playScene->GetStopFlag();
	}
	else if (scene == CLEAR)
	{
		playScene->SetGameOverScene();
		playScene->SetClearScene();
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
		{
			scene = TITLE;
		}
	}
	else if (scene == GAMEOVER)
	{
		playScene->SetGameOverScene();
		playScene->SetClearScene();
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
		{
			scene = TITLE;
		}
	}*/
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
	//if (scene == PLAY)
	//{
	//	playScene->Draw(cmdList,player.get(), map.get(),enemy[0].get(), enemy[1].get(), enemy[2].get());
	//}

	//if (scene == TITLE)
	//{
	//	map->Draw();//マップの3D描画
	//}
	scene_->Draw(cmdList);
	//-------------------------------------------------------------//
	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

	particle3d->Draw(cmdList);
#pragma endregion


#pragma region 前景スプライト描画
	//// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	//-------------------------------------------------------------//


	//-------------------------------------------------------------//
	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
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

	particle3d->Draw(cmdList);
#pragma endregion


#pragma region 前景スプライト描画
	//// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	//-------------------------------------------------------------//
	spriteGrain[grainCount3]->Draw(1.0f);//テクスチャスプライト
	scene_->SpriteDraw();

	//if (scene == PLAY)
	//{
	//	if (!alartValue == 0){
	//		spriteAlartGrain2[grainCount]->Draw(1.0f);//テクスチャスプライト
	//		spriteAlartGrain1[grainCount2]->Draw(1.0f);//テクスチャスプライト
	//	}
	//	spriteGrain[grainCount3]->Draw(1.0f);//テクスチャスプライト
	//	playScene->DrawSprite(player.get(), map.get(), enemy[0].get(), enemy[1].get(), enemy[2].get());
	//}

	//if (scene == TITLE)
	//{
	//	spriteGrain[grainCount3]->Draw(1.0f);//テクスチャスプライト
	//	titleScene->Draw();
	//}
	//if (scene == OPTION)
	//{
	//	debugText.Print(1300, 390, 2.0f, "%f", player->GetViewSpeed());//スピードのスプライト
	//	if (player->GetShakeFlag())
	//	{
	//		debugText.Print(1335, 490, 2.0f, "ON");//ONのスプライト
	//	}
	//	else if (!player->GetShakeFlag())
	//	{
	//		debugText.Print(1325, 490, 2.0f, "OFF");//OFFのスプライト
	//	}
	//	optionScene->Draw();
	//}
	//if (scene == CLEAR)
	//{
	//	clearScene->Draw();
	//	
	//}
	//if (scene == GAMEOVER)
	//{
	//	gameOverScene->Draw();
	//}
	

	//-------------------------------------------------------------//
	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
	// スプライト描画後処理
	Sprite::PostDraw();
}

void SceneManager::ParticlesCreate(XMFLOAT3 Pos)
{
	for (int i = 0; i < 1; i++)
	{
		//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
		const float md_pos = 0.5f;
		XMFLOAT3 pos = Pos;
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		////X,Y,Z全て{-0.05f,+0.05f}でランダムに分布
		const float md_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		//重力に見立ててYのみ{-0.001f,0}でランダム分布
		XMFLOAT3 acc{};
		const float md_acc = 0.001f;
		acc.y = (float)rand() / RAND_MAX * md_acc;

		int time = 60;
		float s_scale = 1.0f;
		float e_scale = 1.0f;
		XMFLOAT4 color = { 1,1,1,1 };
		// 追加
		particle3d->Add(time, pos, vel, acc, s_scale, e_scale, color);
	}
}
