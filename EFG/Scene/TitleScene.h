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
#include"BaseScene.h"
#include "Sound.h"

enum Mode
{
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH
};

class TitleScene :public BaseScene
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:

	TitleScene();

	~TitleScene();

	void Initialize()override;

	void Update()override;

	void Draw(ID3D12GraphicsCommandList* cmdList)override;

	void SpriteDraw()override;

	void Finalize()override;

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

