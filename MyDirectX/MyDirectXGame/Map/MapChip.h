#pragma once
#include <DirectXMath.h>
#include "../3d/Object3d.h"
//#include "../Player/Player.h"
class MapChip
{
protected: // エイリアス
// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	void Initialize();
	void InitializeValue();
	void Update(XMFLOAT3 pos);
	int ArrayValue(float x, float y);
	void Draw();

	bool GetAllGetFlag() { return allGetFlag; }
private:

	Model* modelMapWall = nullptr;
	Object3d* objMapWall[15][15];
	Model* modelCrystal = nullptr;
	Object3d* objCrystal[9];
	XMFLOAT3 crystalPos[9] = { XMFLOAT3({ 1 * 16.0f - (15 * 16.0f / 2), 0.0f, 1 * 16.0f - (15 * 16.0f / 2)   }),
							 XMFLOAT3({ 7 * 16.0f - (15 * 16.0f / 2), 0.0f, 1 * 16.0f - (15 * 16.0f / 2)   }),
							 XMFLOAT3({ 13 * 16.0f - (15 * 16.0f / 2), 0.0f, 1 * 16.0f - (15 * 16.0f / 2)  }),
							 XMFLOAT3({ 1 * 16.0f - (15 * 16.0f / 2), 0.0f, 7 * 16.0f - (15 * 16.0f / 2)   }),
							 XMFLOAT3({ 7 * 16.0f - (15 * 16.0f / 2), 0.0f, 7 * 16.0f - (15 * 16.0f / 2)   }),
							 XMFLOAT3({ 13 * 16.0f - (15 * 16.0f / 2), 0.0f, 7 * 16.0f - (15 * 16.0f / 2)  }),
							 XMFLOAT3({ 1 * 16.0f - (15 * 16.0f / 2), 0.0f, 13 * 16.0f - (15 * 16.0f / 2)  }),
							 XMFLOAT3({ 7 * 16.0f - (15 * 16.0f / 2), 0.0f, 13 * 16.0f - (15 * 16.0f / 2)  }),
							 XMFLOAT3({ 13 * 16.0f - (15 * 16.0f / 2), 0.0f, 13 * 16.0f - (15 * 16.0f / 2) }),
	};
	;
	bool crystalGetFlag[9] = { false,false,false,false,false,false,false,false,false };
	int mapWall[15][15] = { { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
							{ 1,2,0,0,0,0,0,3,0,0,0,0,0,4,1 },
							{ 1,0,1,1,1,1,1,0,1,1,1,1,1,0,1 },
							{ 1,0,1,1,1,1,1,0,1,1,1,1,1,0,1 },
							{ 1,0,1,1,1,1,1,0,1,1,1,1,1,0,1 },
							{ 1,0,1,1,1,1,1,0,1,1,1,1,1,0,1 },
							{ 1,0,1,1,1,1,1,0,1,1,1,1,1,0,1 },
							{ 1,5,0,0,0,0,0,6,0,0,0,0,0,7,1 },
							{ 1,0,1,1,1,1,1,0,1,1,1,1,1,0,1 },
							{ 1,0,1,1,1,1,1,0,1,1,1,1,1,0,1 },
							{ 1,0,1,1,1,1,1,0,1,1,1,1,1,0,1 },
							{ 1,0,1,1,1,1,1,0,1,1,1,1,1,0,1 },
							{ 1,0,1,1,1,1,1,0,1,1,1,1,1,0,1 },
							{ 1,8,0,0,0,0,0,9,0,0,0,0,0,10,1 },
							{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};
	bool allGetFlag = false;
};