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
	modelEnemy = Model::CreateFromObject("gostFace", false);
	objEnemy = Object3d::Create(modelEnemy);
	objEnemy->SetPosition(pos);
	objEnemy->SetScale({ 0.35f,0.3f,0.35f });

	if (!Sprite::LoadTexture(4, L"Resources/enemyDot.png")) {
		assert(0);
		return;
	}
	spriteEnemyDot = Sprite::Create(4, miniMapPos);
	spriteEnemyAngle = Sprite::Create(6, miniMapPos);
}

void Enemy::InitializeValue()
{
	pos = { -4.0f,3.0f,-28.0f };//プレイヤーの位置
	objEnemy->SetPosition(pos);
	objEnemy->SetRotation({ 0, 270, 0 });
	nowMove = UP;
	adjustValueX = 0;
	adjustValueZ = 0;
	speed = 0.2f;
	vReserveFlag = false;
	miniMapPos = { 100 + (16.0f * 10),650 + (16.0f * 7) };
	maxAdjustmentTime = 40;

	wallHitFlag = false;
	adjustmentFlag = false;
	killTime = 0;
	startStopTime = 0;
}

void Enemy::InitializeValue2()
{
	pos = { 4.0f,3.0f,68.0f };//プレイヤーの位置
	objEnemy->SetPosition(pos);
	nowMove = LEFT;
	adjustValueX = 0;
	adjustValueZ = 0;
	speed = 0.16f;
	vReserveFlag = false;
	miniMapPos = { 100 + (16.0f * 9),650 + (16.0f * 19) };
	maxAdjustmentTime = 49;
	wallHitFlag = false;
	adjustmentFlag = false;
	killTime = 0;
	startStopTime = 0;
}

void Enemy::InitializeValue3()
{
	pos = { -76.0f,3.5f,-12.0f };//位置
	objEnemy->SetPosition(pos);
	nowMove = UP;
	adjustValueX = 0;
	adjustValueZ = 0;
	speed = 0.16f;
	vReserveFlag = false;
	miniMapPos = { 100 + (16.0f * 19),650 + (16.0f * 9) };
	maxAdjustmentTime = 49;
	wallHitFlag = false;
	adjustmentFlag = false;
	killTime = 0;
	startStopTime = 0;
}

void Enemy::Update(Player* player, MapChip* mapChip, XMFLOAT2 mapPos, XMFLOAT2 plusValue ,bool catchFlag1, bool catchFlag2)
{

	objEnemy->Update(pos,pos, pos,pos, 0, 1);
	AI(player, mapChip,plusValue);
	if (mapChip->GetGateOpenFlag() && !catchFlag1 && !catchFlag2)
	{
		startStopTime++;
		if(!CatchCollision(player) && startStopTime > 90)
		{
			Move(mapChip, mapPos);
		}
	}
}

void Enemy::Draw()
{
	objEnemy->Draw();
}

void Enemy::DrawSprite(MapChip* mapChip)
{
	if (mapChip->GetDisplayFlag() && spriteEnemyDot->GetPosition().x < 420 && spriteEnemyDot->GetPosition().x > 100
		&& spriteEnemyDot->GetPosition().y > 650 && spriteEnemyDot->GetPosition().y < 986)
	{
		spriteEnemyAngle->Draw(1.0f);
		spriteEnemyDot->Draw(1.0f);
	}
}

void Enemy::AI(Player* player,MapChip* mapChip, XMFLOAT2 plusValue)
{
	XMFLOAT3 playerPos = player->GetPos();

	float vectorX = playerPos.x + plusValue.x - pos.x;
	float vectorZ = playerPos.z + plusValue.y - pos.z;

	if ((vectorX * vectorX) < (vectorZ * vectorZ))
	{
		vReserveFlag = true;
	}
	else if ((vectorX * vectorX) >= (vectorZ * vectorZ))
	{
		vReserveFlag = false;
	}
	if (adjustmentFlag)
	{
		adjustmentTime++;
		if (adjustmentTime >= maxAdjustmentTime)
		{
			adjustmentTime = 0;
			adjustmentFlag = false;
		}
	}
	else if (!adjustmentFlag)
	{
		if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 2)
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
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 3)
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
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 4)
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
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 5)
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
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 6)
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
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 7)
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
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 8)
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
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 9)
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
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 10)
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
	if (mapChip->GetStopFlag() == false)
	{
		if (nowMove == DOWN)
		{
			spriteEnemyAngle->SetRotation(45);
			objEnemy->SetRotation({0, 270, 0});
			pos.z += speed;
			miniMapPos.y += speed * 2;
			adjustValueZ = -3.9f;
		}
		else if (nowMove == UP)
		{
			spriteEnemyAngle->SetRotation(-135);
			objEnemy->SetRotation({ 0, 90, 0 });
			pos.z -= speed;
			miniMapPos.y -= speed * 2;
			adjustValueZ = 3.9f;
		}
		else if (nowMove == RIGHT)
		{
			spriteEnemyAngle->SetRotation(135);
			objEnemy->SetRotation({ 0, 0, 0 });
			pos.x += speed;
			miniMapPos.x -= speed * 2;
			adjustValueX = -3.9f;
		}
		else if (nowMove == LEFT)
		{
			spriteEnemyAngle->SetRotation(-45);
			objEnemy->SetRotation({ 0, 180, 0 });
			pos.x -= speed;
			miniMapPos.x += speed * 2;
			adjustValueX = 3.9f;
		}
	}
	spriteEnemyDot->SetPosition({ miniMapPos.x + mapPos.x , miniMapPos.y + mapPos.y });
	spriteEnemyAngle->SetPosition({ miniMapPos.x + mapPos.x + 8, miniMapPos.y + mapPos.y + 8 });
	objEnemy->SetPosition(pos);
}

bool Enemy::CatchCollision(Player* player)
{
	XMFLOAT3 playerPos = player->GetPos();
	return Collision::ChenkSphere2Sphere(playerPos, pos, 2.5f, 3.0f);
}

bool Enemy::DeathAnimation(Player* player)
{
	if (CatchCollision(player))
	{
		float aX = player->GetPos().x - pos.x;
		float aZ = player->GetPos().z - pos.z;
		float aXZ = XMConvertToDegrees(float(atan2(aX, aZ)));
		
		if (player->GetViewAngle() < aXZ + 30 && player->GetViewAngle() > aXZ - 30)
		{
			player->SetViewAngleY2(aXZ);
			player->SetViewAngleX2(10);
			killTime++;
		}
		else if (player->GetViewAngle() < aXZ)
		{
			player->SetViewAngleY(15);
		}
		else if (player->GetAngle() > aXZ)
		{
			player->SetViewAngleY(-15);
		}

		if (killTime > 60)
		{
			killTime = 0;
			return true;
		}
	}
	return false;
}
