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
	safe_delete(objFighter);
	safe_delete(modelFighter);
	safe_delete(light);
	safe_delete(object1);
	safe_delete(model1);
	safe_delete(objSphere1);
	safe_delete(modelSphere1);
	safe_delete(objSphere2);
	safe_delete(modelSphere2);
	safe_delete(objSphere3);
	safe_delete(modelSphere3);
	safe_delete(objGround);
	safe_delete(modelGround);
	safe_delete(objGround);
	safe_delete(modelGround);
	safe_delete(player);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Sound* audio)
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
	ToonObject3d::SetCamera(camera);
	PhongObject3d::SetCamera(camera);

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
	objSkydome->SetScale({ 1, 1, 1 });
	objSkydome->SetPosition({ 0, 2, -40 });

	modelSphere1 = Model::CreateFromObject("sphere", true);
	objSphere1 = Object3d::Create(modelSphere1);
	objSphere1->SetScale({ 1, 1, 1 });
	objSphere1->SetPosition({ -10, 2, 0 });

	modelSphere2 = Model::CreateFromObject("sphere", true);
	objSphere2 = ToonObject3d::Create(modelSphere2);
	objSphere2->SetScale({ 1, 1, 1 });
	objSphere2->SetPosition({ 10, 2, 0 });

	modelSphere3 = Model::CreateFromObject("sphere", true);
	objSphere3 = PhongObject3d::Create(modelSphere2);
	objSphere3->SetScale({ 1, 1, 1 });
	objSphere3->SetPosition({ 0, 2, 0 });

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
	light->SetLightColor({ 1.0f,1.0f,1.0f });

	Object3d::SetLight(light);
	ToonObject3d::SetLight(light);
	PhongObject3d::SetLight(light);
	object1 = new FbxObject3d;
	object1->Initialize();
	object1->SetModel(model1);
	object1->PlayAnimation();
	////サウンド再生
	//audio->PlayBGM("Resources/Alarm01.wav", true);
	//audio->PlaySE("Resources/Alarm01.wav", false);
	//audio->StopBGM();
	player = new Player;

}

void GameScene::Update()
{
	////マウスの座標
	///*POINT mousePos;
	//GetCursorPos(&mousePos);*/

	debugText.Print(20, 20, 1.5f, "ObjectMove:ArrowKey");
	debugText.Print(20, 50, 1.5f, "EyeMove:W A S D");

	XMFLOAT3 cameraEye = camera->GetEye();
	XMFLOAT3 cameraTarget = camera->GetTarget();
	if (Input::GetInstance()->ControllerPush(Button01))
	{

	}
	//プレイヤー系
	player->Update();
	camera->SetEye(player->GetPos());
	camera->SetTarget(player->GetTarget());
	debugText.Print(20, 80, 1.5f, "%f %f", cameraTarget.x, cameraTarget.z);
	// オブジェクト移動
	//if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT) || input->PushKey(DIK_SPACE) || input->PushKey(DIK_LCONTROL))
	//{
	//	// 現在の座標を取得
	//	XMFLOAT3 pos = objFighter->GetPosition();

	//	// 移動後の座標を計算
	//	if (input->PushKey(DIK_SPACE)) { pos.y += 0.1f;}
	//	else if (input->PushKey(DIK_LCONTROL)) { pos.y -= 0.1f;}

	//	if (input->PushKey(DIK_RIGHT)) { pos.x += 0.1f;}
	//	else if (input->PushKey(DIK_LEFT)) { pos.x -= 0.1f;}
	//	
	//	if (input->PushKey(DIK_UP)) { pos.z += 0.1f; }
	//	else if (input->PushKey(DIK_DOWN)) { pos.z -= 0.1f; }

	//	ParticlesCreate({ pos.x - 2.0f,pos.y,pos.z });
	//	// 座標の変更を反映
	//	objFighter->SetPosition(pos);
	//}
	/*if (Input::GetInstance()->PushKey(DIK_SPACE))
	{
		cameraEye.y += 1.0f;
	}*/


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
	/*if (Input::GetInstance()->KeybordPush(DIK_Q) || Input::GetInstance()->KeybordPush(DIK_E) || Input::GetInstance()->KeybordPush(DIK_LCONTROL) || Input::GetInstance()->KeybordPush(DIK_SPACE))
	{
		if (Input::GetInstance()->KeybordPush(DIK_SPACE)) { camera->CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
		else if (Input::GetInstance()->KeybordPush(DIK_LCONTROL)) { camera->CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
		if (Input::GetInstance()->KeybordPush(DIK_E)) { camera->CameraMoveVector({ +1.0f,0.0f,0.0f }); }
		else if (Input::GetInstance()->KeybordPush(DIK_Q)) { camera->CameraMoveVector({ -1.0f,0.0f,0.0f }); }
	}*/

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
	static XMVECTOR lightDir = { 3, -3, 0, 0 };
	/*if (input->PushKey(DIK_W)) { lightDir.m128_f32[1] += 1.0f; }
	else if (input->PushKey(DIK_S)) { lightDir.m128_f32[1] -= 1.0f; }
	if (input->PushKey(DIK_D)) { lightDir.m128_f32[0] += 1.0f; }
	else if (input->PushKey(DIK_A)) { lightDir.m128_f32[0] -= 1.0f; }*/
	light->SetLightDir(lightDir);
	particle3d->Update();
	camera->Update();
	objSkydome->Update();
	objGround->Update();
	objFighter->Update();
	light->Update();
	object1->Update();
	objSphere1->Update();
	objSphere2->Update();
	objSphere3->Update();

}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

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

	objSphere1->Draw();
	//objSphere2->Draw();
	//objSphere3->Draw();
	//playerObj->Draw();
	//objSkydome->Draw();
	//objGround->Draw();
	//objFighter->Draw();
	//object1->Draw(cmdList);
	//-------------------------------------------------------------//
	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

	ToonObject3d::PreDraw(cmdList);
	//-------------------------------------------------------------//
	objSphere2->Draw();
	ToonObject3d::PostDraw();

	PhongObject3d::PreDraw(cmdList);
	//-------------------------------------------------------------//
	objSphere3->Draw();
	PhongObject3d::PostDraw();

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
