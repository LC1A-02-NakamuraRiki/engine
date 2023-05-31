#include "PlayScene.h"
#include "Input.h"
#include "SoundVector.h"
#include "ClearScene.h"
#include "GameOverScene.h"
#include"SceneManager.h"

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize(DebugCamera* camera)
{
	//ルールスプライト生成
	spriteRule = std::unique_ptr<Sprite>(Sprite::Create(30, { 0.0f,0.0f }));

	//グレインのON
	grainFlag = true;
}

void PlayScene::Update(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, DebugCamera* camera, LightGroop* light)
{
	//プレイヤーのカメラと移動
	camera->SetEye(player->GetPos());
	camera->SetTarget(player->GetTarget());

	//チュートリアル
	TutorialUpdate();

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
	LightCalculationFlag(player, map, enemy1, enemy2, enemy3);

	//音関連
	FootStepAudio(player, map, enemy1, enemy2, enemy3);

	//死亡アニメーション
	DeathAnimation(player, enemy1, enemy2, enemy3);
	
	//ストップフラグ
	stopFlag = map->GetStopFlag();

	//クリスタル全部入手
	ClearFlag(map);

	//マップギミック関連
	MapGimmick(player, map, enemy1, enemy2, enemy3);
}

void PlayScene::Draw3D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3, ID3D12GraphicsCommandList* cmdList)
{
	enemy1->Draw(player, cmdList);//敵の3D描画
	enemy2->Draw(player, cmdList);//敵の3D描画
	enemy3->Draw(player, cmdList);//敵の3D描画

	map->Draw();//マップの3D描画
}

void PlayScene::DrawPost2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
}

void PlayScene::Draw2D(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
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

void PlayScene::Finalize()
{
}

void PlayScene::TutorialUpdate()
{
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && tutrialFlag == true) {
		tutrialFlag = false;
	}
}

void PlayScene::LightCalculationFlag(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	//点滅する条件を満たしていないときに省略
	if (!map->GetGateOpenFlag() || enemy1->CatchCollision(player) || enemy2->CatchCollision(player) || enemy3->CatchCollision(player)){
		return;
	}

	//点滅するかどうかの計算
	LightCalculation(player, map, enemy1);
	LightCalculation(player, map, enemy2);
	LightCalculation(player, map, enemy3);
	
	//結果を反映
	if (ACTIONFLAG == true){
		map->SetLightAction(true);
	}
}

void PlayScene::LightCalculation(Player* player, MapChip* map, Enemy* enemy)
{
	float aX = enemy->GetPos().x - player->GetPos().x;
	float aZ = enemy->GetPos().z - player->GetPos().z;
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
}

void PlayScene::FootStepAudio(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	float vec[3];
	vec[0] = SoundVector::VectorSearch(enemy1->GetPos().x, enemy1->GetPos().z, player->GetPos().x, player->GetPos().z);
	vec[1] = SoundVector::VectorSearch(enemy2->GetPos().x, enemy2->GetPos().z, player->GetPos().x, player->GetPos().z);
	vec[2] = SoundVector::VectorSearch(enemy3->GetPos().x, enemy3->GetPos().z, player->GetPos().x, player->GetPos().z);
	bool soundFlag[3];
	soundFlag[0] = SoundVector::DistanceSearch(enemy1->GetPos().x, enemy1->GetPos().z, player->GetPos().x, player->GetPos().z);
	soundFlag[1] = SoundVector::DistanceSearch(enemy2->GetPos().x, enemy2->GetPos().z, player->GetPos().x, player->GetPos().z);
	soundFlag[2] = SoundVector::DistanceSearch(enemy3->GetPos().x, enemy3->GetPos().z, player->GetPos().x, player->GetPos().z);
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
}

void PlayScene::DeathAnimation(Player* player, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	if (enemy1->DeathAnimation(player))
	{
		GameOverChange();
	}
	if (enemy2->DeathAnimation(player))
	{
		GameOverChange();
	}
	if (enemy3->DeathAnimation(player))
	{
		GameOverChange();
	}
}

void PlayScene::GameOverChange()
{
	BaseScene* scene = new GameOverScene();//ゲームオーバーへ
	sceneManager_->SetNextScene(scene);	
}

void PlayScene::ClearFlag(MapChip* map)
{
	if (map->GetAllGetFlag()){
		BaseScene* scene = new ClearScene();//クリアへ
		sceneManager_->SetNextScene(scene);
	}
}

void PlayScene::MapGimmick(Player* player, MapChip* map, Enemy* enemy1, Enemy* enemy2, Enemy* enemy3)
{
	const float MAXALARTBALUE = 0.2f;
	const float ALARTSPEED = 0.02f;
	//追われている際のグレインのOFF
	alartGrainFlag = false;
	if (!map->GetGateOpenFlag())
	{
		alartValue = 0.0f;
	}
	else if (player->AlartFlag(map, enemy1->GetPos()) && alartValue < MAXALARTBALUE || player->AlartFlag(map, enemy2->GetPos()) && alartValue < MAXALARTBALUE || player->AlartFlag(map, enemy3->GetPos()) && alartValue < MAXALARTBALUE) {

		alartValue += ALARTSPEED;
		//追われている際のグレインのON
		alartGrainFlag = true;
	}
	else if (!player->AlartFlag(map, enemy1->GetPos()) && 0 < alartValue || !player->AlartFlag(map, enemy2->GetPos()) && 0 < alartValue || !player->AlartFlag(map, enemy3->GetPos()) && 0 < alartValue)
	{
		alartValue -= ALARTSPEED;
		//追われている際のグレインのON
		alartGrainFlag = true;
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
