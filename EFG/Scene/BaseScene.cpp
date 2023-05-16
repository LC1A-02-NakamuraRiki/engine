#include "BaseScene.h"

void BaseScene::InitializeBase()
{
	// デバッグテキスト初期化
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	debugText.Initialize(debugTextTexNumber);
}

void BaseScene::DrawDebugText(ID3D12GraphicsCommandList* cmdList)
{
	debugText.DrawAll(cmdList);
}
