#pragma once

#include "../base/SafeDelete.h"
#include "../base/DirectXCommon.h"
#include <DirectXMath.h>
#include "../input/Input.h"
#include "../2d/Sprite.h"
#include "../3d/Object3d.h"
#include "../2d/DebugText.h"
#include "../audio/Audio.h"
#include "../scene/Collision.h"
#include "../3d/ParticleManager.h"
#include "../camera/DebugCamera.h"

class CollisionManager;
class Player;

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

	/// �R���X�g�N���^
	GameScene();

	/// �f�X�g���N�^
	~GameScene();

	/// ������
	void Initialize(DirectXCommon *dxCommon, Input *input, Audio *audio);

	/// ���t���[������
	void Update();

	/// �`��
	void Draw();

	/// �p�[�e�B�N������
	void ParticlesCreate(XMFLOAT3 Pos);

private: // �����o�ϐ�
	DirectXCommon *dxCommon = nullptr;
	Input *input = nullptr;
	Audio *audio = nullptr;
	DebugText debugText;
	
	/// �Q�[���V�[���p
	DebugCamera *camera = nullptr;
	Sprite *spriteBG = nullptr;

	Model *skydomeModel = nullptr;
	Object3d *skydomeObj = nullptr;

	Model *groundModel = nullptr;
	Object3d *groundObj = nullptr;

	Model *carModel = nullptr;
	Object3d *carObj = nullptr;
	ParticleManager *particle3d = nullptr;
	
	Model *modelSphere = nullptr;
	Object3d *objSphere = nullptr;

	Model *modelFighter = nullptr;
	Player *objFighter = nullptr;
	/*Object3d *playerObj = nullptr;
	Model *playerModel = nullptr;

	Sphere sphere;
	Plane plane;
	Triangle triangle;
	Ray ray;*/

	float collision;
	CollisionManager *collisionManager = nullptr;
};