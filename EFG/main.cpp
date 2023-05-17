#include "../base/WinApp.h"
#include "../base/DirectXCommon.h"
#include "../Sound/Sound.h"
#include "../Scene/SceneManager.h"
#include "../3d/LightGroop.h"
#include "../3d/FbxLoader.h"
#include "../2d/PostEffect.h"
#include"../input/Input.h"
#include"../input/GamePad.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#pragma region ウィンドウとDirectXの初期化

	// 汎用機能
	std::unique_ptr <WinApp> win;
	std::unique_ptr <DirectXCommon> dxCommon;
	std::unique_ptr <Sound>audio;
	std::unique_ptr<SceneManager> sceneManager;
	std::unique_ptr<PostEffect> postEffect;

	// ゲームウィンドウの作成
	win = std::make_unique<WinApp>();
	win->Initialize();

	//DirectX初期化処理
	dxCommon = std::make_unique<DirectXCommon>();
	dxCommon->Initialize(win.get());
#pragma endregion

#pragma region 汎用機能初期化
	// 入力の初期化
	Input::GetInstance()->Initialize(win.get());

	// オーディオの初期化
	audio = std::make_unique<Sound>();
	audio->Initialize();

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dxCommon->GetDevice());

	//FBX3Dオブジェクトの初期化
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());

	//ライトの初期化
	LightGroop::StaticInitialize(dxCommon->GetDevice());
	
	//ポストエフェクトの初期化
	postEffect = std::make_unique<PostEffect>();
	postEffect->Initialize();
#pragma endregion

#pragma region シーンマネージャーの初期化
	// ゲームシーンの初期化
	sceneManager = std::make_unique<SceneManager>();
	sceneManager->Initialize(dxCommon.get(), audio.get());
#pragma endregion

#pragma region ゲームループ
	// メインループ
	while (true)
	{
		// メッセージ処理
		if (win->ProcessMessage()) { break; }

		// 入力関連の毎フレーム処理
		Input::GetInstance()->Update();

		// ゲームシーンの毎フレーム処理
		sceneManager->Update();
		
		//////// 描画開始 ////////
		//通常の描画
		postEffect->PreDrawScene(dxCommon->GetCommandList());
		sceneManager->Draw();
		postEffect->PostDrawScene(dxCommon->GetCommandList());

		//ポストエフェクトでの描画
		dxCommon->PreDraw();
		postEffect->Draw(dxCommon->GetCommandList(), sceneManager->GetStopFlag(),sceneManager->GetArartValue());
		sceneManager->PostOffDraw();

		//////// 描画終了 ////////
		dxCommon->PostDraw();

		//ゲームの終了処理
		if (Input::GetInstance()->KeybordTrigger(DIK_ESCAPE)) { break; }
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && sceneManager->GetTitleButtonFlag() == 2) { break; }
	}
#pragma endregion
#pragma region ゲーム終了後の処理
	//FBXの破棄
	FbxLoader::GetInstance()->Finalize();
	// ゲームウィンドウの破棄
	win->Finalize();
#pragma endregion
	return 0;

}