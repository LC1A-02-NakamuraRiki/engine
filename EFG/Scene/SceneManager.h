#pragma once

#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "FbxObject3d.h"
#include "DebugText.h"
#include "Sound.h"
#include "Collision.h"
#include "DebugCamera.h"
#include "Player.h"
#include "MapChip.h"
#include "enemy.h"
#include "LightGroop.h"
#include <array>
#include "TitleScene.h"
#include "OptionScene.h"
#include "PlayScene.h"
#include "ClearScene.h"
#include "GameOverScene.h"

/// ゲームシーン
enum SceneMode
{
	TITLE,
	PLAY,
	CLEAR,
	GAMEOVER,
	OPTION
};

class SceneManager
{
private://エイリアス
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: //静的メンバ変数
	static const int debugTextTexNumber = 0;

public: //メンバ関数

	//コンストクラタ
	SceneManager();

	//デストラクタ
	~SceneManager();

	//初期化
	void Initialize(DirectXCommon* dxCommon, Sound* audio);

	//毎フレーム処理
	void Update();

	//描画
	void Draw();

	//ポストエフェクトOFF描画
	void PostOffDraw();

	//テクスチャ初期化
	void InitializeTexture();

	//グレインの初期化
	void InitializeGrain();

	//FBXの初期化
	void InitializeFBX();

	//アプリ部の初期化
	void InitializeAppli();

	//グレインのアップデート
	void UpdateGrain();

	bool GetStopFlag() { return stopFlag; }

	int GetTitleButtonFlag() { return buttonNo; }

	float GetArartValue() { return alartValue; };
private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Sound* audio = nullptr;
	std::unique_ptr<LightGroop> light;

	DebugText debugText;
	
	std::unique_ptr < TitleScene > titleScene;
	std::unique_ptr < OptionScene > optionScene;
	std::unique_ptr < PlayScene > playScene;
	std::unique_ptr < ClearScene > clearScene;
	std::unique_ptr < GameOverScene > gameOverScene;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	std::unique_ptr <DebugCamera> camera;
	std::array <std::unique_ptr<Sprite>,3> spriteTitle;//タイトル

	std::array<std::unique_ptr<Sprite>,8> spriteGrain;//グレイン
	std::array<std::unique_ptr<Sprite>, 8> spriteAlartGrain1;//グレイン
	std::array<std::unique_ptr<Sprite>, 8> spriteAlartGrain2;//グレイン
	std::array<int, 3>grainCount = {0,3,6};

	std::unique_ptr<Player> player = nullptr;//プレイヤー
	std::array <std::unique_ptr<Enemy>,3> enemy = { nullptr,nullptr,nullptr };//エネミー
	std::unique_ptr<MapChip> map = nullptr;//マップ
	int scene = 0;//シーン
	bool stopFlag;//停止フラグ
	int buttonNo = 0;//タイトルの選択
	
	int titleTime;//タイトル遅延

	float alartValue = 0;

	//シーン
	BaseScene* scene = nullptr;
	//次のシーン
	BaseScene* nextScene = nullptr;
};