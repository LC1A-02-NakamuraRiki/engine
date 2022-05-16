#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "FbxObject3d.h"
#include "DebugText.h"
#include "Audio.h"
#include "Collision.h"
#include "ParticleManager.h"
#include "DebugCamera.h"

/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	Light *light = nullptr;
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
	void Initialize(DirectXCommon *dxCommon, Input *input, Audio *audio);

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

private: // �����o�ϐ�
	DirectXCommon *dxCommon = nullptr;
	Input *input = nullptr;
	Audio *audio = nullptr;
	DebugText debugText;
	
	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>
	DebugCamera *camera = nullptr;
	Sprite *spriteBG = nullptr;

	Model *modelSkydome = nullptr;
	Object3d *objSkydome = nullptr;

	Model *modelGround = nullptr;
	Object3d *objGround = nullptr;

	Model *modelFighter = nullptr;
	Object3d *objFighter = nullptr;
	ParticleManager *particle3d = nullptr;

	Model* model1 = nullptr;
	FbxObject3d* object1 = nullptr;
	/*Object3d *playerObj = nullptr;
	Model *playerModel = nullptr;

	Sphere sphere;
	Plane plane;
	Triangle triangle;
	Ray ray;*/

	float collision;
};