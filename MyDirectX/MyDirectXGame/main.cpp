#include "../base/WinApp.h"
#include "../base/DirectXCommon.h"
#include "../Sound/Sound.h"
#include "../Scene/GameScene.h"
#include "../3d/LightGroop.h"
#include "../3d/FbxLoader.h"
#include "../2d/PostEffect.h"
#include"../input/Input.h"
#include"../input/GamePad.h"
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// 汎用機能
	WinApp *win = nullptr;
	DirectXCommon *dxCommon = nullptr;
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
	Input::GetInstance()->Initialize(win);
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
		
	LightGroop::StaticInitialize(dxCommon->GetDevice());
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());

	postEffect = new PostEffect();
	postEffect->Initialize();
#pragma endregion

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, audio);

	// メインループ
	while (true)
	{
		// メッセージ処理
		if (win->ProcessMessage()) { break; }
		//ESCでの終了
		if (Input::GetInstance()->KeybordTrigger(DIK_ESCAPE)) { break; };
		// 入力関連の毎フレーム処理
		Input::GetInstance()->Update();
		// ゲームシーンの毎フレーム処理
		gameScene->Update();
		postEffect->PreDrawScene(dxCommon->GetCommandList());
		gameScene->Draw();
		postEffect->PostDrawScene(dxCommon->GetCommandList());
		// 描画開始
		dxCommon->PreDraw();
		postEffect->Draw(dxCommon->GetCommandList(),gameScene->GetStopFlag());
		// ゲームシーンの描画
		// 描画終了
		dxCommon->PostDraw();
	}
	// 各種解放
	delete postEffect;
	safe_delete(gameScene);
	safe_delete(audio);
	FbxLoader::GetInstance()->Finalize();
	safe_delete(dxCommon);

	// ゲームウィンドウの破棄
	win->Finalize();
	safe_delete(win);

	return 0;
}