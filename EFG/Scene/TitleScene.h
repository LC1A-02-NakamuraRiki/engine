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

enum Mode
{
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH
};

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

	TitleScene();

	~TitleScene();

	void Initialize()override;

	void Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light)override;

	void Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)override;

	void DrawPost2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)override;

	void Draw2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)override;

	void Finalize();

	//void Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light, bool tutrialFlag);

	bool GetPlayScene() { return playFlag; }
	void SetPlayScene() { playFlag = false; }
	bool GetOptionScene() { return optionFlag; }
	void SetOptionScene() { optionFlag = false;}

	int GetTitleButtonFlag() { return buttonNo; }
private: // �����o�ϐ�
	std::array <std::unique_ptr<Sprite>, 3> spriteTitle;//�^�C�g��
	int titleTime;//�^�C�g���x��
	int buttonNo = 0;//�^�C�g���̑I��
	bool playFlag = false;
	bool optionFlag = false;
};

