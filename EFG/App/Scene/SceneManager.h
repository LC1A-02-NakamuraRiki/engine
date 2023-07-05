#pragma once

#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "FbxObject3d.h"
#include "Sound.h"
#include "Collision.h"
#include "DebugCamera.h"
#include "Player.h"
#include "MapChip.h"
#include "enemy.h"
#include "LightGroop.h"
#include <array>
#include "TitleScene.h"
#include "OptionScene.h"
#include "PlayScene.h"
#include "ClearScene.h"
#include "GameOverScene.h"
#include "BaseScene.h"

//�V�[���Ǘ�
class SceneManager
{
private://�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: //�����o�֐�

	//�R���X�g�N���^
	SceneManager();

	//�f�X�g���N�^
	~SceneManager();

	//������
	void Initialize(DirectXCommon* dxCommon);

	//���t���[������
	void Update();

	//�`��
	void Draw();

	//�|�X�g�G�t�F�N�gOFF�`��
	void PostOffDraw();

	//FBX�̏�����
	void InitializeFBX();

	//�A�v�����̏�����
	void InitializeAppli();

	//���̃V�[���\��
	void SetNextScene(BaseScene* changeScene) { nextScene = changeScene; }

	bool GetStopFlag() { return stopFlag; }

	int GetTitleButtonFlag() { return buttonNo; }

	float GetArartValue() { return alartValue; };
private: // �����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	Sound* audio = nullptr;
	std::unique_ptr<LightGroop> light;

	// �Q�[���V�[���p
	std::unique_ptr <DebugCamera> camera;											//�J����
	std::array <std::unique_ptr<Sprite>, 3> spriteTitle;							//�^�C�g��
	std::unique_ptr<Player> player = nullptr;										//�v���C���[
	std::array <std::unique_ptr<Enemy>, 3> enemy = { nullptr,nullptr,nullptr };		//�G�l�~�[
	std::unique_ptr<MapChip> map = nullptr;											//�}�b�v
	int scene = 0;																	//�V�[��
	bool stopFlag;																	//��~�t���O
	int buttonNo = 0;																//�^�C�g���̑I��
	int titleTime;																	//�^�C�g���x��
	float alartValue = 0;															//�_�ł̒l

	//�V�[��
	BaseScene* nowScene = nullptr;
	//���̃V�[��
	BaseScene* nextScene = nullptr;
};