#pragma once

#include "../base/SafeDelete.h"
#include "../base/DirectXCommon.h"
#include <DirectXMath.h>
#include "../input/Input.h"
#include "../2d/Sprite.h"
#include "../3d/Object3d.h"
#include "../2d/DebugText.h"
#include "../audio/Audio.h"
#include "../scene/Collision.h"
#include "../3d/ParticleManager.h"
#include "../camera/DebugCamera.h"

class CollisionManager;
class Player;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
private: // エイリアス
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

	/// コンストクラタ
	GameScene();

	/// デストラクタ
	~GameScene();

	/// 初期化
	void Initialize(DirectXCommon *dxCommon, Input *input, Audio *audio);

	/// 毎フレーム処理
	void Update();

	/// 描画
	void Draw();

	/// パーティクル生成
	void ParticlesCreate(XMFLOAT3 Pos);

private: // メンバ変数
	DirectXCommon *dxCommon = nullptr;
	Input *input = nullptr;
	Audio *audio = nullptr;
	DebugText debugText;
	
	/// ゲームシーン用
	DebugCamera *camera = nullptr;
	Sprite *spriteBG = nullptr;

	Model *skydomeModel = nullptr;
	Object3d *skydomeObj = nullptr;

	Model *groundModel = nullptr;
	Object3d *groundObj = nullptr;

	Model *carModel = nullptr;
	Object3d *carObj = nullptr;
	ParticleManager *particle3d = nullptr;
	
	Model *modelSphere = nullptr;
	Object3d *objSphere = nullptr;

	Model *modelFighter = nullptr;
	Player *objFighter = nullptr;
	/*Object3d *playerObj = nullptr;
	Model *playerModel = nullptr;

	Sphere sphere;
	Plane plane;
	Triangle triangle;
	Ray ray;*/

	float collision;
	CollisionManager *collisionManager = nullptr;
};