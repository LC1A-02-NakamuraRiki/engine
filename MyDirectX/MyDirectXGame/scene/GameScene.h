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
#include <array>

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
	std::unique_ptr<LightGroop> light;
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
	std::unique_ptr <DebugCamera> camera;
	std::array <std::unique_ptr<Sprite>,3> spriteTitle;//�^�C�g��
	std::array < std::unique_ptr<Sprite>,3> spriteOption ;//�I�v�V����
	std::unique_ptr<Sprite> spriteClear;//�N���A
	std::unique_ptr<Sprite> spriteGAMEOVER;//�Q�[���I�[�o�[
	std::unique_ptr<Sprite> spriteGAMEOVER2;//�Q�[���I�[�o�[
	std::unique_ptr<Sprite> spriteRule;//���[��
	std::array<std::unique_ptr<Sprite>,8> spriteGrain;//�O���C��
	int grainCount = 0;//�O���C���J�E���g
	
	std::unique_ptr<ParticleManager> particle3d;//�p�[�e�B�N��
	std::unique_ptr<Player> player = nullptr;//�v���C���[
	std::array <std::unique_ptr<Enemy>,3> enemy = { nullptr,nullptr,nullptr };//�G�l�~�[
	std::unique_ptr<MapChip> map = nullptr;//�}�b�v
	int scene = 0;//�V�[��
	bool stopFlag;//��~�t���O
	int buttonNo = 0;//�^�C�g���̑I��
	int optionButtonNo = 0;//�I�v�V�����̑I��
	bool tutrialFlag = true;//�`���[�g���A���̕\��
	std::array<int, 3> soundTimer = { 0, 0 ,0 };//�����̕��s���[�g�̃^�C�}�[
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

	int titleTime;//�^�C�g���x��
};