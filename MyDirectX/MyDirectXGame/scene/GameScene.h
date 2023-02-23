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
	LightGroop* light = nullptr;
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
	DebugCamera* camera = nullptr;
	Sprite* spriteTitle = nullptr;//タイトル
	Sprite* spriteTitle2 = nullptr;//タイトル
	Sprite* spriteTitle3 = nullptr;//タイトル
	Sprite* spriteOption = nullptr;//オプション
	Sprite* spriteOption2 = nullptr;//オプション
	Sprite* spriteOption3 = nullptr;//オプション
	Sprite* spriteClear = nullptr;//クリア
	Sprite* spriteGAMEOVER = nullptr;//ゲームオーバー
	Sprite* spriteGAMEOVER2 = nullptr;//ゲームオーバー
	Sprite* spriteRule = nullptr;//ルール
	Sprite* spriteGrain[8] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };//グレイン
	int grainCount = 0;//グレインカウント

	ParticleManager* particle3d = nullptr;//パーティクル
	Player* player = nullptr;//プレイヤー
	Enemy* enemy[3] = { nullptr,nullptr,nullptr };//エネミー
	MapChip* map = nullptr;//マップ
	int scene = 0;//シーン
	bool stopFlag;//停止フラグ
	int buttonNo = 0;//タイトルの選択
	int optionButtonNo = 0;//オプションの選択
	bool tutrialFlag = true;//チュートリアルの表示
	int soundTimer[3] = { 0, 0 ,0 };//足音の歩行レートのタイマー
	//光線方向初期値
	float lightDir0[3] = { 0,1,0 };
	float lightDir5[3] = { 0,-1,0 };
	float lightDir1[3] = { 0,0,1 };
	float lightDir2[3] = { 0,0,-1 };
	float lightDir3[3] = { 1,0,0 };
	float lightDir4[3] = { -1,0,0 };

	//アンビエント初期値
	const float colorAmbient = 1.5f;
	float ambientColor0[3] = { colorAmbient,colorAmbient,colorAmbient };
	
	//ライトの色縦初期値
	const float colorUpDown = 5.0f;
	float lightColor0[3] = { colorUpDown,colorUpDown,colorUpDown };
	float lightColor5[3] = { colorUpDown,colorUpDown,colorUpDown };

	//ライトの色横初期値
	const float colorSide = 4.0f;
	float lightColor1[3] = { colorSide,colorSide,colorSide };
	float lightColor2[3] = { colorSide,colorSide,colorSide };
	float lightColor3[3] = { colorSide,colorSide,colorSide };
	float lightColor4[3] = { colorSide,colorSide,colorSide };

	int titleTime;//タイトル遅延
};