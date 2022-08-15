#include "enemy.h"
#include "../collision/Collision.h"

void Enemy::Initialize()
{
	modelEnemy = Model::CreateFromObject("Human", false);
	objEnemy = Object3d::Create(modelEnemy);
	objEnemy->SetPosition(pos);

	if (!Sprite::LoadTexture(4, L"Resources/enemyDot.png")) {
		assert(0);
		return;
	}
	spriteEnemyDot = Sprite::Create(4, miniMapPos);
	spriteEnemyAngle = Sprite::Create(6, miniMapPos);
}

void Enemy::InitializeValue()
{
	pos = { -8.0f,3.0f,+56.0f };//プレイヤーの位置
	objEnemy->SetPosition(pos);
	nowMove = UP;
	adjustValueX = 0;
	adjustValueZ = 0;
	vReserveFlag = false;
	miniMapPos = { 100 + (16.0f * 10),650 + (16.0f * 14) };
}

void Enemy::Update(Player* player,MapChip* mapChip)
{
	objEnemy->Update();
	AI(player,mapChip);
	Move(mapChip);
}

void Enemy::Draw()
{
	objEnemy->Draw();
}

void Enemy::DrawSprite(MapChip* mapChip)
{
	if (mapChip->GetDisplayFlag())
	{
		spriteEnemyAngle->Draw();
		spriteEnemyDot->Draw();
	}
}

void Enemy::AI(Player* player,MapChip* mapChip)
{
	XMFLOAT3 playerPos = player->GetPos();

	float vectorX  = playerPos.x - pos.x;
	float vectorZ = playerPos.z - pos.z;

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
		if (adjustmentTime > 40)
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

void Enemy::Move(MapChip* mapChip)
{
	if (mapChip->GetStopFlag() == false)
	{
		if (nowMove == DOWN)
		{
			spriteEnemyAngle->SetRotation(45);
			pos.z += 0.4f;
			miniMapPos.y += 0.4f;
			adjustValueZ = -8.0f;
		}
		else if (nowMove == UP)
		{
			spriteEnemyAngle->SetRotation(-135);
			pos.z -= 0.4f;
			miniMapPos.y -= 0.4f;
			adjustValueZ = 8.0f;
		}
		else if (nowMove == RIGHT)
		{
			spriteEnemyAngle->SetRotation(135);
			pos.x += 0.4f;
			miniMapPos.x -= 0.4f;
			adjustValueX = -8.0f;
		}
		else if (nowMove == LEFT)
		{
			spriteEnemyAngle->SetRotation(-45);
			pos.x -= 0.4f;
			miniMapPos.x += 0.4f;
			adjustValueX = 8.0;
		}
	}
	spriteEnemyDot->SetPosition(miniMapPos);
	spriteEnemyAngle->SetPosition({ miniMapPos.x + 8, miniMapPos.y + 8 });
	objEnemy->SetPosition(pos);
}

bool Enemy::catchCollision(Player* player)
{
	XMFLOAT3 playerPos = player->GetPos();
	return Collision::ChenkSphere2Sphere(playerPos, pos, 3.0f, 6.0f);
}
