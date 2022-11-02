#pragma once
#include <DirectXMath.h>

class SoundVector
{
protected: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	void Initialize();//�ŏ��̏�����
	void Update();
public:
	static float DistanceSearch(float playerX, float playerZ, float enemyX, float enemyZ);
	static float VectorSearch(float playerX, float playerZ, float enemyX, float enemyZ);
};

