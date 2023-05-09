#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include <array>
#include "Player.h"
#include"BaseScene.h"

class OptionScene :public BaseScene
{
	enum Mode
	{
		FIRST,
		SECOND,
		THIRD,
		FOURTH,
		FIFTH
	};
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	OptionScene();

	~OptionScene();

	void Initialize()override;

	void Update()override;

	void Draw(ID3D12GraphicsCommandList* cmdList)override;

	void SpriteDraw()override;

	void Finalize()override;

	bool GetTitleScene() { return titleFlag; }
	void SetTitleScene() { titleFlag = false; }
private:
	std::array < std::unique_ptr<Sprite>, 3> spriteOption;//オプション
	int optionButtonNo = 0;//オプションの選択
	bool titleFlag = false;
};

