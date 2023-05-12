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

enum Mode
{
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH
};

class TitleScene
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	TitleScene();

	~TitleScene();

	void Initialize();

	void Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light, bool tutrialFlag);

	void Draw();

	bool GetPlayScene() { return playFlag; }
	void SetPlayScene() { playFlag = false; }
	bool GetOptionScene() { return optionFlag; }
	void SetOptionScene() { optionFlag = false;}

	int GetTitleButtonFlag() { return buttonNo; }
private: // メンバ変数
	std::array <std::unique_ptr<Sprite>, 3> spriteTitle;//タイトル
	int titleTime;//タイトル遅延
	int buttonNo = 0;//タイトルの選択
	bool playFlag = false;
	bool optionFlag = false;
};

