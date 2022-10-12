#pragma once

#include "../base/SafeDelete.h"
#include "../base/DirectXCommon.h"
#include <DirectXMath.h>
#include "../input/Input.h"
#include "../2d/Sprite.h"
#include "../3d/Object3d.h"
#include "../3d/FbxObject3d.h"
#include "../2d/DebugText.h"
#include "../Sound/Sound.h"
#include "../collision/Collision.h"
#include "../3d/ParticleManager.h"
#include "../3d/DebugCamera.h"
#include "../3d/DebugCamera.h"
#include "../Player/Player.h"
#include "../Map/MapChip.h"
#include "../enemy/enemy.h"
#include "../3d/LightGroop.h"

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

	Model *modelSkydome = nullptr;
	Object3d *objSkydome = nullptr;

	Model *modelGround = nullptr;
	Object3d *objGround = nullptr;

	ParticleManager *particle3d = nullptr;
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	MapChip* map = nullptr;
	int scene = 0;
	float collision;

	bool stopFlag;

	float ambientColor0[3] = { 0.3,0.3,0.3 };

	int buttonNo = 0;
	int optionButtonNo = 0;
	// 光線方向初期値

	float lightDir0[3] = { 0,1,0 };
	float lightDir1[3] = { 0,0,1 };
	float lightDir2[3] = { 0,0,-1 };
	float lightDir3[3] = { 1,0,0 };
	float lightDir4[3] = {-1,0,0 };
	float lightDir5[3] = { 0,-1,0 };
	
	float lightColor0[3] = { 10.0,10.0,10.0 };
	float lightColor1[3] = { 10.0,10.0,10.0 };
	float lightColor2[3] = { 10.0,10.0,10.0 };
	float lightColor3[3] = { 10.0,10.0,10.0 };
	float lightColor4[3] = { 10.0,10.0,10.0 };
	float lightColor5[3] = { 10.0,10.0,10.0 };
};