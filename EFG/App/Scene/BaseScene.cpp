#include "BaseScene.h"

void BaseScene::InitializeBase()
{
	// デバッグテキスト初期化
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	debugText.Initialize(debugTextTexNumber);

	// オーディオの初期化
	audio = std::make_unique<Sound>();
	audio->Initialize();

	//グレインの初期化
	InitializeGrain();
}

void BaseScene::DrawDebugText(ID3D12GraphicsCommandList* cmdList)
{
	//全テキスト描画
	debugText.DrawAll(cmdList);
}

void BaseScene::InitializeGrain()
{
	//グレインテクスチャのステータス初期化
	const int MAXGRAINVALUE = 8;
	for (int i = 0; i < MAXGRAINVALUE; i++) {
		spriteGrain[i] = std::unique_ptr<Sprite>(Sprite::Create(50 + i, { 0.0f,0.0f }));
		spriteGrain[i]->SetSize(XMFLOAT2{ 1920.0f * 1.5f,1080.0f * 1.5f });
		spriteAlartGrain1[i] = std::unique_ptr<Sprite>(Sprite::Create(100 + i, { 0.0f,0.0f }));
		spriteAlartGrain1[i]->SetSize(XMFLOAT2{ 1920.0f * 4.0f,1080.0f * 4.0f });
		spriteAlartGrain2[i] = std::unique_ptr<Sprite>(Sprite::Create(100 + i, { 0.0f,0.0f }));
		spriteAlartGrain2[i]->SetSize(XMFLOAT2{ 1920.0f * 5.0f,1080.0f * 5.0f });
	}
}

void BaseScene::UpdateGrain()
{
	//グレイン
	const int MAXGARAIN = 7;
	for (int i = 0; i < 3; i++) {
		grainCount[i]++;
		if (grainCount[i] > MAXGARAIN) {
			grainCount[i] = 0;
		}
	}
}

void BaseScene::DrawGrain()
{
	if (alartGrainFlag) {
		spriteAlartGrain1[grainCount[0]]->Draw(1.0f);//テクスチャスプライト
		spriteAlartGrain2[grainCount[1]]->Draw(1.0f);//テクスチャスプライト
	}
	if (grainFlag)
	{
		spriteGrain[grainCount[2]]->Draw(1.0f);//テクスチャスプライト
	}
}

