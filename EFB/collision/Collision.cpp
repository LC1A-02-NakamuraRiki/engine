#include "Collision.h"

using namespace DirectX;

bool Collision::ChenkSphere2Sphere(XMFLOAT3 pos1, XMFLOAT3 pos2, float r1, float r2)
{
	float ax = (pos2.x - pos1.x) * (pos2.x - pos1.x);
	float ay = (pos2.y - pos1.y) * (pos2.y - pos1.y);
	float az = (pos2.z - pos1.z) * (pos2.z - pos1.z);
	float ar = (r1 + r2) * (r1 + r2);
	if (ax + ay + az <= ar)
	{
		return true;
	}
	else
	{
		return false;
	}
}