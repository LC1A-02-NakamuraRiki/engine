﻿#include "WinApp.h"
#include "DirectXCommon.h"
#include "Sound.h"
#include "GameScene.h"
#include "Light.h"
#include"FbxLoader.h"
#include "PostEffect.h"
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 汎用機能
	WinApp *win = nullptr;
	DirectXCommon *dxCommon = nullptr;
	Input *input = nullptr;
	Sound *audio = nullptr;
	GameScene *gameScene = nullptr;
	PostEffect* postEffect = nullptr;

	// ゲームウィンドウの作成
	win = new WinApp();
	win->Initialize();

	//DirectX初期化処理
	dxCommon = new DirectXCommon();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// 入力の初期化
	input = new Input();
	if (!input->Initialize(win->GetHInstance(), win->GetHwnd())) {
		assert(0);
		return 1;
	}
	input->MouseInitialize(win);
	// オーディオの初期化
	audio = new Sound();
	if (!audio->Initialize()) {
		assert(0);
		return 1;
	}
	// スプライト静的初期化
	if (!Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height)) {
		assert(0);
		return 1;
	}

	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice());
	
	
	Light::StaticInitialize(dxCommon->GetDevice());
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());

	//Sprite::LoadTexture(100, L"Resources/white1x1.png");
	postEffect = new PostEffect();
	postEffect->Initialize(input);
#pragma endregion

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, input, audio);

	// メインループ
	while (true)
	{
		// メッセージ処理
		if (win->ProcessMessage()) { break; }

		// 入力関連の毎フレーム処理
		input->Update();
		input->MouseUpdate();
		// ゲームシーンの毎フレーム処理
		gameScene->Update();
		postEffect->PreDrawScene(dxCommon->GetCommandList());
		gameScene->Draw();
		postEffect->PostDrawScene(dxCommon->GetCommandList());
		// 描画開始
		dxCommon->PreDraw();
		postEffect->Draw(dxCommon->GetCommandList());
		// ゲームシーンの描画
		//gameScene->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}
	// 各種解放
	delete postEffect;
	safe_delete(gameScene);
	safe_delete(audio);
	safe_delete(input);
	FbxLoader::GetInstance()->Finalize();
	safe_delete(dxCommon);

	// ゲームウィンドウの破棄
	win->Finalize();
	safe_delete(win);

	return 0;
}