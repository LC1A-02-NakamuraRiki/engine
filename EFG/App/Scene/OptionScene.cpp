#include "OptionScene.h"

OptionScene::OptionScene()
{
}

OptionScene::~OptionScene()
{
}

void OptionScene::Initialize(DebugCamera* camera)
{
	//背景スプライト生成
	spriteOption[0] = std::unique_ptr<Sprite>(Sprite::Create(23, { 0.0f,0.0f }));
	spriteOption[1] = std::unique_ptr<Sprite>(Sprite::Create(24, { 0.0f,0.0f }));
	spriteOption[2] = std::unique_ptr<Sprite>(Sprite::Create(25, { 0.0f,0.0f }));
	
	//グレインのOFF
	grainFlag = false;

	//追われている際のグレインのOFF
	alartGrainFlag = false;
}

void OptionScene::Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light)
{
	//選択
	ButtonSelect(player, map);

	//感度変更
	ViewChage(player);

	//シェイクの有無
	ShakeSelect(player);

	//タイトルへ
	TitleSlect();
	
}

void OptionScene::Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, ID3D12GraphicsCommandList* cmdList)
{
}

void OptionScene::DrawPost2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
}

void OptionScene::Draw2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	spriteOption[optionButtonNo]->Draw(1.0f);//オプションのスプライト
}

void OptionScene::Finalize()
{
}

bool OptionScene::ButtonUp()
{
	if (Input::GetInstance()->KeybordTrigger(DIK_W) && optionButtonNo != FIRST) {
		return true;
	}
	return false;
}

bool OptionScene::ButtonDown()
{
	if (Input::GetInstance()->KeybordTrigger(DIK_S) && optionButtonNo != THIRD) {
		return true;
	}
	return false;
}

void OptionScene::ButtonSelect(Player* player, MapChip* map)
{
	if (ButtonUp()){
		optionButtonNo--;
	}
	else if (ButtonDown()){
		optionButtonNo++;
	}
}

void OptionScene::ViewChage(Player* player )
{
	if (Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == FIRST)	{
		player->SetViewSpeedPlus();
	}
	else if (Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == FIRST && player->GetViewSpeed() >= 0.05){
		player->SetViewSpeedMinus();
	}
}

void OptionScene::ShakeSelect(Player* player)
{
	//シェイクオフ
	if (Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == SECOND && player->GetShakeFlag() ||
		Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == SECOND && player->GetShakeFlag()) {
		player->SetShakeFlag(false);
	}
	//シェイクオン
	else if (Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == SECOND && !player->GetShakeFlag() ||
		Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == SECOND && !player->GetShakeFlag()) {
		player->SetShakeFlag(true);
	}
}

void OptionScene::TitleSlect()
{
	//タイトルへ
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == THIRD){
		titleFlag = true;
	}
}

