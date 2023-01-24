#include "enemy.h"
#include "Collision.h"
#include "Input.h"

using namespace DirectX;

Enemy::~Enemy()
{
	safe_delete(spriteEnemyDot);
	safe_delete(spriteEnemyAngle);
	safe_delete(modelEnemy);
	safe_delete(objEnemy);
}

void Enemy::Initialize()
{
	//敵初期化
	modelEnemy = Model::CreateFromObject("gostFace", false);//モデル初期化
	objEnemy = Object3d::Create(modelEnemy);//object初期化
	objEnemy->SetPosition(pos);//位置初期化
	objEnemy->SetScale({ 0.35f,0.3f,0.35f });//大きさ初期化

	//画像読み込み
	if (!Sprite::LoadTexture(4, L"Resources/enemyDot.png")) {
		assert(0);
		return;
	}

	//スプライト読み込み
	spriteEnemyDot = Sprite::Create(4, miniMapPos);
	spriteEnemyAngle = Sprite::Create(6, miniMapPos);
}

//鬼ごとの初期化
void Enemy::InitializeValue()
{
	//鬼ごとの初期化
	pos = { -4.0f,3.0f,-28.0f };//位置
	objEnemy->SetPosition(pos);//位置セット
	angle = 270;//向き
	objEnemy->SetRotation({ 0, angle, 0 });//向きセット
	nowMove = UP;//進む向き
	adjustValueX = 0;//調整値X
	adjustValueZ = 0;//調整値Z
	speed = 0.2f;//スピード
	vReserveFlag = false;//優先度
	miniMapPos = { 100 + (16.0f * 10),650 + (16.0f * 7) };//ミニマップ位置
	maxAdjustmentTime = 40;//調整タイム

	wallHitFlag = false;//先読みの座標が壁に当たっているか
	adjustmentFlag = false;//位置調整フラグ
	killTime = 0;//殴りモーションの時間
	startStopTime = 0;//スタートまでの硬直時間
}

void Enemy::InitializeValue2()
{
	//鬼ごとの初期化
	pos = { 4.0f,3.0f,68.0f };//位置
	objEnemy->SetPosition(pos);//位置セット
	nowMove = LEFT;//進む向き
	adjustValueX = 0;//調整値X
	adjustValueZ = 0;//調整値Z
	speed = 0.16f;//スピード
	vReserveFlag = false;//優先度
	miniMapPos = { 100 + (16.0f * 9),650 + (16.0f * 19) };//ミニマップ位置
	maxAdjustmentTime = 49;//調整タイム
	wallHitFlag = false;//先読みの座標が壁に当たっているか
	adjustmentFlag = false;//位置調整フラグ
	killTime = 0;//殴りモーションの時間
	startStopTime = 0;//スタートまでの硬直時間
}

void Enemy::InitializeValue3()
{
	//鬼ごとの初期化
	pos = { -76.0f,3.0f,-12.0f };//位置
	objEnemy->SetPosition(pos);//位置セット
	nowMove = UP;//進む向き
	adjustValueX = 0;//調整値X
	adjustValueZ = 0;//調整値Z
	speed = 0.16f;//スピード
	vReserveFlag = false;//優先度
	miniMapPos = { 100 + (16.0f * 19),650 + (16.0f * 9) };//ミニマップ位置
	maxAdjustmentTime = 49;//調整タイム
	wallHitFlag = false;//先読みの座標が壁に当たっているか
	adjustmentFlag = false;//位置調整フラグ
	killTime = 0;//殴りモーションの時間
	startStopTime = 0;//スタートまでの硬直時間
}

void Enemy::Update(Player* player, MapChip* mapChip, XMFLOAT2 mapPos, XMFLOAT2 plusValue ,bool catchFlag1, bool catchFlag2)
{	
	//アップデート
	objEnemy->Update(pos,pos, pos,pos, 0, 1);
	//探索
	AI(player, mapChip,plusValue);
	if (mapChip->GetGateOpenFlag() && !catchFlag1 && !catchFlag2)//スタートしているか、捕まっていないか
	{
		startStopTime++;//スタートまでの硬直タイム
		if(!CatchCollision(player) && startStopTime > 90)//スタートしたか
		{
			//動き
			Move(mapChip, mapPos);
		}
	}
}

void Enemy::Draw()
{
	objEnemy->Draw();//エネミー描画
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
}

void Enemy::AI(Player* player,MapChip* mapChip, XMFLOAT2 plusValue)
{
	XMFLOAT3 playerPos = player->GetPos();

	//距離調べ
	float vectorX = playerPos.x + plusValue.x - pos.x;
	float vectorZ = playerPos.z + plusValue.y - pos.z;
	
	//優先度調べ
	if ((vectorX * vectorX) < (vectorZ * vectorZ))
	{
		vReserveFlag = true;
	}
	else if ((vectorX * vectorX) >= (vectorZ * vectorZ))
	{
		vReserveFlag = false;
	}

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
		if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 2)//上左角
		{
			if (nowMove == UP)
			{
				nowMove = RIGHT;
				adjustmentFlag = true;
			}
			if (nowMove == LEFT)
			{
				nowMove = DOWN;
				adjustmentFlag = true;
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 3)//上中心
		{
			if (nowMove != LEFT && vReserveFlag == false && 0 < vectorX)
			{
				nowMove = RIGHT;
				adjustmentFlag = true;
			}
			else if (nowMove != RIGHT && vReserveFlag == false && vectorX < 0)
			{
				nowMove = LEFT;
				adjustmentFlag = true;
			}
			else if (nowMove != UP && vReserveFlag == true && vectorZ >= 0)
			{
				nowMove = DOWN;
				adjustmentFlag = true;
			}
			else if (nowMove == UP)
			{
				if (vectorX <= 0)
				{
					nowMove = LEFT;
					adjustmentFlag = true;
				}
				if (vectorX > 0)
				{
					nowMove = RIGHT;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == LEFT)
			{
				if (vectorZ > 0)
				{
					nowMove = DOWN;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == RIGHT)
			{
				if (vectorZ > 0)
				{
					nowMove = DOWN;
					adjustmentFlag = true;
				}
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 4)//上右角
		{
			if (nowMove == RIGHT)
			{
				nowMove = DOWN;
				adjustmentFlag = true;
			}
			if (nowMove == UP)
			{
				nowMove = LEFT;
				adjustmentFlag = true;
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 5)//中央左
		{
			if (nowMove != DOWN && vReserveFlag == true && vectorZ < 0)
			{
				nowMove = UP;
				adjustmentFlag = true;
			}
			else if (nowMove != UP && vReserveFlag == true && 0 < vectorZ)
			{
				nowMove = DOWN;
				adjustmentFlag = true;
			}
			else if (nowMove != LEFT && vReserveFlag == false && vectorX >= 0)
			{
				nowMove = RIGHT;
				adjustmentFlag = true;
			}
			else if(nowMove == LEFT)
			{
				if (vectorZ <= 0)
				{
					nowMove = UP;
					adjustmentFlag = true;
				}
				else if (vectorZ > 0)
				{
					nowMove = DOWN;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == UP)
			{
				if (vectorX > 0)
				{
					nowMove = RIGHT;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == DOWN)
			{
				if (vectorX > 0)
				{
					nowMove = RIGHT;
					adjustmentFlag = true;
				}
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 6)//中央
		{
			if (nowMove == UP && vectorZ > 0)
			{
				if (vectorX <= 0)
				{
					nowMove = LEFT;
					adjustmentFlag = true;
				}
				if (vectorX > 0)
				{
					nowMove = RIGHT;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == DOWN && vectorZ < 0)
			{
				if (vectorX <= 0)
				{
					nowMove = LEFT;
					adjustmentFlag = true;
				}
				if (vectorX > 0)
				{
					nowMove = RIGHT;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == RIGHT && vectorX < 0)
			{
				if (vectorZ <= 0)
				{
					nowMove = UP;
					adjustmentFlag = true;
				}
				if (vectorZ > 0)
				{
					nowMove = DOWN;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == LEFT && vectorX> 0)
			{
				if (vectorZ <= 0)
				{
					nowMove = UP;
					adjustmentFlag = true;
				}
				if (vectorZ > 0)
				{
					nowMove = DOWN;
					adjustmentFlag = true;
				}
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 7)//中央右
		{
		if (nowMove != DOWN && vReserveFlag == true && vectorZ < 0)
		{
			nowMove = UP;
			adjustmentFlag = true;
		}
		else if (nowMove != UP && vReserveFlag == true && 0 < vectorZ)
		{
			nowMove = DOWN;
			adjustmentFlag = true;
		}
		else if (nowMove != RIGHT && vReserveFlag == false && vectorX <= 0)
		{
			nowMove = LEFT;
			adjustmentFlag = true;
		}
		else if (nowMove == RIGHT)
			{
				if (vectorZ <= 0)
				{
					nowMove = UP;
					adjustmentFlag = true;
				}
				if (vectorZ > 0)
				{
					nowMove = DOWN;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == UP)
			{
				if (vectorX < 0)
				{
					nowMove = LEFT;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == DOWN)
			{
				if (vectorX < 0)
				{
					nowMove = LEFT;
					adjustmentFlag = true;
				}
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 8)//下左角
		{
			if (nowMove == LEFT)
			{
				nowMove = UP;
				adjustmentFlag = true;
			}
			if (nowMove == DOWN)
			{
				nowMove = RIGHT;
				adjustmentFlag = true;
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 9)//下中央
		{

		if (nowMove != RIGHT && vReserveFlag == false && vectorX < 0)
		{
			nowMove = LEFT;
			adjustmentFlag = true;
		}
		else if (nowMove != LEFT && vReserveFlag == false && 0 < vectorX)
		{
			nowMove = RIGHT;
			adjustmentFlag = true;
		}
		else if (nowMove != DOWN && vReserveFlag == true && vectorZ <= 0)
		{
			nowMove = UP;
			adjustmentFlag = true;
		}
		else if (nowMove == DOWN)
			{
				if (vectorX <= 0)
				{
					nowMove = LEFT;
					adjustmentFlag = true;
				}
				if (vectorX > 0)
				{
					nowMove = RIGHT;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == LEFT)
			{
				if (vectorZ < 0)
				{
					nowMove = UP;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == RIGHT)
			{
				if (vectorZ < 0)
				{
					nowMove = UP;
					adjustmentFlag = true;
				}
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 10)//下右角
		{
			if (nowMove == DOWN)
			{
				nowMove = LEFT;
				adjustmentFlag = true;
			}
			if (nowMove == RIGHT)
			{
				nowMove = UP;
				adjustmentFlag = true;
			}
		}
	}
}

void Enemy::Move(MapChip* mapChip, XMFLOAT2 mapPos)
{
	
	if (mapChip->GetStopFlag() == false)//STOP発動してるか
	{
		if (nowMove == DOWN)//下に移動
		{
			spriteEnemyAngle->SetRotation(45);//角度をセット
			objEnemy->SetRotation({0, 270, 0});//角度をセット
			angle = 270;//角度の値をセット
			pos.z += speed;//移動スピード
			miniMapPos.y += speed * 2;//ミニマップの移動
			adjustValueZ = -3.9f;//調整値セット
		}
		else if (nowMove == UP)//上に移動
		{
			spriteEnemyAngle->SetRotation(-135);//角度をセット
			objEnemy->SetRotation({ 0, 90, 0 });//角度をセット
			angle = 90;//角度の値をセット
			pos.z -= speed;//移動スピード
			miniMapPos.y -= speed * 2;//ミニマップの移動
			adjustValueZ = 3.9f;//調整値セット
		}
		else if (nowMove == RIGHT)//右に移動
		{
			spriteEnemyAngle->SetRotation(135);//角度をセット
			objEnemy->SetRotation({ 0, 0, 0 });//角度をセット
			angle = 0;//角度の値をセット
			pos.x += speed;//移動スピード
			miniMapPos.x -= speed * 2;//ミニマップの移動
			adjustValueX = -3.9f;//調整値セット
		}
		else if (nowMove == LEFT)//左に移動
		{
			spriteEnemyAngle->SetRotation(-45);//角度をセット
			objEnemy->SetRotation({ 0, 180, 0 });//角度をセット
			angle = 180;//角度の値をセット
			pos.x -= speed;//移動スピード
			miniMapPos.x += speed * 2;//ミニマップの移動
			adjustValueX = 3.9f;//調整値セット
		}
	}

	//obj等に影響
	spriteEnemyDot->SetPosition({ miniMapPos.x + mapPos.x , miniMapPos.y + mapPos.y });//位置セット
	spriteEnemyAngle->SetPosition({ miniMapPos.x + mapPos.x + 8, miniMapPos.y + mapPos.y + 8 });//位置セット
	objEnemy->SetPosition(pos);//位置セット
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

		if (killTime > 60)//モーション終わったか
		{
			killTime = 0;
			return true;
		}
	}
	return false;
}
