#include "PlayScene.h"
#include "Input.h"
#include "SoundVector.h"
#include "Sound.h"

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	camera = std::make_unique<DebugCamera>(DebugCamera(WinApp::window_width, WinApp::window_height));
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera.get());

	light = std::unique_ptr<LightGroop>(LightGroop::Create());
	//ライトのセット
	Object3d::SetLightGroup(light.get());

	//ライト関連
	light->SetAmbientColor(XMFLOAT3({ ambientColor0[0],ambientColor0[1] ,ambientColor0[2] }));
	light->SetDirLightDir(0, XMVECTOR({ lightDir0[0], lightDir0[1], lightDir0[2], 0 }));
	light->SetDirLightColor(0, XMFLOAT3({ lightColor0[0],lightColor0[1] ,lightColor0[2] }));
	light->SetDirLightDir(1, XMVECTOR({ lightDir1[0], lightDir1[1], lightDir1[2], 0 }));
	light->SetDirLightColor(1, XMFLOAT3({ lightColor1[0],lightColor1[1] ,lightColor1[2] }));
	light->SetDirLightDir(2, XMVECTOR({ lightDir2[0], lightDir2[1], lightDir2[2], 0 }));
	light->SetDirLightColor(2, XMFLOAT3({ lightColor2[0],lightColor2[1] ,lightColor2[2] }));
	light->SetDirLightDir(3, XMVECTOR({ lightDir3[0], lightDir3[1], lightDir3[2], 0 }));
	light->SetDirLightColor(3, XMFLOAT3({ lightColor3[0],lightColor3[1] ,lightColor3[2] }));
	light->SetDirLightDir(4, XMVECTOR({ lightDir4[0], lightDir4[1], lightDir4[2], 0 }));
	light->SetDirLightColor(4, XMFLOAT3({ lightColor4[0],lightColor4[1] ,lightColor4[2] }));
	light->SetDirLightDir(5, XMVECTOR({ lightDir5[0], lightDir5[1], lightDir5[2], 0 }));
	light->SetDirLightColor(5, XMFLOAT3({ lightColor5[0],lightColor5[1] ,lightColor5[2] }));
	//プレイヤー初期化
	player = std::make_unique<Player>();
	player->Initialize();
	//マップ初期化
	map = std::make_unique<MapChip>();
	map->Initialize();

	//敵初期化
	const int MAXENEMYNUM = 3;
	for (int i = 0; i < MAXENEMYNUM; i++) {
		enemy[i] = std::make_unique <Enemy>();
		enemy[i]->Initialize();
	}

	map = std::make_unique<MapChip>();
	map->Initialize();

	player->InitializeValue();
	map->InitializeValue();

	if (!Sprite::LoadTexture(30, L"Resources/tutrial.png")) {
		assert(0);
		return;
	}
	spriteRule = std::unique_ptr<Sprite>(Sprite::Create(30, { 0.0f,0.0f }));
}

void PlayScene::Update()
{

	//プレイヤーのカメラと移動
	camera->SetEye(player->GetPos());
	camera->SetTarget(player->GetTarget());

	//チュートリアル
	if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && tutrialFlag == true){
		tutrialFlag = false;
	}

	//プレイヤーのアップデート
	player->Update(map.get(), tutrialFlag, enemy[0]->CatchCollision(player.get()), enemy[1]->CatchCollision(player.get()), enemy[2]->CatchCollision(player.get()));

	//カメラアップデート
	camera->Update();

	//ライトアップデート
	light->Update();

	//マップアップデート
	map->Update(player->GetPos(), player->GetMapPos(), enemy[0]->GetPos(), enemy[1]->GetPos(), enemy[2]->GetPos());

	//エネミーアップデート
	enemy[0]->Update(player.get(), map.get(), player->GetMapPos(), XMFLOAT2(0, 0), enemy[1]->CatchCollision(player.get()), enemy[2]->CatchCollision(player.get()));
	enemy[1]->Update(player.get(), map.get(), player->GetMapPos(), player->GetShortCut(map.get(), enemy[1]->GetPos()), enemy[0]->CatchCollision(player.get()), enemy[2]->CatchCollision(player.get()));
	enemy[2]->Update(player.get(), map.get(), player->GetMapPos(), player->GetShortCut(map.get(), enemy[2]->GetPos()), enemy[0]->CatchCollision(player.get()), enemy[1]->CatchCollision(player.get()));

	//ライト点滅関連
	
	if (map->GetGateOpenFlag() && !enemy[0]->CatchCollision(player.get()) && !enemy[1]->CatchCollision(player.get()) && !enemy[2]->CatchCollision(player.get()))
	{
		bool ACTIONFLAG = false;
		const float MAXDISTANCE = 32.0f;
		float aX = enemy[0]->GetPos().x - player->GetPos().x;
		float aZ = enemy[0]->GetPos().z - player->GetPos().z;
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

		float aX2 = enemy[1]->GetPos().x - player->GetPos().x;
		float aZ2 = enemy[1]->GetPos().z - player->GetPos().z;
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

		float aX3 = enemy[2]->GetPos().x - player->GetPos().x;
		float aZ3 = enemy[2]->GetPos().z - player->GetPos().z;
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
	
	//音関連
	float vec[3];
	vec[0] = SoundVector::VectorSearch(enemy[0]->GetPos().x, enemy[0]->GetPos().z, player->GetPos().x, player->GetPos().z);
	vec[1] = SoundVector::VectorSearch(enemy[1]->GetPos().x, enemy[1]->GetPos().z, player->GetPos().x, player->GetPos().z);
	vec[2] = SoundVector::VectorSearch(enemy[2]->GetPos().x, enemy[2]->GetPos().z, player->GetPos().x, player->GetPos().z);
	bool soundFlag[3];
	soundFlag[0] = SoundVector::DistanceSearch(enemy[0]->GetPos().x, enemy[0]->GetPos().z, player->GetPos().x, player->GetPos().z);
	soundFlag[1] = SoundVector::DistanceSearch(enemy[1]->GetPos().x, enemy[1]->GetPos().z, player->GetPos().x, player->GetPos().z);
	soundFlag[2] = SoundVector::DistanceSearch(enemy[2]->GetPos().x, enemy[2]->GetPos().z, player->GetPos().x, player->GetPos().z) ;
	const float MAXENEMYVALUE = 3;
	if (map->GetGateOpenFlag() && !enemy[0]->CatchCollision(player.get()) && !enemy[1]->CatchCollision(player.get()) && !enemy[2]->CatchCollision(player.get()))
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
					//audio->PlaySE("Resources/seR.wav", false);
				}
				else if (-vec[i] + player->GetAngle() - LEFTVALUE > LEFTVALUE - sideValue && -vec[i] + player->GetAngle() - LEFTVALUE < LEFTVALUE + sideValue || -vec[i] + player->GetAngle() - LEFTVALUE < -RIGHTVALUE + sideValue && -vec[i] + player->GetAngle() - LEFTVALUE > -RIGHTVALUE - sideValue)
				{
					//audio->PlaySE("Resources/seL.wav", false);
				}
				else
				{
					//audio->PlaySE("Resources/seL.wav", false);
					//audio->PlaySE("Resources/seR.wav", false);
				}
				soundTimer[i] = 0;
			}
		}
	}

	//死亡アニメーション
	
	if (enemy[0]->DeathAnimation(player.get()))
	{
		gameOverFlag = true;
	}
	if (enemy[1]->DeathAnimation(player.get()))
	{
		gameOverFlag = true;
	}
	if (enemy[2]->DeathAnimation(player.get()))
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

	const float MAXALARTBALUE = 0.2f;
	const float ALARTSPEED = 0.02f;
	if (!map->GetGateOpenFlag())
	{
		alartValue = 0.0f;
	}
	else if (player->AlartFlag(map.get(), enemy[0]->GetPos()) && alartValue < MAXALARTBALUE || player->AlartFlag(map.get(), enemy[1]->GetPos()) && alartValue < MAXALARTBALUE || player->AlartFlag(map.get(), enemy[2]->GetPos()) && alartValue < MAXALARTBALUE) {
		
		alartValue += ALARTSPEED;
	}
	else if (!player->AlartFlag(map.get(),enemy[0]->GetPos()) && 0 < alartValue || !player->AlartFlag(map.get(), enemy[1]->GetPos()) && 0 < alartValue || !player->AlartFlag(map.get(), enemy[2]->GetPos()) && 0 < alartValue)
	{
		alartValue -= ALARTSPEED;
	}
}

void PlayScene::Draw(ID3D12GraphicsCommandList* cmdList)
{
	
	enemy[0]->Draw(player.get(), cmdList);//敵の3D描画
	enemy[1]->Draw(player.get(), cmdList);//敵の3D描画
	enemy[2]->Draw(player.get(), cmdList);//敵の3D描画

	map->Draw();//マップの3D描画

}

void PlayScene::SpriteDraw()
{
	map->DrawSprite(player->GetPos());//マップ関連のスプライト
	player->DrawSprite();//プレイヤーのスプライト
	
	enemy[0]->DrawSprite(map.get());//エネミースプライト
	enemy[1]->DrawSprite(map.get());//エネミースプライト
	enemy[2]->DrawSprite(map.get());//エネミースプライト
	if (tutrialFlag == true) {
		spriteRule->Draw(1.0f);//ルール表示スプライト
	}
}

void PlayScene::Finalize()
{
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
