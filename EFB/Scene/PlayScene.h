#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include <array>
#include "Player.h"
#include "MapChip.h"
#include "enemy.h"
#include "DebugCamera.h"
#include "LightGroop.h"
#include "Sound.h"

class PlayScene
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void Initialize();

	void Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light, Sound* audio);

	void Draw(ID3D12GraphicsCommandList* cmdList, Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3);

	void DrawSprite(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3);

	bool GetClearScene() { return clearFlag; }
	void SetClearScene() { clearFlag = false; }

	bool GetGameOverScene() { return gameOverFlag; }
	void SetGameOverScene() { gameOverFlag = false; }

	bool GetStopFlag() { return stopFlag; }
	void SetStopFlag() { stopFlag = false; }

	bool GetTutrialFlag() { return tutrialFlag; }
private:
	std::unique_ptr<Sprite> spriteRule;//ルール

	std::array<int, 3> soundTimer = { 0, 0 ,0 };//足音の歩行レートのタイマー
	bool clearFlag = false;
	bool gameOverFlag = false;
	bool stopFlag;//停止フラグ
	bool tutrialFlag = true;//チュートリアルの表示

};

