#include "enemy.h"
#include "Collision.h"
#include "Input.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"

using namespace DirectX;

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	//敵初期化
	modelWalking = std::unique_ptr<FbxModel>(FbxLoader::GetInstance()->LoadModelFromFile("Walking"));//モデル初期化
	objectWalking = std::make_unique<FbxObject3d>();//object初期化
	objectWalking->Initialize();//初期化
	objectWalking->SetModel(modelWalking.get());//モデルと同期
	objectWalking->PlayAnimation();//アニメーション


	//敵初期化
	modelAttack = std::unique_ptr<FbxModel>(FbxLoader::GetInstance()->LoadModelFromFile("Zombie Attack"));//モデル初期化
	objectAttack = std::make_unique<FbxObject3d>();//object初期化
	objectAttack->Initialize();//初期化
	objectAttack->SetModel(modelAttack.get());//モデルと同期
	objectAttack->PlayAnimation();//アニメーション

	//画像読み込み
	if (!Sprite::LoadTexture(4, L"Resources/enemyDot.png")) {
		assert(0);
		return;
	}
	//画像読み込み
	if (!Sprite::LoadTexture(99, L"Resources/DeadEf.png")) {
		assert(0);
		return;
	}
	//スプライト読み込み
	spriteEnemyDot = std::unique_ptr<Sprite>(Sprite::Create(4, miniMapPos));
	spriteEnemyAngle = std::unique_ptr<Sprite>(Sprite::Create(6, miniMapPos));
	spriteDeadEffect = std::unique_ptr<Sprite>(Sprite::Create(99, { 0,0 }));
}

//鬼ごとの初期化
void Enemy::InitializeValue()
{
	objectWalking->AnimationReset();
	objectAttack->AnimationReset();

	//鬼ごとの初期化
	pos = { -4.0f,3.0f,-28.0f };//位置
	angle = 360;//向き
	nowMove = static_cast<int>(MoveVector::UP);//進む向き
	adjustValueX = 0;//調整値X
	adjustValueZ = 0;//調整値Z
	speed = 0.2f;//スピード
	vReserveFlag = false;//優先度
	miniMapPos = { 100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 7) };//ミニマップ位置
	maxAdjustmentTime = 40;//調整タイム

	wallHitFlag = false;//先読みの座標が壁に当たっているか
	adjustmentFlag = false;//位置調整フラグ
	killTime = 0;//殴りモーションの時間
	startStopTime = 0;//スタートまでの硬直時間
	deadPos = { 0.0f,2.5f,0.0f };
	deadView = 0.0f;
	deadAlpha = 0.0f;
}

void Enemy::InitializeValue2()
{
	objectWalking->AnimationReset();
	objectAttack->AnimationReset();
	//鬼ごとの初期化
	pos = { 4.0f,3.0f,68.0f };//位置
	nowMove = static_cast<int>(MoveVector::LEFT);//進む向き
	adjustValueX = 0;//調整値X
	adjustValueZ = 0;//調整値Z
	speed = 0.16f;//スピード
	vReserveFlag = false;//優先度
	miniMapPos = { 100 + (MAPWALLSIZE * 9),650 + (MAPWALLSIZE * 19) };//ミニマップ位置
	maxAdjustmentTime = 49;//調整タイム
	wallHitFlag = false;//先読みの座標が壁に当たっているか
	adjustmentFlag = false;//位置調整フラグ
	killTime = 0;//殴りモーションの時間
	startStopTime = 0;//スタートまでの硬直時間
	deadPos = { 0.0f,2.5f,0.0f };
	deadView = 0.0f;
	deadAlpha = 0.0f;
}

void Enemy::InitializeValue3()
{
	objectWalking->AnimationReset();
	objectAttack->AnimationReset();
	//鬼ごとの初期化
	pos = { -76.0f,3.0f,-12.0f };//位置
	nowMove = static_cast<int>(MoveVector::UP);//進む向き
	adjustValueX = 0;//調整値X
	adjustValueZ = 0;//調整値Z
	speed = 0.16f;//スピード
	vReserveFlag = false;//優先度
	miniMapPos = { 100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 9) };//ミニマップ位置
	maxAdjustmentTime = 49;//調整タイム
	wallHitFlag = false;//先読みの座標が壁に当たっているか
	adjustmentFlag = false;//位置調整フラグ
	killTime = 0;//殴りモーションの時間
	startStopTime = 0;//スタートまでの硬直時間
	deadPos = { 0.0f,2.5f,0.0f };
	deadView = 0.0f;
	deadAlpha = 0.0f;
}

void Enemy::Update(Player* player, MapChip* mapChip, XMFLOAT2 mapPos, XMFLOAT2 plusValue, bool catchFlag1, bool catchFlag2)
{
	//探索
	AI(player, mapChip, plusValue);

	//移動
	if (StartFlag(player, mapChip, catchFlag1, catchFlag2)) {//移動可能か
		Move(player, mapChip, mapPos);
	}

	//オブジェクトのアップデート
	ObjectUpdate(player, mapChip);
}

void Enemy::ObjectUpdate(Player* player, MapChip* mapChip)
{
	//アニメーション
	if (AnimationStop(mapChip)) {
		objectWalking->StopAnimation();
	}
	else {
		objectWalking->playAnimation();
	}

	objectWalking->SetPosition(XMFLOAT3(pos.x, pos.y - 2.8f, pos.z));
	objectWalking->SetRotation(XMFLOAT3(0, angle, 0));

	if (CatchCollision(player)) {
		objectAttack->SetPosition(XMFLOAT3(pos.x, pos.y - 2.8f, pos.z));
		objectAttack->SetRotation(XMFLOAT3(0, (XMConvertToDegrees(atan2(pos.x - player->GetPos().x, pos.z - player->GetPos().z)) + 270) - 90, 0));
	}
	else {
		objectAttack->AnimationReset();
	}

	//ライトの情報を参照
	bool lightAction = mapChip->LightAction();
	objectWalking->Update(lightAction);//アップデート
	objectAttack->Update(lightAction);//アップデート

}

void Enemy::Draw(Player* player, ID3D12GraphicsCommandList* cmdList)
{
	if (!CatchCollision(player))//捕まってないとき
	{
		objectWalking->Draw(cmdList);//エネミー歩き描画
	}
	else//捕まった時
	{
		objectAttack->Draw(cmdList);//エネミーアタック描画
	}
}

void Enemy::DrawSprite(MapChip* mapChip)
{
	//スタートしたかどうか
	if (mapChip->GetDisplayFlag() && spriteEnemyDot->GetPosition().x < 420 && spriteEnemyDot->GetPosition().x > 100
		&& spriteEnemyDot->GetPosition().y > 650 && spriteEnemyDot->GetPosition().y < 986)
	{
		spriteEnemyAngle->Draw(1.0f);//見ている方向描画
		spriteEnemyDot->Draw(1.0f);//エネミーのドット描画
	}
	if (killTime > 45)
	{
		deadAlpha += 0.01f;
		spriteDeadEffect->Draw(deadAlpha);
	}
	spriteEnemyDot->Draw(1.0f);//エネミーのドット描画
}

void Enemy::AI(Player* player, MapChip* mapChip, XMFLOAT2 plusValue)
{
	AiPriority(player, plusValue);

	if (adjustmentFlag)//位置調整フラグ
	{
		adjustmentTime++;
		if (adjustmentTime >= maxAdjustmentTime)
		{
			adjustmentTime = 0;
			adjustmentFlag = false;
		}
	}
	else if (!adjustmentFlag)//位置調整フラグ
	{
		if (NodeValue(mapChip) == static_cast<int>(AriaValue::LEFTTOP))//上左角
		{
			CornerJudge(MoveVector::UP, MoveVector::RIGHT);
			CornerJudge(MoveVector::LEFT, MoveVector::DOWN);
		}
		else if (NodeValue(mapChip) == static_cast<int>(AriaValue::CENTERTOP))//上中心
		{
			ThreeWayJudge1();
		}
		else if (NodeValue(mapChip) == static_cast<int>(AriaValue::RIGHTTOP))//上右角
		{
			CornerJudge(MoveVector::RIGHT, MoveVector::DOWN);
			CornerJudge(MoveVector::UP, MoveVector::LEFT);
		}
		else if (NodeValue(mapChip) == static_cast<int>(AriaValue::LEFTMIDDLE))//中央左
		{
			ThreeWayJudge2();
		}
		else if (NodeValue(mapChip) == static_cast<int>(AriaValue::CENTERMIDDLE))//中央
		{
			FourWayJudge();
		}
		else if (NodeValue(mapChip) == static_cast<int>(AriaValue::RIGHTMIDDLE))//中央右
		{
			ThreeWayJudge3();
		}
		else if (NodeValue(mapChip) == static_cast<int>(AriaValue::LEFTBOTTOM))//下左角
		{
			CornerJudge(MoveVector::LEFT, MoveVector::UP);
			CornerJudge(MoveVector::DOWN, MoveVector::RIGHT);
		}
		else if (NodeValue(mapChip) == static_cast<int>(AriaValue::CENTERBOTTOM))//下中央
		{
			ThreeWayJudge4();
		}
		else if (NodeValue(mapChip) == static_cast<int>(AriaValue::RIGHTBOTTOM))//下右角
		{
			CornerJudge(MoveVector::DOWN, MoveVector::LEFT);
			CornerJudge(MoveVector::RIGHT, MoveVector::UP);
		}
	}
}

void Enemy::Move(Player* player, MapChip* mapChip, XMFLOAT2 mapPos)
{
	if (mapChip->GetStopFlag() == false)//STOP発動してるか
	{
		if (nowMove == static_cast<int>(MoveVector::DOWN))//下に移動
		{
			MoveValue(45, 360, 0, 1, 0, -1);
		}
		else if (nowMove == static_cast<int>(MoveVector::UP))//上に移動
		{
			MoveValue(-135, 180, 0, -1, 0, 1);
		}
		else if (nowMove == static_cast<int>(MoveVector::RIGHT))//右に移動
		{
			MoveValue(135, 90, 1, 0, -1, 0);
		}
		else if (nowMove == static_cast<int>(MoveVector::LEFT))//左に移動
		{
			MoveValue(-45, 270, -1, 0, 1, 0);
		}
	}

	//obj等に影響
	const float enemyAngleAdjustValue = 8.0f;
	spriteEnemyDot->SetPosition({ miniMapPos.x + mapPos.x , miniMapPos.y + mapPos.y });//位置セット
	spriteEnemyAngle->SetPosition({ miniMapPos.x + mapPos.x + enemyAngleAdjustValue, miniMapPos.y + mapPos.y + enemyAngleAdjustValue });//位置セット
}

void Enemy::MoveValue(float spriteAngle, float objectAngle, float xSpeed, float zSpeed, float adjustX, float adjustZ)
{
	spriteEnemyAngle->SetRotation(spriteAngle);//角度をセット
	angle = objectAngle;//角度の値をセット
	pos.x += speed * xSpeed;//移動スピード
	pos.z += speed * zSpeed;//移動スピード
	miniMapPos.x -= (speed * 2) * xSpeed;//ミニマップの移動
	miniMapPos.y += (speed * 2) * zSpeed;//ミニマップの移動
	adjustValueX = 3.9f * adjustX;//調整値セット
	adjustValueZ = 3.9f * adjustZ;//調整値セット
}

bool Enemy::CatchCollision(Player* player)
{
	XMFLOAT3 playerPos = player->GetPos();//座標取得
	return Collision::ChenkSphere2Sphere(playerPos, pos, 2.5f, 3.0f);//プレイヤーと当たったか
}

bool Enemy::DeathAnimation(Player* player)
{
	if (CatchCollision(player))//捕まったか
	{
		//角度調べ
		float aX = player->GetPos().x - pos.x;//xのベクトル
		float aZ = player->GetPos().z - pos.z;//zのベクトル
		float aXZ = XMConvertToDegrees(float(atan2(aX, aZ)));//角度算出
		XMFLOAT3 playerPos = { 0,0,0 };
		playerPos = player->GetPos();
		if (player->GetViewAngle() < aXZ + 30 && player->GetViewAngle() > aXZ - 30)//敵の方向ききった
		{
			player->SetViewAngleY2(aXZ);
			player->SetViewAngleX2(10);

			killTime++;
		}
		else if (player->GetViewAngle() < aXZ)//敵の方向いてないとき
		{
			player->SetViewAngleY(15);
		}
		else if (player->GetAngle() > aXZ)//敵の方向いてないとき
		{
			player->SetViewAngleY(-15);
		}

		if (killTime > 45)//モーション終わったか
		{
			if (killTime > 50)//モーション終わったか
			{
				player->SetViewAngleX2(70.0f);
			}
			//少しづつ上向くのと血の演出
			else if (killTime > 45)
			{
				deadAlphaCountFlag = true;
				deadView += 9;
				player->SetViewAngleX2(10.0f + deadView);
			}

			//倒れる
			if (deadPos.y >= 0.0f)
			{
				deadPos.y -= 0.25f;
			}
			playerPos.y = deadPos.y;
			player->SetPos(playerPos);
		}
		if (killTime > 150)//モーション終わったか
		{
			killTime = 0;
			return true;
		}
	}
	return false;
}

bool Enemy::StartFlag(Player* player, MapChip* mapChip, bool catchFlag1, bool catchFlag2)
{
	if (mapChip->GetGateOpenFlag() && !catchFlag1 && !catchFlag2)//スタートしているか、捕まっていないか
	{
		startStopTime++;//スタートまでの硬直タイム
		if (!CatchCollision(player) && startStopTime > 90)//スタートしたか
		{
			return true;
		}
	}
	return false;
}

bool Enemy::AnimationStop(MapChip* mapChip)
{
	if (mapChip->GetStopFlag() || startStopTime < 90)
	{
		return true;
	}
	return false;
}

void Enemy::AiPriority(Player* player, XMFLOAT2 plusValue)
{
	XMFLOAT3 playerPos = player->GetPos();

	//距離調べ
	vectorX = playerPos.x + plusValue.x - pos.x;
	vectorZ = playerPos.z + plusValue.y - pos.z;
	//優先度調べ
	if ((vectorX * vectorX) < (vectorZ * vectorZ))
	{
		vReserveFlag = true;
	}
	else if ((vectorX * vectorX) >= (vectorZ * vectorZ))
	{
		vReserveFlag = false;
	}
}

int Enemy::NodeValue(MapChip* mapChip)
{
	return mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ);
}

int Enemy::CornerJudge(MoveVector vec, MoveVector result)
{
	if (nowMove == static_cast<int>(vec)) {
		adjustmentFlag = true;
		return static_cast<int>(result);
	}
	return -1;
}

void Enemy::ThreeWayJudge1()
{
	if (nowMove != static_cast<int>(MoveVector::LEFT) && vReserveFlag == false && 0 < vectorX)
	{
		nowMove = static_cast<int>(MoveVector::RIGHT);
		adjustmentFlag = true;
	}
	else if (nowMove != static_cast<int>(MoveVector::RIGHT) && vReserveFlag == false && vectorX < 0)
	{
		nowMove = static_cast<int>(MoveVector::LEFT);
		adjustmentFlag = true;
	}
	else if (nowMove != static_cast<int>(MoveVector::UP) && vReserveFlag == true && vectorZ >= 0)
	{
		nowMove = static_cast<int>(MoveVector::DOWN);
		adjustmentFlag = true;
	}
	else if (nowMove == static_cast<int>(MoveVector::UP))
	{
		if (vectorX <= 0)
		{
			nowMove = static_cast<int>(MoveVector::LEFT);
			adjustmentFlag = true;
		}
		if (vectorX > 0)
		{
			nowMove = static_cast<int>(MoveVector::RIGHT);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::LEFT))
	{
		if (vectorZ > 0)
		{
			nowMove = static_cast<int>(MoveVector::DOWN);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::RIGHT))
	{
		if (vectorZ > 0)
		{
			nowMove = static_cast<int>(MoveVector::DOWN);
			adjustmentFlag = true;
		}
	}
}

void Enemy::ThreeWayJudge2()
{
	if (nowMove != static_cast<int>(MoveVector::DOWN) && vReserveFlag == true && vectorZ < 0)
	{
		nowMove = static_cast<int>(MoveVector::UP);
		adjustmentFlag = true;
	}
	else if (nowMove != static_cast<int>(MoveVector::UP) && vReserveFlag == true && 0 < vectorZ)
	{
		nowMove = static_cast<int>(MoveVector::DOWN);
		adjustmentFlag = true;
	}
	else if (nowMove != static_cast<int>(MoveVector::LEFT) && vReserveFlag == false && vectorX >= 0)
	{
		nowMove = static_cast<int>(MoveVector::RIGHT);
		adjustmentFlag = true;
	}
	else if (nowMove == static_cast<int>(MoveVector::LEFT))
	{
		if (vectorZ <= 0)
		{
			nowMove = static_cast<int>(MoveVector::UP);
			adjustmentFlag = true;
		}
		else if (vectorZ > 0)
		{
			nowMove = static_cast<int>(MoveVector::DOWN);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::UP))
	{
		if (vectorX > 0)
		{
			nowMove = static_cast<int>(MoveVector::RIGHT);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::DOWN))
	{
		if (vectorX > 0)
		{
			nowMove = static_cast<int>(MoveVector::RIGHT);
			adjustmentFlag = true;
		}
	}
}

void Enemy::ThreeWayJudge3()
{
	if (nowMove != static_cast<int>(MoveVector::DOWN) && vReserveFlag == true && vectorZ < 0)
	{
		nowMove = static_cast<int>(MoveVector::UP);
		adjustmentFlag = true;
	}
	else if (nowMove != static_cast<int>(MoveVector::UP) && vReserveFlag == true && 0 < vectorZ)
	{
		nowMove = static_cast<int>(MoveVector::DOWN);
		adjustmentFlag = true;
	}
	else if (nowMove != static_cast<int>(MoveVector::RIGHT) && vReserveFlag == false && vectorX <= 0)
	{
		nowMove = static_cast<int>(MoveVector::LEFT);
		adjustmentFlag = true;
	}
	else if (nowMove == static_cast<int>(MoveVector::RIGHT))
	{
		if (vectorZ <= 0)
		{
			nowMove = static_cast<int>(MoveVector::UP);
			adjustmentFlag = true;
		}
		if (vectorZ > 0)
		{
			nowMove = static_cast<int>(MoveVector::DOWN);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::UP))
	{
		if (vectorX < 0)
		{
			nowMove = static_cast<int>(MoveVector::LEFT);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::DOWN))
	{
		if (vectorX < 0)
		{
			nowMove = static_cast<int>(MoveVector::LEFT);
			adjustmentFlag = true;
		}
	}
}

void Enemy::ThreeWayJudge4()
{
	if (nowMove != static_cast<int>(MoveVector::RIGHT) && vReserveFlag == false && vectorX < 0)
	{
		nowMove = static_cast<int>(MoveVector::LEFT);
		adjustmentFlag = true;
	}
	else if (nowMove != static_cast<int>(MoveVector::LEFT) && vReserveFlag == false && 0 < vectorX)
	{
		nowMove = static_cast<int>(MoveVector::RIGHT);
		adjustmentFlag = true;
	}
	else if (nowMove != static_cast<int>(MoveVector::DOWN) && vReserveFlag == true && vectorZ <= 0)
	{
		nowMove = static_cast<int>(MoveVector::UP);
		adjustmentFlag = true;
	}
	else if (nowMove == static_cast<int>(MoveVector::DOWN))
	{
		if (vectorX <= 0)
		{
			nowMove = static_cast<int>(MoveVector::LEFT);
			adjustmentFlag = true;
		}
		if (vectorX > 0)
		{
			nowMove = static_cast<int>(MoveVector::RIGHT);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::LEFT))
	{
		if (vectorZ < 0)
		{
			nowMove = static_cast<int>(MoveVector::UP);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::RIGHT))
	{
		if (vectorZ < 0)
		{
			nowMove = static_cast<int>(MoveVector::UP);
			adjustmentFlag = true;
		}
	}
}

void Enemy::FourWayJudge()
{
	if (nowMove == static_cast<int>(MoveVector::UP) && vectorZ > 0)
	{
		if (vectorX <= 0)
		{
			nowMove = static_cast<int>(MoveVector::LEFT);
			adjustmentFlag = true;
		}
		if (vectorX > 0)
		{
			nowMove = static_cast<int>(MoveVector::RIGHT);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::DOWN) && vectorZ < 0)
	{
		if (vectorX <= 0)
		{
			nowMove = static_cast<int>(MoveVector::LEFT);
			adjustmentFlag = true;
		}
		if (vectorX > 0)
		{
			nowMove = static_cast<int>(MoveVector::RIGHT);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::RIGHT) && vectorX < 0)
	{
		if (vectorZ <= 0)
		{
			nowMove = static_cast<int>(MoveVector::UP);
			adjustmentFlag = true;
		}
		if (vectorZ > 0)
		{
			nowMove = static_cast<int>(MoveVector::DOWN);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::LEFT) && vectorX > 0)
	{
		if (vectorZ <= 0)
		{
			nowMove = static_cast<int>(MoveVector::UP);
			adjustmentFlag = true;
		}
		if (vectorZ > 0)
		{
			nowMove = static_cast<int>(MoveVector::DOWN);
			adjustmentFlag = true;
		}
	}
}
