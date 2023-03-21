#include "PlayScene.h"
#include "Input.h"
#include "SoundVector.h"

void PlayScene::Initialize()
{
	if (!Sprite::LoadTexture(30, L"Resources/tutrial.png")) {
		assert(0);
		return;
	}
	spriteRule = std::unique_ptr<Sprite>(Sprite::Create(30, { 0.0f,0.0f }));
}

void PlayScene::Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light, Sound* audio)
{

	//�v���C���[�̃J�����ƈړ�
	camera->SetEye(player->GetPos());
	camera->SetTarget(player->GetTarget());

	//�`���[�g���A��
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && tutrialFlag == true)
	{
		tutrialFlag = false;
	}

	//�v���C���[�̃A�b�v�f�[�g
	player->Update(map, tutrialFlag, enemy1->CatchCollision(player), enemy2->CatchCollision(player), enemy3->CatchCollision(player));

	//�J�����A�b�v�f�[�g
	camera->Update();

	//���C�g�A�b�v�f�[�g
	light->Update();

	//�}�b�v�A�b�v�f�[�g
	map->Update(player->GetPos(), player->GetMapPos(), enemy1->GetPos(), enemy2->GetPos(), enemy3->GetPos());

	//�G�l�~�[�A�b�v�f�[�g
	enemy1->Update(player, map, player->GetMapPos(), XMFLOAT2(0, 0), enemy2->CatchCollision(player), enemy3->CatchCollision(player));
	enemy2->Update(player, map, player->GetMapPos(), player->GetShortCut(map, enemy2->GetPos()), enemy1->CatchCollision(player), enemy3->CatchCollision(player));
	enemy3->Update(player, map, player->GetMapPos(), player->GetShortCut(map, enemy3->GetPos()), enemy1->CatchCollision(player), enemy2->CatchCollision(player));

	//���C�g�_�Ŋ֘A
	
	if (map->GetGateOpenFlag() && !enemy1->CatchCollision(player) && !enemy2->CatchCollision(player) && !enemy3->CatchCollision(player))
	{
		float aX = enemy1->GetPos().x - player->GetPos().x;
		float aZ = enemy1->GetPos().z - player->GetPos().z;
		float aXZ = aX * aX + aZ * aZ;
		float axzDistanse = float(sqrt(aXZ));
		if (axzDistanse < 20.0f)
		{
			map->SetLightAction(true);
		}
		else
		{
			map->SetLightAction(false);
		}

		float aX2 = enemy2->GetPos().x - player->GetPos().x;
		float aZ2 = enemy2->GetPos().z - player->GetPos().z;
		float aXZ2 = aX2 * aX2 + aZ2 * aZ2;
		float axzDistanse2 = float(sqrt(aXZ2));
		if (axzDistanse2 < 20.0f)
		{
			map->SetLightAction(true);
		}
		else
		{
			map->SetLightAction(false);
		}

		float aX3 = enemy3->GetPos().x - player->GetPos().x;
		float aZ3 = enemy3->GetPos().z - player->GetPos().z;
		float aXZ3 = aX3 * aX3 + aZ3 * aZ3;
		float axzDistanse3 = float(sqrt(aXZ3));
		if (axzDistanse3 < 20.0f)
		{
			map->SetLightAction(true);
		}
		else
		{
			map->SetLightAction(false);
		}
	}
	
	//���֘A
	float vec[3];
	vec[0] = SoundVector::VectorSearch(enemy1->GetPos().x, enemy1->GetPos().z, player->GetPos().x, player->GetPos().z);
	vec[1] = SoundVector::VectorSearch(enemy2->GetPos().x, enemy2->GetPos().z, player->GetPos().x, player->GetPos().z);
	vec[2] = SoundVector::VectorSearch(enemy3->GetPos().x, enemy3->GetPos().z, player->GetPos().x, player->GetPos().z);
	bool soundFlag[3];
	soundFlag[0] = SoundVector::DistanceSearch(enemy1->GetPos().x, enemy1->GetPos().z, player->GetPos().x, player->GetPos().z);
	soundFlag[1] = SoundVector::DistanceSearch(enemy2->GetPos().x, enemy2->GetPos().z, player->GetPos().x, player->GetPos().z);
	soundFlag[2] = SoundVector::DistanceSearch(enemy3->GetPos().x, enemy3->GetPos().z, player->GetPos().x, player->GetPos().z) ;
	if (map->GetGateOpenFlag() && !enemy1->CatchCollision(player) && !enemy2->CatchCollision(player) && !enemy3->CatchCollision(player))
	{
		for (int i = 0; i < 3; i++)
		{
			soundTimer[i]++;
			
			const float sideValue = 45;
			if (soundFlag[i] && soundTimer[i] > 20 && !map->GetStopFlag())
			{
				if (-vec[i] + player->GetAngle() - 90 < -90 + sideValue && -vec[i] + player->GetAngle() - 90 > -90 - sideValue || -vec[i] + player->GetAngle() - 90 > 270 - sideValue && -vec[i] + player->GetAngle() - 90 < 270 + sideValue)
				{
					audio->PlaySE("Resources/seR.wav", false);
				}
				else if (-vec[i] + player->GetAngle() - 90 > 90 - sideValue && -vec[i] + player->GetAngle() - 90 < 90 + sideValue || -vec[i] + player->GetAngle() - 90 < -270 + sideValue && -vec[i] + player->GetAngle() - 90 > -270 - sideValue)
				{
					audio->PlaySE("Resources/seL.wav", false);
				}
				else
				{
					audio->PlaySE("Resources/seL.wav", false);
					audio->PlaySE("Resources/seR.wav", false);
				}
				soundTimer[i] = 0;
			}
		}
	}

	//���S�A�j���[�V����
	
	if (enemy1->DeathAnimation(player))
	{
		gameOverFlag = true;
	}
	if (enemy2->DeathAnimation(player))
	{
		gameOverFlag = true;
	}
	if (enemy3->DeathAnimation(player))
	{
		gameOverFlag = true;
	}
	
	//�X�g�b�v�t���O
	stopFlag = map->GetStopFlag();

	//�N���X�^���S������
	if (map->GetAllGetFlag())
	{
		clearFlag = true;//�N���A��
	}
}

void PlayScene::Draw(ID3D12GraphicsCommandList* cmdList,Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	
	enemy1->Draw(player, cmdList);//�G��3D�`��
	enemy2->Draw(player, cmdList);//�G��3D�`��
	enemy3->Draw(player, cmdList);//�G��3D�`��

	map->Draw();//�}�b�v��3D�`��

}

void PlayScene::DrawSprite(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	map->DrawSprite(player->GetPos());//�}�b�v�֘A�̃X�v���C�g
	player->DrawSprite();//�v���C���[�̃X�v���C�g
	
	enemy1->DrawSprite(map);//�G�l�~�[�X�v���C�g
	enemy2->DrawSprite(map);//�G�l�~�[�X�v���C�g
	enemy3->DrawSprite(map);//�G�l�~�[�X�v���C�g
	if (tutrialFlag == true) {
		spriteRule->Draw(1.0f);//���[���\���X�v���C�g
	}
}
