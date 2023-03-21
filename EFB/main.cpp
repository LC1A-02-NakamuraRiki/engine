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

#pragma region 汎用機能初期化
	// 入力の初期化
	Input::GetInstance()->Initialize(win.get());
	// オーディオの初期化
	audio = std::make_unique<Sound>();
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

	LightGroop::StaticInitialize(dxCommon->GetDevice());
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());

	postEffect = std::make_unique<PostEffect>();
	postEffect->Initialize();
#pragma endregion

	// ゲームシーンの初期化
	sceneManager = std::make_unique<SceneManager>();
	sceneManager->Initialize(dxCommon.get(), audio.get());

	// メインループ
	while (true)
	{
		// メッセージ処理
		if (win->ProcessMessage()) { break; }

		// 入力関連の毎フレーム処理
		Input::GetInstance()->Update();
		// ゲームシーンの毎フレーム処理
		sceneManager->Update();
		if (Input::GetInstance()->KeybordTrigger(DIK_ESCAPE))
		{
			break;
		}
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && sceneManager->GetTitleButtonFlag() == 2)
		{
			break;
		}
		postEffect->PreDrawScene(dxCommon->GetCommandList());
		sceneManager->Draw();
		postEffect->PostDrawScene(dxCommon->GetCommandList());

		// 描画開始
		dxCommon->PreDraw();
		postEffect->Draw(dxCommon->GetCommandList(), sceneManager->GetStopFlag());
		sceneManager->PostOffDraw();
		// ゲームシーンの描画
		// 描画終了
		dxCommon->PostDraw();
		//ESCでの終了

	}
	FbxLoader::GetInstance()->Finalize();
	// ゲームウィンドウの破棄
	win->Finalize();
	return 0;
}