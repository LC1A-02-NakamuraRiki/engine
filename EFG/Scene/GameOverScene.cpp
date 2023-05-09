#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize()
{
	if (!Sprite::LoadTexture(20, L"Resources/GAMEOVER2.png")) {
		assert(0);
		return;
	}
	spriteGAMEOVER = std::unique_ptr<Sprite>(Sprite::Create(20, { 0.0f,0.0f }));
}

void GameOverScene::Update()
{
}

void GameOverScene::Draw(ID3D12GraphicsCommandList* cmdList)
{
}

void GameOverScene::SpriteDraw()
{
	spriteGAMEOVER->Draw(1.0f);//ゲームオーバーのスプライト
}

void GameOverScene::Finalize()
{
}
