#include "SoundVector.h"

void SoundVector::Initialize()
{

}

void SoundVector::Update()
{

}

float SoundVector::DistanceSearch(float playerX, float playerZ, float enemyX, float enemyZ)
{
	float aX = enemyX - playerX;
	float aZ = enemyZ - playerZ;
	float aXZ = aX * aX + aZ * aZ;
	float axzDistanse = sqrt(aXZ);
	return axzDistanse;
}

float SoundVector::VectorSearch(float playerX, float playerZ, float enemyX, float enemyZ)
{
	float aX = enemyX - playerX;
	float aZ = enemyZ - playerZ;
	XMConvertToDegrees(atan2(aX, aZ));
}
