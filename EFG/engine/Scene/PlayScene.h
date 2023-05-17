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
#include "BaseScene.h"

class PlayScene : public BaseScene
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

	PlayScene();

	~PlayScene();

	//������
	void Initialize(DebugCamera* camera)override;

	//�X�V
	void Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, LightGroop* light)override;

	//3D�`��
	void Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, ID3D12GraphicsCommandList* cmdList)override;

	//2D�`��(�|�X�g�G�t�F�N�g����)
	void DrawPost2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)override;

	//2D�`��(�|�X�g�G�t�F�N�g����)
	void Draw2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)override;

	//�I������
	void Finalize()override;

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
	bool stopFlag;//��~�t���O
	bool tutrialFlag = true;//�`���[�g���A���̕\��
	float alartValue = 0.0f;
};

