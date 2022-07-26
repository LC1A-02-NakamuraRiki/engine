#include "enemy.h"

void Enemy::Initialize()
{
	modelEnemy = Model::CreateFromObject("bom", false);
	objEnemy = Object3d::Create(modelEnemy);
	objEnemy->SetPosition(XMFLOAT3({ 0, 80, 0 }));
}

void Enemy::Update(MapChip* mapChip)
{
	objEnemy->Update();
}

void Enemy::Draw()
{
	objEnemy->Draw();
}

void Enemy::Move(MapChip* mapChip)
{
}
