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
/// �Q�[���V�[��
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
protected: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	LightGroop *light = nullptr;
private: // �ÓI�����o�ϐ�
	static const int debugTextTexNumber = 0;

public: // �����o�֐�

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon *dxCommon, Sound *audio);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �p�[�e�B�N������
	/// </summary>
	void ParticlesCreate(XMFLOAT3 Pos);

	bool GetStopFlag() { return stopFlag; }
private: // �����o�ϐ�
	DirectXCommon *dxCommon = nullptr;
	Sound *audio = nullptr;
	DebugText debugText;
	
	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
	DebugCamera *camera = nullptr;
	Sprite *spriteTitle = nullptr;
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

	float ambientColor0[3] = { 0.1,0.1,0.1 };
	// �������������l

	float lightDir0[3] = { 0,1,0 };
	float lightDir1[3] = { 0,0,1 };
	float lightDir2[3] = { 0,0,-1 };
	float lightDir3[3] = { 1,0,0 };
	float lightDir4[3] = {-1,0,0 };
	float lightDir5[3] = { 0,-1,0 };
	
	float lightColor0[3] = { 1.75,1.75,1.4 };
	float lightColor1[3] = { 1.2,1.2,0.96 };
	float lightColor2[3] = { 1.2,1.2,0.96 };
	float lightColor3[3] = { 1.2,1.2,0.96 };
	float lightColor4[3] = { 1.2,1.2,0.96 };
	float lightColor5[3] = { 1.5,1.5,1.2 };
};