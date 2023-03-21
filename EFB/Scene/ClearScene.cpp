#include "ClearScene.h"

void ClearScene::Initialize()
{
	if (!Sprite::LoadTexture(19, L"Resources/Clear.png")) {
		assert(0);
		return;
	}
	spriteClear = std::unique_ptr<Sprite>(Sprite::Create(19, { 0.0f,0.0f }));
}

void ClearScene::Draw()
{
	spriteClear->Draw(1.0f);//クリアのスプライト
}
