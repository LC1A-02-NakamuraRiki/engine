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

/// <summary>
/// ゲームシーン
/// </summary>
enum Mode
{
	TITLE,
	PLAY,
	CLEAR,
	GAMEOVER,
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
	Light *light = nullptr;
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

private: // メンバ変数
	DirectXCommon *dxCommon = nullptr;
	//Input *input = nullptr;
	Sound *audio = nullptr;
	DebugText debugText;
	
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	DebugCamera *camera = nullptr;
	Sprite *spriteBG = nullptr;

	Model *modelSkydome = nullptr;
	Object3d *objSkydome = nullptr;

	Model *modelGround = nullptr;
	Object3d *objGround = nullptr;

	ParticleManager *particle3d = nullptr;
	
	//FbxModel* model1 = nullptr;
	//FbxObject3d* object1 = nullptr;


	/*Object3d *playerObj = nullptr;
	Model *playerModel = nullptr;

	Sphere sphere;
	Plane plane;
	Triangle triangle;
	Ray ray;*/
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	MapChip* map = nullptr;
	int scene = 0;
	float collision;
};