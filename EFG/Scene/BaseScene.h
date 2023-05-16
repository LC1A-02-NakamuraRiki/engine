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
/// �V�[���`�F���W�x�[�X
/// </summary>
class BaseScene
{
private: //�ÓI�����o�ϐ�
	static const int debugTextTexNumber = 0;
public:
	virtual ~BaseScene() = default;

	//�x�[�X�����̏�����
	void InitializeBase();

	//�f�o�b�O�e�L�X�g�̕`��
	void DrawDebugText(ID3D12GraphicsCommandList* cmdList);

	/// ������
	virtual void Initialize() = 0;

	/// �X�V
	virtual void Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light) = 0;

	/// �`��
	virtual void Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, ID3D12GraphicsCommandList* cmdList) = 0;

	virtual void DrawPost2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3) = 0;

	virtual void Draw2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3) = 0;

	virtual void Finalize() = 0;

	virtual void SetSceneManager(SceneManager* sceneManager) { sceneManager_ = sceneManager; }
protected:
	SceneManager* sceneManager_ = nullptr;
	Sound* audio = nullptr;
	DebugText debugText;

	bool tutrialFlag;

};
