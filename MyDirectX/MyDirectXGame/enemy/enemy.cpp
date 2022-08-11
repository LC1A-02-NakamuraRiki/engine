#include "enemy.h"
#include "../collision/Collision.h"

void Enemy::Initialize()
{
	modelEnemy = Model::CreateFromObject("bom", false);
	objEnemy = Object3d::Create(modelEnemy);
	objEnemy->SetPosition(pos);
}

void Enemy::InitializeValue()
{
	pos = { -8.0f,0.0f,+56.0f };//プレイヤーの位置
	objEnemy->SetPosition(pos);
	nowMove = UP;
	adjustValueX = 0;
	adjustValueZ = 0;
	vReserveFlag = false;
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

	if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 2)
	{
		if (nowMove == UP)
		{
			nowMove = RIGHT;
		}
		if (nowMove == LEFT)
		{
			nowMove = DOWN;
		}
	}
	else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 3)
	{
		if (nowMove != LEFT && vReserveFlag == false && 0 < vectorX)
		{
			nowMove = RIGHT;
		}
		
		else if (nowMove != RIGHT && vReserveFlag == false && vectorX < 0)
		{
			nowMove = LEFT;
		}

		else if (nowMove != UP && vReserveFlag == true)
		{
			nowMove = DOWN;
		}
	}
	else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 4)
	{
		if (nowMove == RIGHT)
		{
			nowMove = DOWN;
		}
		if (nowMove == UP)
		{
			nowMove = LEFT;
		}
	}
	else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 5)
	{
		if (nowMove != DOWN && vReserveFlag == true && vectorZ < 0)
		{
			nowMove = UP;
		}
		else if (nowMove != UP && vReserveFlag == true && 0 < vectorZ)
		{
			nowMove = DOWN;
		}
		else if (nowMove != LEFT && vReserveFlag == false)
		{
			nowMove = RIGHT;
		}
	}
	else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 6)
	{
		if (nowMove != DOWN && vReserveFlag == true && vectorZ < 0)
		{
			nowMove = UP;
		}
		if (nowMove != UP && vReserveFlag == true && 0 < vectorZ)
		{
			nowMove = DOWN;
		}
		if (nowMove != LEFT && vReserveFlag == false && 0 < vectorX)
		{
			nowMove = RIGHT;
		}
		if (nowMove != RIGHT && vReserveFlag == false && vectorX < 0)
		{
			nowMove = LEFT;
		}

	}
	else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 7)
	{
		if (nowMove != DOWN && vReserveFlag == true && vectorZ < 0)
		{
			nowMove = UP;
		}
		else if (nowMove != UP && vReserveFlag == true && 0 < vectorZ)
		{
			nowMove = DOWN;
		}
		else if (nowMove != RIGHT && vReserveFlag == false)
		{
			nowMove = LEFT;
		}
	}
	else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 8)
	{
		if (nowMove == LEFT)
		{
			nowMove = UP;
		}
		if (nowMove == DOWN)
		{
			nowMove = RIGHT;
		}
	}
	else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 9)
	{
		if (nowMove != RIGHT && vReserveFlag == false && vectorX < 0)
		{
			nowMove = LEFT;
		}
		else if (nowMove != LEFT && vReserveFlag == false && 0 < vectorX)
		{
			nowMove = RIGHT;
		}
		else if (nowMove != DOWN && vReserveFlag == true)
		{
			nowMove = UP;
		}
	}
	else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 10)
	{
		if (nowMove == DOWN)
		{
			nowMove = LEFT;
		}
		if (nowMove == RIGHT)
		{
			nowMove = UP;
		}
	}
}

void Enemy::Move(MapChip* mapChip)
{
	if (mapChip->GetStopFlag() == false)
	{
		if (nowMove == DOWN)
		{
			pos.z += 0.4f;
			adjustValueZ = -8.0f;
		}
		else if (nowMove == UP)
		{
			pos.z -= 0.4f;
			adjustValueZ = 8.0f;
		}
		else if (nowMove == RIGHT)
		{
			pos.x += 0.4f;
			adjustValueX = -8.0f;
		}
		else if (nowMove == LEFT)
		{
			pos.x -= 0.4f;
			adjustValueX = 8.0;
		}
	}
	objEnemy->SetPosition(pos);
}

bool Enemy::catchCollision(Player* player)
{
	XMFLOAT3 playerPos = player->GetPos();
	return Collision::ChenkSphere2Sphere(playerPos, pos, 3.0f, 6.0f);
}
