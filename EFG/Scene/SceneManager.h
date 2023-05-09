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
#include "ParticleManager.h"
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
#include"BaseScene.h"

/// <summary>
/// ゲームシーン
/// </summary>
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
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	std::unique_ptr<LightGroop> light;
private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	SceneManager();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SceneManager();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Sound* audio);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void PostOffDraw();

	void SetNextScene(BaseScene* nextScene) { nextScene_ = nextScene; }

	/// <summary>
	/// パーティクル生成
	/// </summary>
	void ParticlesCreate(XMFLOAT3 Pos);

	bool GetStopFlag() { return stopFlag; }

	int GetTitleButtonFlag() { return buttonNo; }

	float GetArartValue() { return alartValue; };
private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Sound* audio = nullptr;
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
	int grainCount = 0;//グレインカウント
	int grainCount2 = 3;//グレインカウント
	int grainCount3 = 6;//グレインカウント

	std::unique_ptr<ParticleManager> particle3d;//パーティクル
	std::unique_ptr<Player> player = nullptr;//プレイヤー
	std::array <std::unique_ptr<Enemy>,3> enemy = { nullptr,nullptr,nullptr };//エネミー
	std::unique_ptr<MapChip> map = nullptr;//マップ
	int scene = 0;//シーン
	bool stopFlag;//停止フラグ
	int buttonNo = 0;//タイトルの選択
	
	
	int titleTime;//タイトル遅延

	float alartValue = 0;

	//今のシーン
	BaseScene* scene_ = nullptr;
	//次のシーン
	BaseScene* nextScene_ = nullptr;
};