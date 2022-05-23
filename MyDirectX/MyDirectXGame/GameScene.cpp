#include "GameScene.h"
#include "Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "FbxLoader.h"
#include "FbxObject3d.h"
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
	safe_delete(objFighter);
	safe_delete(modelFighter);
	safe_delete(light);
	safe_delete(object1);
	safe_delete(model1);
}

void GameScene::Initialize(DirectXCommon *dxCommon, Input *input, Audio *audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);
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
	modelGround = Model::CreateFromObject("ground", true);
	objGround = Object3d::Create(modelGround);

	modelFighter = Model::CreateFromObject("largeCarL", true);
	objFighter = Object3d::Create(modelFighter);
	
	// モデル名を指定してファイル読み込み
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");

	// デバイスをセット
	FbxObject3d::SetDevice(dxCommon->GetDevice());
	// カメラをセット
	FbxObject3d::SetCamera(camera);
	// グラフィックスパイプライン生成
	FbxObject3d::CreateGraphicsPipeline();
	light = Light::Create();
	light->SetLightColor({ 1.0f,0.8f,0.8f});
	
	Object3d::SetLight(light);

	object1 = new FbxObject3d;
	object1->Initialize();
	object1->SetModel(model1);
	////サウンド再生
	//audio->PlayBGM("Resources/Alarm01.wav", true);
	//audio->PlaySE("Resources/Alarm01.wav", false);
	//audio->StopBGM();
}

void GameScene::Update()
{
	////マウスの座標
	///*POINT mousePos;
	//GetCursorPos(&mousePos);*/

	debugText.Print(20, 20, 1.5f,"ObjectMove:ArrowKey");
	debugText.Print(20, 50, 1.5f,"EyeMove:W A S D");
	debugText.Print(20, 80, 1.5f,"EyeTarget:SPACE Q LCONTROL E");
	XMFLOAT3 cameraEye = camera->GetEye();
	XMFLOAT3 cameraTarget = camera->GetTarget();

	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT) || input->PushKey(DIK_SPACE) || input->PushKey(DIK_LCONTROL))
	{
		// 現在の座標を取得
		XMFLOAT3 pos = objFighter->GetPosition();

		// 移動後の座標を計算
		if (input->PushKey(DIK_SPACE)) { pos.y += 0.1f;}
		else if (input->PushKey(DIK_LCONTROL)) { pos.y -= 0.1f;}

		if (input->PushKey(DIK_RIGHT)) { pos.x += 0.1f;}
		else if (input->PushKey(DIK_LEFT)) { pos.x -= 0.1f;}
		
		if (input->PushKey(DIK_UP)) { pos.z += 0.1f; }
		else if (input->PushKey(DIK_DOWN)) { pos.z -= 0.1f; }

		ParticlesCreate({ pos.x - 2.0f,pos.y,pos.z });
		// 座標の変更を反映
		objFighter->SetPosition(pos);
	}

	// カメラ移動
	/*if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
	{
		if (input->PushKey(DIK_W)) { cameraEye.y += 1.0f; }
		else if (input->PushKey(DIK_S)) { cameraEye.y -= 1.0f; }
		if (input->PushKey(DIK_D)) { cameraEye.x += 1.0f; }
		else if (input->PushKey(DIK_A)) { cameraEye.x -= 1.0f; }

		camera->SetEye(cameraEye);
	}*/

	//// カメラ移動
	if (input->PushKey(DIK_Q) || input->PushKey(DIK_E) || input->PushKey(DIK_LCONTROL) || input->PushKey(DIK_SPACE))
	{
		if (input->PushKey(DIK_SPACE)) { camera->CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_LCONTROL)) { camera->CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_E)) { camera->CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_Q)) { camera->CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
	}

	//カメラ角度変更
	/*if (input->PushKey(DIK_W) || input->PushKey(DIK_A) || input->PushKey(DIK_S) || input->PushKey(DIK_D))
	{
		if (input->PushKey(DIK_W)) { cameraTarget.y += 1.0f; }
		else if (input->PushKey(DIK_S)) { cameraTarget.y -= 1.0f; }
		if (input->PushKey(DIK_D)) { cameraTarget.x += 1.0f; }
		else if (input->PushKey(DIK_A)) { cameraTarget.x -= 1.0f; }
		camera->SetTarget(cameraTarget);
	}*/
	
	//ライト
	/*static XMVECTOR lightDir = { 0, 1, 5, 0 };
	if (input->PushKey(DIK_W)) { lightDir.m128_f32[1] += 1.0f; }
	else if (input->PushKey(DIK_S)) { lightDir.m128_f32[1] -= 1.0f; }
	if (input->PushKey(DIK_D)) { lightDir.m128_f32[0] += 1.0f; }
	else if (input->PushKey(DIK_A)) { lightDir.m128_f32[0] -= 1.0f; }
	light->SetLightDir(lightDir);*/
	
	particle3d->Update();
	camera->Update();
	objSkydome->Update();
	objGround->Update();
	objFighter->Update();
	light->Update();
	object1->Update();
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


	spriteBG->Draw();


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
	objFighter->Draw();
	object1->Draw(cmdList);
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

		// 追加
		particle3d->Add(60, pos, vel, acc, 1.0f, 1.0f, {1,1,1,1});
	}
}