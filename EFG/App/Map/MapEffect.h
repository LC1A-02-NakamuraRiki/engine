#pragma once
#include <DirectXMath.h>

class MapEffect
{
private: // �G�C���A�X
// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	static bool LightAction(bool lightActionFlag, float lightCount);

	//�h�A�J��
	static float DoorOpen(float MapEffect::DoorOpen(XMFLOAT3 pos, bool gateOpenFlag, float doorAngle);
};

