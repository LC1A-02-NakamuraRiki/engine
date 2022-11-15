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
	LightGroop *light = nullptr;
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
	void Initialize(DirectXCommon *dxCommon, Sound *audio);

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
	DirectXCommon *dxCommon = nullptr;
	Sound *audio = nullptr;
	DebugText debugText;
	
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	DebugCamera *camera = nullptr;
	Sprite *spriteTitle = nullptr;
	Sprite* spriteTitle2 = nullptr;
	Sprite* spriteTitle3 = nullptr;
	Sprite* spriteOption = nullptr;
	Sprite* spriteOption2 = nullptr;
	Sprite* spriteOption3 = nullptr;
	Sprite* spriteClear = nullptr;
	Sprite* spriteGAMEOVER = nullptr;
	Sprite* spriteRule = nullptr;

	ParticleManager *particle3d = nullptr;
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	MapChip* map = nullptr;
	int scene = 0;
	float collision;

	bool stopFlag;

	float ambientColor0[3] = { 0.35f,0.35f,0.35f };

	int buttonNo = 0;
	int optionButtonNo = 0;
	
	bool tutrialFlag = true;
	// 光線方向初期値

	float lightDir0[3] = { 0,1,0 };
	float lightDir1[3] = { 0,0,1 };
	float lightDir2[3] = { 0,0,-1 };
	float lightDir3[3] = { 1,0,0 };
	float lightDir4[3] = {-1,0,0 };
	float lightDir5[3] = { 0,-1,0 };
	
	float lightColor0[3] = { 8.0,8.0,8.0 };
	float lightColor1[3] = { 6.0,6.0,6.0 };
	float lightColor2[3] = { 6.0,6.0,6.0 };
	float lightColor3[3] = { 6.0,6.0,6.0 };
	float lightColor4[3] = { 6.0,6.0,6.0 };
	float lightColor5[3] = { 8.0,8.0,8.0 };
};