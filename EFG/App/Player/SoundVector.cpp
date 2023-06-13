#include "SoundVector.h"
using namespace DirectX;

bool SoundVector::DistanceSearch(float playerX, float playerZ, float enemyX, float enemyZ)
{
	//�����v�Z
	float aX = enemyX - playerX;
	float aZ = enemyZ - playerZ;
	float aXZ = aX * aX + aZ * aZ;
	float axzDistanse = float(sqrt(aXZ));
	if (axzDistanse < 32.0f)
	{
		return true;
	}
	return false;
}

float SoundVector::VectorSearch(float playerX, float playerZ, float enemyX, float enemyZ)
{
	//�p�x�v�Z
	float aX = enemyX - playerX;
	float aZ = enemyZ - playerZ;
	return XMConvertToDegrees(float(atan2(aX, aZ)));
}
