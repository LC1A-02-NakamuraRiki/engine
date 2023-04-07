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
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && tutrialFlag == true){
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
		bool ACTIONFLAG = false;
		const float MAXDISTANCE = 32.0f;
		float aX = enemy1->GetPos().x - player->GetPos().x;
		float aZ = enemy1->GetPos().z - player->GetPos().z;
		float aXZ = aX * aX + aZ * aZ;
		float axzDistanse = float(sqrt(aXZ));
		if (axzDistanse < MAXDISTANCE)
		{
			ACTIONFLAG = true;
		}
		else
		{
			map->SetLightAction(false);
		}

		float aX2 = enemy2->GetPos().x - player->GetPos().x;
		float aZ2 = enemy2->GetPos().z - player->GetPos().z;
		float aXZ2 = aX2 * aX2 + aZ2 * aZ2;
		float axzDistanse2 = float(sqrt(aXZ2));
		if (axzDistanse2 < MAXDISTANCE)
		{
			ACTIONFLAG = true;
		}
		else
		{
			map->SetLightAction(false);
		}

		float aX3 = enemy3->GetPos().x - player->GetPos().x;
		float aZ3 = enemy3->GetPos().z - player->GetPos().z;
		float aXZ3 = aX3 * aX3 + aZ3 * aZ3;
		float axzDistanse3 = float(sqrt(aXZ3));
		if (axzDistanse3 < MAXDISTANCE)
		{
			ACTIONFLAG = true;
		}
		else
		{
			map->SetLightAction(false);
		}
		if(ACTIONFLAG == true)
		{
			map->SetLightAction(true);
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
	const float MAXENEMYVALUE = 3;
	if (map->GetGateOpenFlag() && !enemy1->CatchCollision(player) && !enemy2->CatchCollision(player) && !enemy3->CatchCollision(player))
	{
		for (int i = 0; i < MAXENEMYVALUE; i++)
		{
			soundTimer[i]++;
			
			const float sideValue = 45.0f;
			const int MAXDELAYTIME = 20;
			const float LEFTVALUE = 90.0f;
			const float RIGHTVALUE = 270.0f;

			if (soundFlag[i] && soundTimer[i] > MAXDELAYTIME && !map->GetStopFlag())
			{
				if (-vec[i] + player->GetAngle() - LEFTVALUE < -LEFTVALUE + sideValue && -vec[i] + player->GetAngle() - LEFTVALUE > -LEFTVALUE - sideValue || -vec[i] + player->GetAngle() - LEFTVALUE > RIGHTVALUE - sideValue && -vec[i] + player->GetAngle() - LEFTVALUE < RIGHTVALUE + sideValue)
				{
					audio->PlaySE("Resources/seR.wav", false);
				}
				else if (-vec[i] + player->GetAngle() - LEFTVALUE > LEFTVALUE - sideValue && -vec[i] + player->GetAngle() - LEFTVALUE < LEFTVALUE + sideValue || -vec[i] + player->GetAngle() - LEFTVALUE < -RIGHTVALUE + sideValue && -vec[i] + player->GetAngle() - LEFTVALUE > -RIGHTVALUE - sideValue)
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

	const float MAXALARTBALUE = 0.2f;
	const float ALARTSPEED = 0.02f;
	if (!map->GetGateOpenFlag())
	{
		alartValue = 0.0f;
	}
	else if (player->AlartFlag(map, enemy1->GetPos())&& alartValue < MAXALARTBALUE || player->AlartFlag(map, enemy2->GetPos()) && alartValue < MAXALARTBALUE || player->AlartFlag(map, enemy3->GetPos()) && alartValue < MAXALARTBALUE) {
		
		alartValue += ALARTSPEED;
	}
	else if (!player->AlartFlag(map,enemy1->GetPos()) && 0 < alartValue || !player->AlartFlag(map, enemy2->GetPos()) && 0 < alartValue|| !player->AlartFlag(map, enemy3->GetPos()) && 0 < alartValue)
	{
		alartValue -= ALARTSPEED;
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

float PlayScene::GetShVa1(Player* player, MapChip* map, Enemy* enemy2)
{
	return player->GetShortCut(map, enemy2->GetPos()).x;
}

float PlayScene::GetShVa2(Player* player, MapChip* map, Enemy* enemy2)
{
	return player->GetShortCut(map, enemy2->GetPos()).y;
}

float PlayScene::GetShVa3(Player* player, MapChip* map, Enemy* enemy3)
{
	return player->GetShortCut(map, enemy3->GetPos()).x;
}

float PlayScene::GetShVa4(Player* player, MapChip* map, Enemy* enemy3)
{
	return player->GetShortCut(map, enemy3->GetPos()).y;
}
