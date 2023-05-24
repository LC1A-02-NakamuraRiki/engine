#include "ClearScene.h"
#include "TitleScene.h"
#include"SceneManager.h"

ClearScene::ClearScene()
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize(DebugCamera* camera)
{
	//�N���A�X�v���C�g����
	spriteClear = std::unique_ptr<Sprite>(Sprite::Create(19, { 0.0f,0.0f }));
}

void ClearScene::Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light)
{
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE)) {
		BaseScene* scene = new TitleScene();//�^�C�g����
		sceneManager_->SetNextScene(scene);
	}
}

void ClearScene::Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, ID3D12GraphicsCommandList* cmdList)
{
}

void ClearScene::DrawPost2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
}

void ClearScene::Draw2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	//�N���A�̃X�v���C�g�`��
	spriteClear->Draw(1.0f);
}

void ClearScene::Finalize()
{
}
