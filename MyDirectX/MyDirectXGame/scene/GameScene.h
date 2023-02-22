#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "FbxObject3d.h"
#include "DebugText.h"
#include "Sound.h"
#include "Collision.h"
#include "ParticleManager.h"
#include "DebugCamera.h"
#include "DebugCamera.h"
#include "Player.h"
#include "MapChip.h"
#include "enemy.h"
#include "LightGroop.h"

/// <summary>
/// �Q�[���V�[��
/// </summary>
enum Mode
{
	TITLE,
	PLAY,
	CLEAR,
	GAMEOVER,
	OPTION
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
	LightGroop* light = nullptr;
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
	void Initialize(DirectXCommon* dxCommon, Sound* audio);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	void PostOffDraw();
	/// <summary>
	/// �p�[�e�B�N������
	/// </summary>
	void ParticlesCreate(XMFLOAT3 Pos);

	bool GetStopFlag() { return stopFlag; }
	int GetTitleButtonFlag() { return buttonNo; }
private: // �����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	Sound* audio = nullptr;
	DebugText debugText;

	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
	DebugCamera* camera = nullptr;
	Sprite* spriteTitle = nullptr;
	Sprite* spriteTitle2 = nullptr;
	Sprite* spriteTitle3 = nullptr;
	Sprite* spriteOption = nullptr;
	Sprite* spriteOption2 = nullptr;
	Sprite* spriteOption3 = nullptr;
	Sprite* spriteClear = nullptr;
	Sprite* spriteGAMEOVER = nullptr;
	Sprite* spriteGAMEOVER2 = nullptr;
	Sprite* spriteRule = nullptr;
	Sprite* spriteGrain[8] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
	int grainCount = 0;

	ParticleManager* particle3d = nullptr;
	Player* player = nullptr;
	Enemy* enemy[3] = { nullptr,nullptr,nullptr };


	MapChip* map = nullptr;
	int scene = 0;
	float collision;

	bool stopFlag;

	int buttonNo = 0;
	int optionButtonNo = 0;

	bool tutrialFlag = true;

	int soundTimer[3] = { 0, 0 ,0 };
	// �������������l

	float lightDir0[3] = { 0,1,0 };
	float lightDir5[3] = { 0,-1,0 };
	float lightDir1[3] = { 0,0,1 };
	float lightDir2[3] = { 0,0,-1 };
	float lightDir3[3] = { 1,0,0 };
	float lightDir4[3] = { -1,0,0 };

	const float colorAmbient = 1.5f;
	float ambientColor0[3] = { colorAmbient,colorAmbient,colorAmbient };

	const float colorUpDown = 5.0f;
	float lightColor0[3] = { colorUpDown,colorUpDown,colorUpDown };
	float lightColor5[3] = { colorUpDown,colorUpDown,colorUpDown };

	const float colorSide = 4.0f;
	float lightColor1[3] = { colorSide,colorSide,colorSide };
	float lightColor2[3] = { colorSide,colorSide,colorSide };
	float lightColor3[3] = { colorSide,colorSide,colorSide };
	float lightColor4[3] = { colorSide,colorSide,colorSide };

	FbxModel* modelWalking[3] = { nullptr, nullptr, nullptr };
	FbxObject3d* objectWalking[3] = {nullptr, nullptr, nullptr};

	FbxModel* modelAttack[3] = { nullptr, nullptr, nullptr };
	FbxObject3d* objectAttack[3] = { nullptr, nullptr, nullptr };

	int titleTime;
};