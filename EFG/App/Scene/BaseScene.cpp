#include "BaseScene.h"

void BaseScene::InitializeBase()
{
	// �f�o�b�O�e�L�X�g������
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	debugText.Initialize(debugTextTexNumber);

	// �I�[�f�B�I�̏�����
	audio = std::make_unique<Sound>();
	audio->Initialize();

	//�O���C���̏�����
	InitializeGrain();
}

void BaseScene::DrawDebugText(ID3D12GraphicsCommandList* cmdList)
{
	//�S�e�L�X�g�`��
	debugText.DrawAll(cmdList);
}

void BaseScene::InitializeGrain()
{
	//�O���C���e�N�X�`���̃X�e�[�^�X������
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
	//�O���C��
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
		spriteAlartGrain1[grainCount[0]]->Draw(1.0f);//�e�N�X�`���X�v���C�g
		spriteAlartGrain2[grainCount[1]]->Draw(1.0f);//�e�N�X�`���X�v���C�g
	}
	if (grainFlag)
	{
		spriteGrain[grainCount[2]]->Draw(1.0f);//�e�N�X�`���X�v���C�g
	}
}

