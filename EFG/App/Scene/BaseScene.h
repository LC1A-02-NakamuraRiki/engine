#pragma once
#include <DirectXMath.h>
#include "Player.h"
#include "MapChip.h"
#include "enemy.h"
#include "DebugCamera.h"
#include "LightGroop.h"
#include "Sound.h"
#include "DebugText.h"

class SceneManager;
/// <summary>
/// シーンチェンジベース
/// </summary>
class BaseScene
{
private: //静的メンバ変数
	static const int debugTextTexNumber = 0;
public:
	virtual ~BaseScene() = default;

	// ベース部分の初期化
	void InitializeBase();

	//デバッグテキストの描画
	void DrawDebugText(ID3D12GraphicsCommandList* cmdList);

	//初期化
	virtual void Initialize(DebugCamera* camera) = 0;

	//更新
	virtual void Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light) = 0;

	//3D描画
	virtual void Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, ID3D12GraphicsCommandList* cmdList) = 0;

	//2D描画(ポストエフェクトあり)
	virtual void DrawPost2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3) = 0;

	//2D描画(ポストエフェクト無し)
	virtual void Draw2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3) = 0;

	//終了処理
	virtual void Finalize() = 0;

	//シーンのセット
	virtual void SetSceneManager(SceneManager* sceneManager) { sceneManager_ = sceneManager; }
protected:
	
	SceneManager* sceneManager_ = nullptr;        //シーン
	Sound* audio = nullptr;                       //サウンド
	DebugText debugText;                          //デバッグテキスト
	bool tutrialFlag;                             //チュートリアル
};
