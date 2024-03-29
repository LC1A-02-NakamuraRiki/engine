#pragma once
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include <array>
#include "Player.h"
#include "BaseScene.h"

//オプションシーン
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
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//コンストラクタ
	OptionScene();

	//デスストラクタ
	~OptionScene();

	//初期化
	void Initialize(DebugCamera* camera)override;

	//更新
	void Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light)override;

	//3D描画
	void Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, ID3D12GraphicsCommandList* cmdList)override;

	//2D描画(ポストエフェクトあり)
	void DrawPost2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)override;

	//2D描画(ポストエフェクト無し)
	void Draw2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)override;

	//終了処理
	void Finalize()override;

	//ボタンアップ
	bool ButtonUp();

	//ボタンダウン
	bool ButtonDown();

	//決定ボタン
	void ButtonSelect(Player* player, MapChip* map);

	void ViewChage(Player* player );

	void ShakeSelect(Player* player);

	void TitleSlect();
	bool GetTitleScene() { return titleFlag; }
	void SetTitleScene() { titleFlag = false; }
private:
	std::array < std::unique_ptr<Sprite>, 3> spriteOption;		//オプション
	int optionButtonNo = 0;										//オプションの選択
	bool titleFlag = false;										//タイトル移行フラグ
};

