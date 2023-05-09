#include "OptionScene.h"

OptionScene::OptionScene()
{
}

OptionScene::~OptionScene()
{
}

void OptionScene::Initialize()
{
	//// �w�i�X�v���C�g����
	spriteOption[0] = std::unique_ptr<Sprite>(Sprite::Create(23, { 0.0f,0.0f }));
	spriteOption[1] = std::unique_ptr<Sprite>(Sprite::Create(24, { 0.0f,0.0f }));
	spriteOption[2] = std::unique_ptr<Sprite>(Sprite::Create(25, { 0.0f,0.0f }));
}

void OptionScene::Update()
{
	//�I��
	if (Input::GetInstance()->KeybordTrigger(DIK_W) && optionButtonNo != FIRST || Input::GetInstance()->KeybordTrigger(DIK_UP) && optionButtonNo != FIRST)
	{
		optionButtonNo--;
	}
	else if (Input::GetInstance()->KeybordTrigger(DIK_S) && optionButtonNo != THIRD || Input::GetInstance()->KeybordTrigger(DIK_DOWN) && optionButtonNo != THIRD)
	{
		optionButtonNo++;
	}

	//���x�ύX
	if (Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == FIRST)
	{
		player->SetViewSpeedPlus();
	}
	else if (Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == FIRST && player->GetViewSpeed() >= 0.05)
	{
		player->SetViewSpeedMinus();
	}

	//�V�F�C�N�I�t
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == SECOND && player->GetShakeFlag() ||
		Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == SECOND && player->GetShakeFlag() ||
		Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == SECOND && player->GetShakeFlag())
	{
		player->SetShakeFlag(false);
	}
	//�V�F�C�N�I��
	else if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == SECOND && !player->GetShakeFlag() ||
		Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == SECOND && !player->GetShakeFlag() ||
		Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == SECOND && !player->GetShakeFlag())
	{
		player->SetShakeFlag(true);
	}

	//�^�C�g����
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == THIRD)
	{
		titleFlag = true;
	}
}

void OptionScene::Draw(ID3D12GraphicsCommandList* cmdList)
{
	const int MAXBUTTON = 3;
	for (int i = 0; i < MAXBUTTON; i++)
	{
		if (optionButtonNo == i)
		{
			spriteOption[i]->Draw(1.0f);//�I�v�V�����̃X�v���C�g
		}
	}
}

void OptionScene::SpriteDraw()
{
}

void OptionScene::Finalize()
{
}
