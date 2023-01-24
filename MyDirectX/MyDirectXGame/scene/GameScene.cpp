#include "GameScene.h"
#include "Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "Input.h"
#include "SoundVector.h"

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteTitle);
	safe_delete(spriteTitle2);
	safe_delete(spriteTitle3);
	safe_delete(spriteOption);
	safe_delete(spriteOption2);
	safe_delete(spriteOption3);
	safe_delete(spriteClear);
	safe_delete(spriteGAMEOVER);
	safe_delete(spriteRule);
	safe_delete(spriteGrain[0]);
	safe_delete(spriteGrain[1]);
	safe_delete(spriteGrain[2]);
	safe_delete(spriteGrain[3]);
	safe_delete(spriteGrain[4]);
	safe_delete(spriteGrain[5]);
	safe_delete(spriteGrain[6]);
	safe_delete(spriteGrain[7]);
	safe_delete(particle3d);
	safe_delete(light);
	safe_delete(player);
	safe_delete(enemy[0]);
	safe_delete(enemy[1]);
	safe_delete(enemy[2]);
	safe_delete(map);

	safe_delete(objectWalking[0]);
	safe_delete(modelWalking[0]);
	safe_delete(objectWalking[1]);
	safe_delete(modelWalking[1]);
	safe_delete(objectWalking[2]);
	safe_delete(modelWalking[2]);

	safe_delete(objectAttack[0]);
	safe_delete(modelAttack[0]);
	safe_delete(objectAttack[1]);
	safe_delete(modelAttack[1]);
	safe_delete(objectAttack[2]);
	safe_delete(modelAttack[2]);
}

void GameScene::Initialize(DirectXCommon *dxCommon, Sound *audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(audio);

	this->dxCommon = dxCommon;
	this->audio = audio;

	camera = new DebugCamera(WinApp::window_width, WinApp::window_height);
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	particle3d = ParticleManager::Create(dxCommon->GetDevice(), camera);
	
	//スプライト
	// テクスチャ読み込み
	if (!Sprite::LoadTexture(18, L"Resources/Title.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(21, L"Resources/Title2.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(22, L"Resources/Title3.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(19, L"Resources/Clear.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(20, L"Resources/GAMEOVER.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(23, L"Resources/Option.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(24, L"Resources/Option2.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(25, L"Resources/Option3.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(30, L"Resources/tutrial.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(50, L"Resources/grain.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(51, L"Resources/grain2.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(52, L"Resources/grain3.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(53, L"Resources/grain4.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(54, L"Resources/grain5.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(55, L"Resources/grain6.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(56, L"Resources/grain7.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(57, L"Resources/grain8.png")) {
		assert(0);
		return;
	}
	//// 背景スプライト生成
	spriteTitle = Sprite::Create(18, { 0.0f,0.0f });
	spriteTitle2 = Sprite::Create(21, { 0.0f,0.0f });
	spriteTitle3 = Sprite::Create(22, { 0.0f,0.0f });
	spriteOption = Sprite::Create(23, { 0.0f,0.0f });
	spriteOption2 = Sprite::Create(24, { 0.0f,0.0f });
	spriteOption3 = Sprite::Create(25, { 0.0f,0.0f });
	spriteClear = Sprite::Create(19, { 0.0f,0.0f });
	spriteGAMEOVER = Sprite::Create(20, { 0.0f,0.0f });
	spriteRule = Sprite::Create(30, { 0.0f,0.0f });
	spriteGrain[0] = Sprite::Create(50, { 0.0f,0.0f });
	spriteGrain[1] = Sprite::Create(51, { 0.0f,0.0f });
	spriteGrain[2] = Sprite::Create(52, { 0.0f,0.0f });
	spriteGrain[3] = Sprite::Create(53, { 0.0f,0.0f });
	spriteGrain[4] = Sprite::Create(54, { 0.0f,0.0f });
	spriteGrain[5] = Sprite::Create(55, { 0.0f,0.0f });
	spriteGrain[6] = Sprite::Create(56, { 0.0f,0.0f });
	spriteGrain[7] = Sprite::Create(57, { 0.0f,0.0f });

	// 3Dオブジェクト生成

	// デバイスをセット
	FbxObject3d::SetDevice(dxCommon->GetDevice());
	// カメラをセット
	FbxObject3d::SetCamera(camera);
	// グラフィックスパイプライン生成
	FbxObject3d::CreateGraphicsPipeline();
	light = LightGroop::Create();
	
	Object3d::SetLightGroup(light);
	//ライト
	light->SetAmbientColor(XMFLOAT3(ambientColor0));

	light->SetDirLightDir(0, XMVECTOR({ lightDir0[0], lightDir0[1], lightDir0[2], 0 }));
	light->SetDirLightColor(0, XMFLOAT3(lightColor0));

	light->SetDirLightDir(1, XMVECTOR({ lightDir1[0], lightDir1[1], lightDir1[2], 0 }));
	light->SetDirLightColor(1, XMFLOAT3(lightColor1));

	light->SetDirLightDir(2, XMVECTOR({ lightDir2[0], lightDir2[1], lightDir2[2], 0 }));
	light->SetDirLightColor(2, XMFLOAT3(lightColor2));

	light->SetDirLightDir(3, XMVECTOR({ lightDir3[0], lightDir3[1], lightDir3[2], 0 }));
	light->SetDirLightColor(3, XMFLOAT3(lightColor3));

	light->SetDirLightDir(4, XMVECTOR({ lightDir4[0], lightDir4[1], lightDir4[2], 0 }));
	light->SetDirLightColor(4, XMFLOAT3(lightColor4));

	light->SetDirLightDir(5, XMVECTOR({ lightDir5[0], lightDir5[1], lightDir5[2], 0 }));
	light->SetDirLightColor(5, XMFLOAT3(lightColor5));
	player = new Player;
	player->Initialize();
	map = new MapChip;
	map->Initialize();
	
	for (int i = 0; i < 3; i++)
	{
		enemy[i] = new Enemy;
		enemy[i]->Initialize();
	}
	for (int i = 0; i < 3; i++)
	{
		modelWalking[i] = FbxLoader::GetInstance()->LoadModelFromFile("Walking");
		objectWalking[i] = new FbxObject3d;
		objectWalking[i]->Initialize();
		objectWalking[i]->SetModel(modelWalking[0]);
		objectWalking[i]->PlayAnimation();

		modelAttack[i] = FbxLoader::GetInstance()->LoadModelFromFile("Zombie Attack");
		objectAttack[i] = new FbxObject3d;
		objectAttack[i]->Initialize();
		objectAttack[i]->SetModel(modelAttack[0]);
		objectAttack[i]->PlayAnimation();
	}
}

void GameScene::Update()
{
	//int mapY = int((player->GetPos().z / 8) + ((21 + 1) / 2));
	//int mapX = int((player->GetPos().x / 8) + ((21 + 1) / 2));
	//debugText.Print(20.0f, 40.0f, 2.0f, "%d %d", mapX,mapY);
	//debugText.Print(20.0f, 20.0f, 2.0f, "%f %f", player->GetPos().x - enemy->GetPos().x, player->GetPos().z - enemy->GetPos().z);
	//debugText.Print(20.0f, 40.0f, 2.0f, "%d",map->GetArrayValue(mapX,mapY));
	
	
	//debugText.Print(20.0f, 20.0f, 2.0f, "%f %f", player->GetPos().x, player->GetPos().z);
	//debugText.Print(20.0f, 40.0f, 2.0f, "%f",player->GetViewAngle());
	//debugText.Print(20.0f, 20.0f, 2.0f, "%f %f", player->GetShortCut(map,enemy[1]->GetPos()).x, player->GetShortCut(map, enemy[1]->GetPos()).y);

	if (scene == TITLE)
	{
		titleTime = 0;
		objectWalking[0]->AnimationReset();
		objectWalking[1]->AnimationReset();
		objectWalking[2]->AnimationReset();

		objectWalking[0]->AnimationReset();
		objectWalking[1]->AnimationReset();
		objectWalking[2]->AnimationReset();

		if (Input::GetInstance()->KeybordTrigger(DIK_W) && buttonNo != 0 || Input::GetInstance()->KeybordTrigger(DIK_UP) && buttonNo != 0)
		{
			buttonNo--;
		}

		else if (Input::GetInstance()->KeybordTrigger(DIK_S) && buttonNo != 2 || Input::GetInstance()->KeybordTrigger(DIK_DOWN) && buttonNo != 2)
		{
			buttonNo++;
		}
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE)&& buttonNo == 0)
		{
			player->InitializeValue();
				
			enemy[0]->InitializeValue();
			enemy[1]->InitializeValue2();
			enemy[2]->InitializeValue3();
			
			map->InitializeValue();
			scene = PLAY;
		}
		else if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && buttonNo == 1)
		{
			scene = OPTION;
		}
	}
	else if (scene == OPTION)
	{
		if (Input::GetInstance()->KeybordTrigger(DIK_W) && optionButtonNo != 0 || Input::GetInstance()->KeybordTrigger(DIK_UP) && optionButtonNo != 0)
		{
			optionButtonNo--;
		}

		else if (Input::GetInstance()->KeybordTrigger(DIK_S) && optionButtonNo != 2 || Input::GetInstance()->KeybordTrigger(DIK_DOWN) && optionButtonNo != 2)
		{
			optionButtonNo++;
		}

		if (Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == 0)
		{
			player->SetViewSpeedPlus();
		}
		else if (Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == 0&& player->GetViewSpeed() >= 0.05)
		{
			player->SetViewSpeedMinus();
		}

		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == 1 && player->GetShakeFlag()||
			Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == 1 && player->GetShakeFlag()||
			Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == 1 && player->GetShakeFlag())
		{
			player->SetShakeFlag(false);
		}
		else if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == 1 && !player->GetShakeFlag() ||
			Input::GetInstance()->KeybordTrigger(DIK_A) && optionButtonNo == 1 && !player->GetShakeFlag() ||
			Input::GetInstance()->KeybordTrigger(DIK_D) && optionButtonNo == 1 && !player->GetShakeFlag())
		{
			player->SetShakeFlag(true);
		}

		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && optionButtonNo == 2)
		{
			scene = TITLE;
		}
	}
	else if (scene == PLAY)
	{
		titleTime++;
		grainCount++;
		
		if (grainCount > 7)
		{
			grainCount = 0;
		}
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE) && tutrialFlag == true)
		{
			tutrialFlag = false;
		}
		//プレイヤー系
		camera->SetEye(player->GetPos());
		camera->SetTarget(player->GetTarget());
		
		player->Update(map,tutrialFlag,enemy[0]->CatchCollision(player), enemy[1]->CatchCollision(player), enemy[2]->CatchCollision(player));
		camera->Update();
		light->Update();
		map->Update(player->GetPos(),player->GetMapPos(),enemy[0]->GetPos(), enemy[1]->GetPos(), enemy[2]->GetPos());
		stopFlag = map->GetStopFlag();
		if (map->GetStopFlag() || enemy[0]->GetStartStopTime() < 90)
		{
			objectWalking[0]->StopAnimation();
			objectWalking[1]->StopAnimation();
			objectWalking[2]->StopAnimation();
		}
		else
		{
			objectWalking[0]->playAnimation();
			objectWalking[1]->playAnimation();
			objectWalking[2]->playAnimation();
		}
		enemy[0]->Update(player, map, player->GetMapPos(), XMFLOAT2(0,0),enemy[1]->CatchCollision(player), enemy[2]->CatchCollision(player));
		enemy[1]->Update(player, map, player->GetMapPos(), player->GetShortCut(map,enemy[1]->GetPos()), enemy[0]->CatchCollision(player), enemy[2]->CatchCollision(player));
		enemy[2]->Update(player, map, player->GetMapPos(), player->GetShortCut(map, enemy[2]->GetPos()), enemy[0]->CatchCollision(player), enemy[1]->CatchCollision(player));

		for (int i = 0; i < 3; i++)
		{
			objectWalking[i]->SetPosition(XMFLOAT3(enemy[i]->GetPos().x, enemy[i]->GetPos().y - 2.8f, enemy[i]->GetPos().z));
			objectWalking[i]->SetRotation(XMFLOAT3(0, enemy[i]->GetRotation() + 90, 0));
			
		}
		for (int i = 0; i < 3; i++)
		{
			if (enemy[i]->CatchCollision(player)) {
				objectAttack[i]->SetPosition(XMFLOAT3(enemy[i]->GetPos().x, enemy[i]->GetPos().y - 2.8f, enemy[i]->GetPos().z));
				objectAttack[i]->SetRotation(XMFLOAT3(0, (XMConvertToDegrees(atan2(enemy[i]->GetPos().x - player->GetPos().x, enemy[i]->GetPos().z - player->GetPos().z)) + 270)-90, 0));

			}
			else
			{
				objectAttack[i]->AnimationReset();
			}
			bool lightAction = map->LightAction();
			objectWalking[i]->Update(lightAction);
			objectAttack[i]->Update(lightAction);
		}
		for (int i = 0; i < 3; i++)
		{
			if (map->GetGateOpenFlag() && !enemy[0]->CatchCollision(player) && !enemy[1]->CatchCollision(player) && !enemy[2]->CatchCollision(player))
			{
				float aX = enemy[i]->GetPos().x - player->GetPos().x;
				float aZ = enemy[i]->GetPos().z - player->GetPos().z;
				float aXZ = aX * aX + aZ * aZ;
				float axzDistanse = float(sqrt(aXZ));
				if (axzDistanse < 20.0f)
				{
					map->SetLightAction(true);
					i = 3;
				}
				else
				{
					map->SetLightAction(false);
				}
			}
		}
		if (map->GetGateOpenFlag() && !enemy[0]->CatchCollision(player) && !enemy[1]->CatchCollision(player) && !enemy[2]->CatchCollision(player))
		{
			for (int i = 0; i < 3; i++)
			{
				soundTimer[i]++;
				float vec = SoundVector::VectorSearch(enemy[i]->GetPos().x, enemy[i]->GetPos().z, player->GetPos().x, player->GetPos().z);
				float sideValue = 45;
				if (SoundVector::DistanceSearch(enemy[i]->GetPos().x, enemy[i]->GetPos().z, player->GetPos().x, player->GetPos().z) && soundTimer[i] > 20 && !map->GetStopFlag())
				{
					if (-vec + player->GetAngle() - 90 < -90 + sideValue && -vec + player->GetAngle() - 90 > -90 - sideValue || -vec + player->GetAngle() - 90 > 270 - sideValue && -vec + player->GetAngle() - 90 < 270 + sideValue)
					{
						audio->PlaySE("Resources/seR.wav", false);
					}
					else if (-vec + player->GetAngle() - 90 > 90 - sideValue && -vec + player->GetAngle() - 90 < 90 + sideValue || -vec + player->GetAngle() - 90 < -270 + sideValue && -vec + player->GetAngle() - 90 > -270 - sideValue)
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

		for (int i = 0; i < 3; i++)
		{
			if (enemy[i]->DeathAnimation(player))
			{
				scene = GAMEOVER;
			}
		}
		if (map->GetAllGetFlag())
		{
			scene = CLEAR;
		}
	}
	else if (scene == CLEAR)
	{
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
		{
			buttonNo = 0;
			scene = TITLE;
		}
	}
	else if (scene == GAMEOVER)
	{
		if (Input::GetInstance()->KeybordTrigger(DIK_SPACE))
		{
			buttonNo = 0;
			scene = TITLE;
		}
	}
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList *cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画g
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//-------------------------------------------------------------//

	//-------------------------------------------------------------//
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion
	
#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);
	//-------------------------------------------------------------//
	if (scene == PLAY)
	{
		map->Draw();
		/*for (int i = 0; i < 3; i++)
		{
			enemy[i]->Draw();
		}*/
	}
	for (int i = 0; i < 3; i++)
	{
		if (!enemy[i]->CatchCollision(player))
		{
			objectWalking[i]->Draw(cmdList);
		}
		else
		{
			objectAttack[i]->Draw(cmdList);
		}
	}
	//objectAttack->Draw(cmdList);
	//-------------------------------------------------------------//
	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

	particle3d->Draw(cmdList);
#pragma endregion

	
#pragma region 前景スプライト描画
	//// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	//-------------------------------------------------------------//


	//-------------------------------------------------------------//
	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}

void GameScene::PostOffDraw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//-------------------------------------------------------------//

	//-------------------------------------------------------------//
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);
	//-------------------------------------------------------------//

	//-------------------------------------------------------------//
	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

	particle3d->Draw(cmdList);
#pragma endregion


#pragma region 前景スプライト描画
	//// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	//-------------------------------------------------------------//
	if (scene == PLAY)
	{
		map->DrawSprite(player->GetPos());
		player->DrawSprite();
		for (int i = 0; i < 3; i++)
		{
			enemy[i]->DrawSprite(map);
		}
		if (tutrialFlag == true) {
			spriteRule->Draw(1.0f);
		}
		spriteGrain[grainCount]->Draw(0.75f);
	}

	if (scene == TITLE || scene == PLAY && titleTime < 5)
	{
		if (buttonNo == 0)
		{
			spriteTitle->Draw(1.0f);
		}
		else if (buttonNo == 1)
		{
			spriteTitle2->Draw(1.0f);
		}
		else if (buttonNo == 2)
		{
			spriteTitle3->Draw(1.0f);
		}
	}
	if (scene == OPTION)
	{
		debugText.Print(1300, 390, 2.0f, "%f", player->GetViewSpeed());
		if (player->GetShakeFlag())
		{
			debugText.Print(1335, 490, 2.0f, "ON");
		}
		else if (!player->GetShakeFlag())
		{
			debugText.Print(1325, 490, 2.0f, "OFF");
		}
		if (optionButtonNo == 0)
		{
			spriteOption->Draw(1.0f);
		}
		else if (optionButtonNo == 1)
		{
			spriteOption2->Draw(1.0f);
		}
		else if (optionButtonNo == 2)
		{
			spriteOption3->Draw(1.0f);
		}
	}
	if (scene == CLEAR)
	{
		spriteClear->Draw(1.0f);
	}
	if (scene == GAMEOVER)
	{
		spriteGAMEOVER->Draw(1.0f);
	}
	if (scene == PLAY)
	{

	}
	//-------------------------------------------------------------//
	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
	// スプライト描画後処理
	Sprite::PostDraw();
}

void GameScene::ParticlesCreate(XMFLOAT3 Pos)
{
	for (int i = 0; i < 1; i++)
	{
		//X,Y,Z全て{-5.0f,+5.0f}でランダムに分布
		const float md_pos = 0.5f;
		XMFLOAT3 pos = Pos;
		pos.x += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.z += (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		////X,Y,Z全て{-0.05f,+0.05f}でランダムに分布
		const float md_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		//重力に見立ててYのみ{-0.001f,0}でランダム分布
		XMFLOAT3 acc{};
		const float md_acc = 0.001f;
		acc.y = (float)rand() / RAND_MAX * md_acc;

		int time = 60;
		float s_scale = 1.0f;
		float e_scale = 1.0f;
		XMFLOAT4 color = { 1,1,1,1 };
		// 追加
		particle3d->Add(time, pos, vel, acc, s_scale, e_scale, color);
	}
}
