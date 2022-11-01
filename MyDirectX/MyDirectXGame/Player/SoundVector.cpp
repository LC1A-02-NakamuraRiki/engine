#include "SoundVector.h"
using namespace DirectX;
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
	float axzDistanse = float(sqrt(aXZ));
	return axzDistanse;
}

float SoundVector::VectorSearch(float playerX, float playerZ, float enemyX, float enemyZ)
{
	float aX = enemyX - playerX;
	float aZ = enemyZ - playerZ;
	return XMConvertToDegrees(float(atan2(aX, aZ)));
}
