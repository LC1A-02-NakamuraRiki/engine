#include "OptionScene.h"

OptionScene::OptionScene()
{
}

OptionScene::~OptionScene()
{
}

void OptionScene::Initialize()
{
	//// 背景スプライト生成
	spriteOption[0] = std::unique_ptr<Sprite>(Sprite::Create(23, { 0.0f,0.0f }));
	spriteOption[1] = std::unique_ptr<Sprite>(Sprite::Create(24, { 0.0f,0.0f }));
	spriteOption[2] = std::unique_ptr<Sprite>(Sprite::Create(25, { 0.0f,0.0f }));
}

void OptionScene::Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light)
{
	//選択
	if (Input::GetInstance()->KeybordTrigger(DIK_W) && optionButtonNo != FIRST || Input::GetInstance()->KeybordTrigger(DIK_UP) && optionButtonNo != FIRST)
	{
		optionButtonNo--;
	}
	else if (Input::GetInstance()->KeybordTrigger(DIK_S) && optionButtonNo != THIRD || Input::GetInstance()->KeybordTrigger(DIK_DOWN) && optionButtonNo != THIRD)
	{
		optionButtonNo++;
	}

	//感度変更
	if (Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == FIRST)
	{
		player->SetViewSpeedPlus();
	}
	else if (Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == FIRST && player->GetViewSpeed() >= 0.05)
	{
		player->SetViewSpeedMinus();
	}

	//シェイクオフ
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == SECOND && player->GetShakeFlag() ||
		Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == SECOND && player->GetShakeFlag() ||
		Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == SECOND && player->GetShakeFlag())
	{
		player->SetShakeFlag(false);
	}
	//シェイクオン
	else if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == SECOND && !player->GetShakeFlag() ||
		Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == SECOND && !player->GetShakeFlag() ||
		Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == SECOND && !player->GetShakeFlag())
	{
		player->SetShakeFlag(true);
	}

	//タイトルへ
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == THIRD)
	{
		titleFlag = true;
	}
	
}

void OptionScene::Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, ID3D12GraphicsCommandList* cmdList)
{
}

void OptionScene::DrawPost2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
}

void OptionScene::Draw2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	const int MAXBUTTON = 3;
	for (int i = 0; i < MAXBUTTON; i++)
	{
		if (optionButtonNo == i)
		{
			spriteOption[i]->Draw(1.0f);//オプションのスプライト
		}
	}
	debugText.Print(1.0f, 1.0f, 1.0f, "aaa");
}

void OptionScene::Finalize()
{
}

