#pragma once

#include "SafeDelete.h"
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
#include "DebugCamera.h"
#include "Player.h"
#include "MapChip.h"
#include "enemy.h"
#include "LightGroop.h"
#include <array>

/// <summary>
/// ゲームシーン
/// </summary>
enum Mode
{
	TITLE,
	PLAY,
	CLEAR,
	GAMEOVER,
	OPTION
};

class GameScene
{
protected: // エイリアス
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
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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
	/// <summary>
	/// パーティクル生成
	/// </summary>
	void ParticlesCreate(XMFLOAT3 Pos);

	bool GetStopFlag() { return stopFlag; }
	int GetTitleButtonFlag() { return buttonNo; }
private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Sound* audio = nullptr;
	DebugText debugText;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	std::unique_ptr <DebugCamera> camera;
	std::array <std::unique_ptr<Sprite>,3> spriteTitle;//タイトル
	std::array < std::unique_ptr<Sprite>,3> spriteOption ;//オプション
	std::unique_ptr<Sprite> spriteClear;//クリア
	std::unique_ptr<Sprite> spriteGAMEOVER;//ゲームオーバー
	std::unique_ptr<Sprite> spriteGAMEOVER2;//ゲームオーバー
	std::unique_ptr<Sprite> spriteRule;//ルール
	std::array<std::unique_ptr<Sprite>,8> spriteGrain;//グレイン
	int grainCount = 0;//グレインカウント
	
	std::unique_ptr<ParticleManager> particle3d;//パーティクル
	std::unique_ptr<Player> player = nullptr;//プレイヤー
	std::array <std::unique_ptr<Enemy>,3> enemy = { nullptr,nullptr,nullptr };//エネミー
	std::unique_ptr<MapChip> map = nullptr;//マップ
	int scene = 0;//シーン
	bool stopFlag;//停止フラグ
	int buttonNo = 0;//タイトルの選択
	int optionButtonNo = 0;//オプションの選択
	bool tutrialFlag = true;//チュートリアルの表示
	std::array<int, 3> soundTimer = { 0, 0 ,0 };//足音の歩行レートのタイマー
	//光線方向初期値
	std::array<float, 3> lightDir0 = { 0,1,0 };
	std::array<float, 3> lightDir5 = { 0,-1,0 };
	std::array<float, 3> lightDir1 = { 0,0,1 };
	std::array<float, 3> lightDir2 = { 0,0,-1 };
	std::array<float, 3> lightDir3 = { 1,0,0 };
	std::array<float, 3> lightDir4 = { -1,0,0 };

	//アンビエント初期値
	const float COLORAMBIENT = 1.5f;
	std::array<float, 3> ambientColor0 = { COLORAMBIENT,COLORAMBIENT,COLORAMBIENT };
	
	//ライトの色縦初期値
	const float COLORUPDOWN = 5.0f;
	std::array<float, 3> lightColor0 = { COLORUPDOWN,COLORUPDOWN,COLORUPDOWN };
	std::array<float, 3> lightColor5 = { COLORUPDOWN,COLORUPDOWN,COLORUPDOWN };

	//ライトの色横初期値
	const float COLORSIDE = 4.0f;
	std::array<float, 3> lightColor1 = { COLORSIDE,COLORSIDE,COLORSIDE };
	std::array<float, 3> lightColor2 = { COLORSIDE,COLORSIDE,COLORSIDE };
	std::array<float, 3> lightColor3 = { COLORSIDE,COLORSIDE,COLORSIDE };
	std::array<float, 3> lightColor4 = { COLORSIDE,COLORSIDE,COLORSIDE };

	int titleTime;//タイトル遅延
};