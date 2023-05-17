#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize(DebugCamera* camera)
{
	if (!Sprite::LoadTexture(20, L"Resources/GAMEOVER2.png")) {
		assert(0);
		return;
	}
	spriteGAMEOVER = std::unique_ptr<Sprite>(Sprite::Create(20, { 0.0f,0.0f }));
}

void GameOverScene::Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light)
{
}

void GameOverScene::Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, ID3D12GraphicsCommandList* cmdList)
{
}

void GameOverScene::DrawPost2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
}

void GameOverScene::Draw2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	spriteGAMEOVER->Draw(1.0f);//ゲームオーバーのスプライト
}

void GameOverScene::Finalize()
{
}