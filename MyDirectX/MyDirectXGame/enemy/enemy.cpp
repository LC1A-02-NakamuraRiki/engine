#include "enemy.h"

void Enemy::Initialize()
{
	modelEnemy = Model::CreateFromObject("bom", false);
	objEnemy = Object3d::Create(modelEnemy);
	objEnemy->SetPosition(pos);
}

void Enemy::Update(MapChip* mapChip)
{
	objEnemy->Update();
	AI(mapChip);
	Move();
}

void Enemy::Draw()
{
	objEnemy->Draw();
}

void Enemy::AI(MapChip* mapChip)
{
	if (mapChip->ArrayValue(pos.x, pos.z) == 2)
	{
		nowMove = RIGHT;
	}
	else if (mapChip->ArrayValue(pos.x, pos.z) == 3)
	{
		nowMove = RIGHT;
	}
	else if (mapChip->ArrayValue(pos.x, pos.z) == 4)
	{
		nowMove = DOWN;
	}
	else if (mapChip->ArrayValue(pos.x, pos.z) == 5)
	{
		nowMove = UP;
	}
	else if (mapChip->ArrayValue(pos.x, pos.z) == 6)
	{
		nowMove = UP;
	}
	else if (mapChip->ArrayValue(pos.x, pos.z) == 7)
	{
		nowMove = DOWN;
	}
	else if (mapChip->ArrayValue(pos.x, pos.z) == 8)
	{
		nowMove = UP;
	}
	else if (mapChip->ArrayValue(pos.x, pos.z) == 9)
	{
		nowMove = LEFT;
	}
	else if (mapChip->ArrayValue(pos.x, pos.z) == 10)
	{
		nowMove = LEFT;
	}
}

void Enemy::Move()
{
	if (nowMove == DOWN)
	{
		pos.z += 0.4f;
	}
	else if (nowMove == UP)
	{
		pos.z -= 0.4f;
	}
	else if (nowMove == RIGHT)
	{
		pos.x += 0.4f;
	}
	else if (nowMove == LEFT)
	{
		pos.x -= 0.4f;
	}
	objEnemy->SetPosition(pos);
}
