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

void OptionScene::Update(Player* player)
{
	//選択
	if (Input::GetInstance()->KeybordTrigger(DIK_W) && optionButtonNo != 0 || Input::GetInstance()->KeybordTrigger(DIK_UP) && optionButtonNo != 0)
	{
		optionButtonNo--;
	}
	else if (Input::GetInstance()->KeybordTrigger(DIK_S) && optionButtonNo != 2 || Input::GetInstance()->KeybordTrigger(DIK_DOWN) && optionButtonNo != 2)
	{
		optionButtonNo++;
	}

	//感度変更
	if (Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == 0)
	{
		player->SetViewSpeedPlus();
	}
	else if (Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == 0 && player->GetViewSpeed() >= 0.05)
	{
		player->SetViewSpeedMinus();
	}

	//シェイクオフ
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == 1 && player->GetShakeFlag() ||
		Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == 1 && player->GetShakeFlag() ||
		Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == 1 && player->GetShakeFlag())
	{
		player->SetShakeFlag(false);
	}
	//シェイクオン
	else if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == 1 && !player->GetShakeFlag() ||
		Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == 1 && !player->GetShakeFlag() ||
		Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == 1 && !player->GetShakeFlag())
	{
		player->SetShakeFlag(true);
	}

	//タイトルへ
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == 2)
	{
		titleFlag = true;
	}
}

void OptionScene::Draw()
{
	for (int i = 0; i < 3; i++)
	{
		if (optionButtonNo == i)
		{
			spriteOption[i]->Draw(1.0f);//オプションのスプライト
		}
	}
}
