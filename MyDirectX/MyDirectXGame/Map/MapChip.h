#pragma once
#include <DirectXMath.h>
#include "../3d/Object3d.h"
#include "../2d/Sprite.h"
#include"../LoadCSV.h"

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
	void Initialize();//最初の初期化
	void InitializeValue();//タイトル時の初期化
	void MapCreate();
	void Update(XMFLOAT3 pos);//アップデート
	int ArrayValue(float x, float y);//座標からマップチップ配列の算出
	void Draw();
	void DrawSprite();
	void TimeStop();
	void EnemyDisplay();
	bool GetAllGetFlag() { return allGetFlag; }
	bool GetStopFlag() { return stopFlag; }
	bool GetDisplayFlag() { return displayFlag; }
private:

	Model* modelMapWall = nullptr;
	Object3d* objMapWall[21][21];
	Model*  modelCeiling = nullptr;
	Object3d* objCeiling[21][21];
	Model* modelCrystal = nullptr;
	Model* modelItemCrystal = nullptr;
	Object3d* objCrystal[9];
	XMFLOAT3 crystalPos[9] = {XMFLOAT3({ 1 * 16.0f -  (21 * 16.0f / 2), 0.0f, 1 * 16.0f -  (21 * 16.0f / 2)   }),
							  XMFLOAT3({ 10 * 16.0f -  (21 * 16.0f / 2), 0.0f, 1 * 16.0f -  (21 * 16.0f / 2)   }),
							  XMFLOAT3({ 19 * 16.0f - (21 * 16.0f / 2), 0.0f, 1 * 16.0f -  (21 * 16.0f / 2)  }),
							  XMFLOAT3({ 1 * 16.0f -  (21 * 16.0f / 2), 0.0f, 10 * 16.0f -  (21 * 16.0f / 2)   }),
							  XMFLOAT3({ 10 * 16.0f -  (21 * 16.0f / 2), 0.0f, 16 * 16.0f -  (21 * 16.0f / 2)   }),
							  XMFLOAT3({ 19 * 16.0f - (21 * 16.0f / 2), 0.0f, 10 * 16.0f -  (21 * 16.0f / 2)  }),
							  XMFLOAT3({ 1 * 16.0f -  (21 * 16.0f / 2), 0.0f, 19 * 16.0f - (21 * 16.0f / 2)  }),
							  XMFLOAT3({ 10 * 16.0f -  (21 * 16.0f / 2), 0.0f, 19 * 16.0f - (21 * 16.0f / 2)  }),
							  XMFLOAT3({ 19 * 16.0f - (21 * 16.0f / 2), 0.0f, 19 * 16.0f - (21 * 16.0f / 2) }),
	};
	;
	XMFLOAT2 mapCrystalPos[9] = { {100 + (16.0f * 19),650 + (16.0f * 1)},
								  {100 + (16.0f * 10),650 + (16.0f * 1)},
								  {100 + (16.0f * 1),650 + (16.0f * 1)},
								  {100 + (16.0f * 19),650 + (16.0f * 10)},
								  {100 + (16.0f * 10),650 + (16.0f * 16)},
								  {100 + (16.0f * 1),650 + (16.0f * 10)},
								  {100 + (16.0f * 19),650 + (16.0f * 19)},
								  {100 + (16.0f * 10),650 + (16.0f * 19)},
								  {100 + (16.0f * 1),650 + (16.0f * 19)} };

	bool crystalGetFlag[9] = { false,false,false,false,false,false,false,false,false };//クリスタル取ったか
	int MapValue = 21;
	int MapValueX = 15;
	int MapValueZ = 15;
	/*int mapWall[15][15] = { 
		{ 1,1,1,1,1,1,1,1,1 },
		{ 1,2,0,0,3,0,0,4,1 },
		{ 1,0,1,1,0,1,1,0,1 },
		{ 1,0,1,1,0,1,1,0,1 },
		{ 1,5,0,0,6,0,0,7,1 },
		{ 1,0,1,1,0,1,1,0,1 },
		{ 1,0,1,1,0,1,1,0,1 },
		{ 1,8,0,0,9,0,0,10,1 },
		{ 1,1,1,1,1,1,1,1,1 }
	};*/

	int mapWall[21][21] = {
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
	};

	int mapWallLeftUp[7][7] = {
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0 },
	};
	int mapWallLeftCenter[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallLeftDown[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallCenterUp[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallCenterCenter[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallCenterDown[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallRightUp[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallRightCenter[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallRightDown[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};

	int mapWallLeftUp1[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallLeftCenter1[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallLeftDown1[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallCenterUp1[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallCenterCenter1[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallCenterDown1[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallRightUp1[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallRightCenter1[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};
	int mapWallRightDown1[7][7] = {
		{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,0 },

	};

	bool allGetFlag = false;//クリスタル全部とれたか

	int stopTime = 0;
	bool stopFlag = false;

	int displayTime = 0;
	bool displayFlag = false;

	Sprite* spriteMapWall[21][21];
	Sprite* spriteMapBack = nullptr;

	Sprite* spriteCrystal[9] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
	Sprite* spriteNumber[9] = { nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr };
	int number = 9;
};