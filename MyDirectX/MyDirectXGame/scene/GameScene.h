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


/// <summary>
/// �Q�[���V�[��
/// </summary>
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

private: // �����o�ϐ�
	DirectXCommon *dxCommon = nullptr;
	//Input *input = nullptr;
	Sound *audio = nullptr;
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
	
	FbxModel* model1 = nullptr;
	FbxObject3d* object1 = nullptr;

	Player* player = nullptr;

	Model* modelMapWall = nullptr;
	Object3d* objMapWall[20][20];
	int mapWall[18][18] = { { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
						    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
						    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
						    { 1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1 },
						    { 1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1 },
						    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
						    { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
						    { 1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1 },
						    { 1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1 },
							{ 1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1 },
							{ 1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1 },
							{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
							{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
							{ 1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1 },
							{ 1,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1 },
							{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
							{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
							{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
								};
	/*Object3d *playerObj = nullptr;
	Model *playerModel = nullptr;

	Sphere sphere;
	Plane plane;
	Triangle triangle;
	Ray ray;*/

	float collision;
};