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

//シーンチェンジベース
class BaseScene
{
private://エイリアス
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
private: //静的メンバ変数
	//デバッグテキストのロードナンバー
	static const int debugTextTexNumber = 0;

public:
	//デスストラクタ
	virtual ~BaseScene() = default;

	//ベース部分の初期化
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

	//グレインの初期化
	void InitializeGrain();

	//グレインのアップデート
	void UpdateGrain();

	//グレインのアップデート
	void DrawGrain();

	//シーンのセット
	virtual void SetSceneManager(SceneManager* sceneManager) { sceneManager_ = sceneManager; }

protected:
	std::unique_ptr <Sound>audio;								//サウンド
	SceneManager* sceneManager_ = nullptr;						//シーン
	DebugText debugText;										//デバッグテキスト
	bool tutrialFlag;											//チュートリアル
	std::array<std::unique_ptr<Sprite>, 8> spriteGrain;			//グレイン
	std::array<std::unique_ptr<Sprite>, 8> spriteAlartGrain1;	//グレイン
	std::array<std::unique_ptr<Sprite>, 8> spriteAlartGrain2;	//グレイン
	std::array<int, 3>grainCount = { 0,3,6 };					//グレインのカウント
	bool grainFlag = false;										//グレインフラグ
	bool alartGrainFlag = false;								//アラートグレインフラグ
};
