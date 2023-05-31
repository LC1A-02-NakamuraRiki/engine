#include "GameOverScene.h"
#include "TitleScene.h"
#include"SceneManager.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize(DebugCamera* camera)
{
	//ゲームオーバーのスプライト生成
	spriteGAMEOVER = std::unique_ptr<Sprite>(Sprite::Create(20, { 0.0f,0.0f }));

	//グレインのOFF
	grainFlag = false;

	//追われている際のグレインのOFF
	alartGrainFlag = false;
}

void GameOverScene::Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light)
{
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE)) {
		BaseScene* scene = new TitleScene();//タイトルへ
		sceneManager_->SetNextScene(scene);
	}
}

void GameOverScene::Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, ID3D12GraphicsCommandList* cmdList)
{
}

void GameOverScene::DrawPost2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
}

void GameOverScene::Draw2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	//ゲームオーバーのスプライト描画
	spriteGAMEOVER->Draw(1.0f);
}

void GameOverScene::Finalize()
{
}