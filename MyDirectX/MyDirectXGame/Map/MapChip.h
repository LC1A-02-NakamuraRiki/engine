#pragma once
#include <DirectXMath.h>
#include "../3d/Object3d.h"
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
	void Update();
	int ArrayValue(float x, float y);
	void Draw();
private:

	Model* modelMapWall = nullptr;
	Object3d* objMapWall[15][13];
	int mapWall[15][13] = { { 1,1,1,1,1,1,1,1,1,1,1,1,1 },							
							{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
							{ 1,0,1,0,1,0,1,0,1,0,1,0,1 },
							{ 1,0,1,0,1,0,1,0,1,0,1,0,1 },
							{ 1,0,1,0,1,0,1,0,1,0,1,0,1 },							
							{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
							{ 1,0,1,0,1,0,1,0,1,0,1,0,1 },
							{ 1,0,1,0,1,0,1,0,1,0,1,0,1 },
							{ 1,0,1,0,1,0,1,0,1,0,1,0,1 },							
							{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
							{ 1,0,1,0,1,0,1,0,1,0,1,0,1 },
							{ 1,0,1,0,1,0,1,0,1,0,1,0,1 },
							{ 1,0,1,0,1,0,1,0,1,0,1,0,1 },						
							{ 1,0,0,0,0,0,0,0,0,0,0,0,1 },
							{ 1,1,1,1,1,1,1,1,1,1,1,1,1 }
	};
};