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

	//プレイヤーのカメラと移動
	camera->SetEye(player->GetPos());
	camera->SetTarget(player->GetTarget());

	//チュートリアル
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && tutrialFlag == true)
	{
		tutrialFlag = false;
	}

	//プレイヤーのアップデート
	player->Update(map, tutrialFlag, enemy1->CatchCollision(player), enemy2->CatchCollision(player), enemy3->CatchCollision(player));

	//カメラアップデート
	camera->Update();

	//ライトアップデート
	light->Update();

	//マップアップデート
	map->Update(player->GetPos(), player->GetMapPos(), enemy1->GetPos(), enemy2->GetPos(), enemy3->GetPos());

	//エネミーアップデート
	enemy1->Update(player, map, player->GetMapPos(), XMFLOAT2(0, 0), enemy2->CatchCollision(player), enemy3->CatchCollision(player));
	enemy2->Update(player, map, player->GetMapPos(), player->GetShortCut(map, enemy2->GetPos()), enemy1->CatchCollision(player), enemy3->CatchCollision(player));
	enemy3->Update(player, map, player->GetMapPos(), player->GetShortCut(map, enemy3->GetPos()), enemy1->CatchCollision(player), enemy2->CatchCollision(player));

	//ライト点滅関連
	
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
	
	//音関連
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

	//死亡アニメーション
	
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
	
	//ストップフラグ
	stopFlag = map->GetStopFlag();

	//クリスタル全部入手
	if (map->GetAllGetFlag())
	{
		clearFlag = true;//クリアへ
	}
}

void PlayScene::Draw(ID3D12GraphicsCommandList* cmdList,Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	
	enemy1->Draw(player, cmdList);//敵の3D描画
	enemy2->Draw(player, cmdList);//敵の3D描画
	enemy3->Draw(player, cmdList);//敵の3D描画

	map->Draw();//マップの3D描画

}

void PlayScene::DrawSprite(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	map->DrawSprite(player->GetPos());//マップ関連のスプライト
	player->DrawSprite();//プレイヤーのスプライト
	
	enemy1->DrawSprite(map);//エネミースプライト
	enemy2->DrawSprite(map);//エネミースプライト
	enemy3->DrawSprite(map);//エネミースプライト
	if (tutrialFlag == true) {
		spriteRule->Draw(1.0f);//ルール表示スプライト
	}
}
