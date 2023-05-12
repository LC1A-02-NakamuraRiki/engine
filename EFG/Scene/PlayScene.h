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
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
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

	float GetArartValue() { return alartValue; };

	float GetShVa1( Player* player,MapChip* map, Enemy* enemy2);
	float GetShVa2( Player* player,MapChip* map, Enemy* enemy2);
	float GetShVa3( Player* player,MapChip* map, Enemy* enemy3);
	float GetShVa4( Player* player,MapChip* map, Enemy* enemy3);
private:
	std::unique_ptr<Sprite> spriteRule;//���[��

	std::array<int, 3> soundTimer = { 0, 0 ,0 };//�����̕��s���[�g�̃^�C�}�[
	bool clearFlag = false;
	bool gameOverFlag = false;
	bool stopFlag;//��~�t���O
	bool tutrialFlag = true;//�`���[�g���A���̕\��
	float alartValue = 0.0f;
};

