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
	//�Q�[���I�[�o�[�̃X�v���C�g����
	spriteGAMEOVER = std::unique_ptr<Sprite>(Sprite::Create(20, { 0.0f,0.0f }));

	//�O���C����OFF
	grainFlag = false;

	//�ǂ��Ă���ۂ̃O���C����OFF
	alartGrainFlag = false;
}

void GameOverScene::Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light)
{
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE)) {
		BaseScene* scene = new TitleScene();//�^�C�g����
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
	//�Q�[���I�[�o�[�̃X�v���C�g�`��
	spriteGAMEOVER->Draw(1.0f);
}

void GameOverScene::Finalize()
{
}