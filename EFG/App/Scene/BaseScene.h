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

//�V�[���`�F���W�x�[�X
class BaseScene
{
private://�G�C���A�X
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
private: //�ÓI�����o�ϐ�
	//�f�o�b�O�e�L�X�g�̃��[�h�i���o�[
	static const int debugTextTexNumber = 0;

public:
	//�f�X�X�g���N�^
	virtual ~BaseScene() = default;

	//�x�[�X�����̏�����
	void InitializeBase();

	//�f�o�b�O�e�L�X�g�̕`��
	void DrawDebugText(ID3D12GraphicsCommandList* cmdList);

	//������
	virtual void Initialize(DebugCamera* camera) = 0;

	//�X�V
	virtual void Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light) = 0;

	//3D�`��
	virtual void Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, ID3D12GraphicsCommandList* cmdList) = 0;

	//2D�`��(�|�X�g�G�t�F�N�g����)
	virtual void DrawPost2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3) = 0;

	//2D�`��(�|�X�g�G�t�F�N�g����)
	virtual void Draw2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3) = 0;

	//�I������
	virtual void Finalize() = 0;

	//�O���C���̏�����
	void InitializeGrain();

	//�O���C���̃A�b�v�f�[�g
	void UpdateGrain();

	//�O���C���̃A�b�v�f�[�g
	void DrawGrain();

	//�V�[���̃Z�b�g
	virtual void SetSceneManager(SceneManager* sceneManager) { sceneManager_ = sceneManager; }

protected:
	std::unique_ptr <Sound>audio;								//�T�E���h
	SceneManager* sceneManager_ = nullptr;						//�V�[��
	DebugText debugText;										//�f�o�b�O�e�L�X�g
	bool tutrialFlag;											//�`���[�g���A��
	std::array<std::unique_ptr<Sprite>, 8> spriteGrain;			//�O���C��
	std::array<std::unique_ptr<Sprite>, 8> spriteAlartGrain1;	//�O���C��
	std::array<std::unique_ptr<Sprite>, 8> spriteAlartGrain2;	//�O���C��
	std::array<int, 3>grainCount = { 0,3,6 };					//�O���C���̃J�E���g
	bool grainFlag = false;										//�O���C���t���O
	bool alartGrainFlag = false;								//�A���[�g�O���C���t���O
};
