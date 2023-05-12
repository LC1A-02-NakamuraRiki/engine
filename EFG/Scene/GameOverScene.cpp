#include "GameOverScene.h"

void GameOverScene::Initialize()
{
	if (!Sprite::LoadTexture(20, L"Resources/GAMEOVER2.png")) {
		assert(0);
		return;
	}
	spriteGAMEOVER = std::unique_ptr<Sprite>(Sprite::Create(20, { 0.0f,0.0f }));
}

void GameOverScene::Draw()
{
	spriteGAMEOVER->Draw(1.0f);//ゲームオーバーのスプライト
}
