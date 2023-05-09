#pragma once
#include <DirectXMath.h>
#include "Player.h"
#include "MapChip.h"
#include "enemy.h"
#include "DebugCamera.h"
#include "LightGroop.h"
#include "Sound.h"

class SceneManager;
/// <summary>
/// �V�[���`�F���W�x�[�X
/// </summary>
class BaseScene
{
public:
	virtual ~BaseScene() = default;

	/// ������
	virtual void Initialize() = 0;

	/// �X�V
	virtual void Update() = 0;

	/// �`��
	virtual void Draw(ID3D12GraphicsCommandList* cmdList) = 0;

	virtual void SpriteDraw() = 0;

	virtual void Finalize() = 0;

	virtual void SetSceneManager(SceneManager* sceneManager) { sceneManager_ = sceneManager; }
protected:
	SceneManager* sceneManager_ = nullptr;
	Sound* audio = nullptr;
	std::unique_ptr < Player> player;
	std::unique_ptr<MapChip> map = nullptr;//�}�b�v
	std::array <std::unique_ptr<Enemy>, 3> enemy = { nullptr,nullptr,nullptr };//�G�l�~�[
	std::unique_ptr < DebugCamera> camera;
	std::unique_ptr < LightGroop> light;
	bool tutrialFlag;

	//�������������l
	std::array<float, 3> lightDir0 = { 0,1,0 };
	std::array<float, 3> lightDir5 = { 0,-1,0 };
	std::array<float, 3> lightDir1 = { 0,0,1 };
	std::array<float, 3> lightDir2 = { 0,0,-1 };
	std::array<float, 3> lightDir3 = { 1,0,0 };
	std::array<float, 3> lightDir4 = { -1,0,0 };

	//�A���r�G���g�����l
	const float COLORAMBIENT = 1.5f;
	std::array<float, 3> ambientColor0 = { COLORAMBIENT,COLORAMBIENT,COLORAMBIENT };

	//���C�g�̐F�c�����l
	const float COLORUPDOWN = 5.0f;
	std::array<float, 3> lightColor0 = { COLORUPDOWN,COLORUPDOWN,COLORUPDOWN };
	std::array<float, 3> lightColor5 = { COLORUPDOWN,COLORUPDOWN,COLORUPDOWN };

	//���C�g�̐F�������l
	const float COLORSIDE = 4.0f;
	std::array<float, 3> lightColor1 = { COLORSIDE,COLORSIDE,COLORSIDE };
	std::array<float, 3> lightColor2 = { COLORSIDE,COLORSIDE,COLORSIDE };
	std::array<float, 3> lightColor3 = { COLORSIDE,COLORSIDE,COLORSIDE };
	std::array<float, 3> lightColor4 = { COLORSIDE,COLORSIDE,COLORSIDE };
};
