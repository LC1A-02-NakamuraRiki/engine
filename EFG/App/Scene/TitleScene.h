#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include <array>
#include "Player.h"
#include "MapChip.h"
#include "enemy.h"
#include "DebugCamera.h"
#include "LightGroop.h"
#include "BaseScene.h"
#include <vector>

enum Mode
{
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH
};

//�^�C�g���V�[��
class TitleScene : public BaseScene
{
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//�R���X�g���N�^
	TitleScene();

	//�f�X�X�g���N�^
	~TitleScene();

	//������
	void Initialize(DebugCamera* camera)override;

	//�X�V
	void Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light)override;

	//3D�`��
	void Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, ID3D12GraphicsCommandList* cmdList)override;

	//2D�`��(�|�X�g�G�t�F�N�g����)
	void DrawPost2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)override;

	//2D�`��(�|�X�g�G�t�F�N�g����)
	void Draw2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)override;

	//�I������
	void Finalize()override;

	//�^�C�g���̃{�^��
	int GetTitleButtonFlag() { return buttonNo; }

	//�{�^���A�b�v
	bool ButtonUp();

	//�{�^���_�E��
	bool ButtonDown();
	
	//����{�^��
	void ButtonSelect(Player* player, MapChip* map);
	
	//�G�X�e�[�^�X������
	void InitializeEnemyStatus(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3);

private: // �����o�ϐ�
	std::array <std::unique_ptr<Sprite>, 3> spriteTitle;	//�^�C�g��
	int titleTime;											//�^�C�g���x��
	int buttonNo = 0;										//�^�C�g���̑I��
};

