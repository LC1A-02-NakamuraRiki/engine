#include "BaseScene.h"

void BaseScene::InitializeBase()
{
	// �f�o�b�O�e�L�X�g������
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	debugText.Initialize(debugTextTexNumber);
}

void BaseScene::DrawDebugText(ID3D12GraphicsCommandList* cmdList)
{
	//�S�e�L�X�g�`��
	debugText.DrawAll(cmdList);
}
