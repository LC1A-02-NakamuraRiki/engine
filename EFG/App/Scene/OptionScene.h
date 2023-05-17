#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include <array>
#include "Player.h"
#include "BaseScene.h"

class OptionScene : public BaseScene
{
	enum Mode
	{
		FIRST,
		SECOND,
		THIRD,
		FOURTH,
		FIFTH
	};
private: // �G�C���A�X
// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	OptionScene();

	~OptionScene();

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

	bool GetTitleScene() { return titleFlag; }
	void SetTitleScene() { titleFlag = false; }
private:
	std::array < std::unique_ptr<Sprite>, 3> spriteOption;//�I�v�V����
	int optionButtonNo = 0;//�I�v�V�����̑I��
	bool titleFlag = false;
};

