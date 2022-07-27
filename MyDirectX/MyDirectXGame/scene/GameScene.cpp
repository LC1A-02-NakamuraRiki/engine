#include "../Scene/GameScene.h"
#include "../collision/Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "../3d/FbxLoader.h"
#include "../3d/FbxObject3d.h"
#include "../input/Input.h"

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteBG);
	safe_delete(particle3d);
	safe_delete(objSkydome);
	safe_delete(modelSkydome);
	safe_delete(objGround);
	safe_delete(modelGround);
	safe_delete(light);
	//safe_delete(object1);
	//safe_delete(model1);
	safe_delete(player);
	safe_delete(enemy);
	safe_delete(map);
	//safe_delete(modelMapWall);
	/*for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			safe_delete(objMapWall[y][x]);
		}
	}*/
}

void GameScene::Initialize(DirectXCommon *dxCommon, Sound *audio)
{
	// nullptrチェック
	assert(dxCommon);
	//assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	//this->input = input;
	this->audio = audio;

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	particle3d = ParticleManager::Create(dxCommon->GetDevice(), camera);
	
	//スプライト
	// テクスチャ読み込み
	if (!Sprite::LoadTexture(1, L"Resources/background.png")) {
		assert(0);
		return;
	}
	//// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	
	// 3Dオブジェクト生成
	modelSkydome = Model::CreateFromObject("skydome", false);
	objSkydome = Object3d::Create(modelSkydome);
	objSkydome->SetScale({5.0f,5.0f,5.0f});
	modelGround = Model::CreateFromObject("ground", true);
	objGround = Object3d::Create(modelGround);
	objGround->SetScale({ 2.0f,2.0f ,2.0f });

	// モデル名を指定してファイル読み込み
	//model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	// デバイスをセット
	FbxObject3d::SetDevice(dxCommon->GetDevice());
	// カメラをセット
	FbxObject3d::SetCamera(camera);
	// グラフィックスパイプライン生成
	FbxObject3d::CreateGraphicsPipeline();
	light = Light::Create();
	light->SetLightColor({ 1.0f,0.8f,0.8f});
	
	Object3d::SetLight(light);

	/*object1 = new FbxObject3d;
	object1->Initialize();
	object1->SetModel(model1);
	object1->PlayAnimation();*/
	////サウンド再生
	//audio->PlayBGM("Resources/Alarm01.wav", true);
	//audio->PlaySE("Resources/Alarm01.wav", false);
	//audio->StopBGM();
	player = new Player;

	map = new MapChip;
	map->Initialize();
	
	enemy = new Enemy;
	enemy->Initialize();
}

void GameScene::Update()
{
	////マウスの座標
	///*POINT mousePos;
	//GetCursorPos(&mousePos);*/
	


	debugText.Print(20, 20, 2.0f, "END : ESC");
	if (scene == TITLE)
	{
		debugText.Print(680, 300, 5.0f, "ESCAPE fom BOM");
		debugText.Print(700, 800, 5.0f, "START : SPACE");
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
		{
			scene = PLAY;
		}
	}
	else if (scene == PLAY)
	{
		debugText.Print(20, 50, 2.0f, "MOVE : W A S D");
		debugText.Print(20, 80, 2.0f, "VIEW : MOUSE or ArrowKey ");
		debugText.Print(20, 110, 2.0f, "SENSI CHANGE -/+  :  9/0 ");
		debugText.Print(20, 140, 2.0f, "NowSENSI :  %f", player->GetViewSpeed());

		//プレイヤー系
		camera->SetEye(player->GetPos());
		camera->SetTarget(player->GetTarget());
		//ライト
		static XMVECTOR lightDir = { 0.5f, -1, 0, 0 };
		/*if (input->PushKey(DIK_W)) { lightDir.m128_f32[1] += 1.0f; }
		else if (input->PushKey(DIK_S)) { lightDir.m128_f32[1] -= 1.0f; }
		if (input->PushKey(DIK_D)) { lightDir.m128_f32[0] += 1.0f; }
		else if (input->PushKey(DIK_A)) { lightDir.m128_f32[0] -= 1.0f; }*/

		light->SetLightDir(lightDir);
		player->Update(map);
		particle3d->Update();
		camera->Update();
		objSkydome->Update();
		objGround->Update();
		light->Update();
		//object1->Update();
		map->Update();
		enemy->Update(player, map);
		if (enemy->catchCollision(player))
		{
			scene = GAMEOVER;
		}
	}
	else if (scene == GAMEOVER)
	{
		debugText.Print(680, 300, 5.0f, "   GAMEOVER");
		debugText.Print(700, 800, 5.0f, "TITLE : SPACE");
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
		{
			scene = TITLE;
		}
	}
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList *cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//-------------------------------------------------------------//
	//spriteBG->Draw();
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
	//playerObj->Draw();
	objSkydome->Draw();
	objGround->Draw();
	map->Draw();
	enemy->Draw();
	//objFighter->Draw();
	//object1->Draw(cmdList);
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

void GameScene::ParticlesCreate(XMFLOAT3 Pos)
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
