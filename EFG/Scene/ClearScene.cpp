#include "ClearScene.h"

ClearScene::ClearScene()
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
	if (!Sprite::LoadTexture(19, L"Resources/Clear.png")) {
		assert(0);
		return;
	}
	spriteClear = std::unique_ptr<Sprite>(Sprite::Create(19, { 0.0f,0.0f }));
}

void ClearScene::Draw(ID3D12GraphicsCommandList* cmdList)
{
	spriteClear->Draw(1.0f);//クリアのスプライト
}

void ClearScene::Update()
{
}

void ClearScene::SpriteDraw()
{
}

void ClearScene::Finalize()
{
}


