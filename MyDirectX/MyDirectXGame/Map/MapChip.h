#pragma once
#include <DirectXMath.h>
#include "Object3d.h"
#include "Sprite.h"
#include"LoadCSV.h"
#include "SafeDelete.h"
#include <memory>

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
	~MapChip();
	void Initialize();//最初の初期化
	void InitializeValue();//タイトル時の初期化
	void MapCreate();//マップ作製
	void MapMove(XMFLOAT2 mapPos);//ミニマップ移動
	void Update(XMFLOAT3 pos, XMFLOAT2 mapPos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3);//アップデート
	int ArrayValue(float x, float y);//座標からマップチップ配列の算出
	void Draw();//描画
	void DrawSprite(XMFLOAT3 pos);//スプライト描画
	void TimeStop();//時間停止
	void EnemyDisplay();//敵スポット
	
	//Getter
	int GetArrayValue(int x, int z) { return mapWall[z][x]; }
	int GetPlayerArrayValue(int x, int z) { return mapPlayer[x][z]; }
	bool GetAllGetFlag() { return allGetFlag; }
	bool GetStopFlag() { return stopFlag; }
	bool GetDisplayFlag() { return displayFlag; }
	bool GetCrystalGetFlag(int no) { return crystalGetFlag[no]; }
	bool GetGateOpenFlag() { return gateOpenFlag; }

	bool LightAction();//ライト点滅
	bool SetLightAction(bool actionFlag) {return this->lightAction = actionFlag;}//フラグセット
private:

	std::unique_ptr<Model> modelMapWall;

	std::unique_ptr<Object3d> objMapWall[21][21];
	std::unique_ptr<Model> modelCeiling;
	std::unique_ptr<Model> modelFlat;
	std::unique_ptr<Object3d> objCeiling[21][21];
	std::unique_ptr<Model> modelFloor;
	std::unique_ptr<Object3d> objFloor[21][21];
	std::unique_ptr<Model> modelCrystal;
	std::unique_ptr<Model> modelItemCrystal;
	std::unique_ptr<Object3d> objCrystal[11];

	std::unique_ptr<Sprite> spriteDoorOpen;
	std::unique_ptr<Model> modelDoor[4];
	float doorAngle[4] = {90, 270,90,270};
	std::unique_ptr<Object3d> objMapDoor[4];
	bool gateOpenFlag = false;//ゲート空いたか
	float wallSize = 8;//壁の大きさ
	XMFLOAT3 crystalPos[11] = {XMFLOAT3({ 1 * wallSize - (21 * wallSize / 2),  1.0f, 1 * wallSize - (21 * wallSize / 2)   }),
							  XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2), 1.0f, 1 * wallSize - (21 * wallSize / 2)   }),
							  XMFLOAT3({ 19 * wallSize - (21 * wallSize / 2), 1.0f, 1 * wallSize - (21 * wallSize / 2)  }),
							  XMFLOAT3({ 1 * wallSize - (21 * wallSize / 2),  1.0f, 10 * wallSize - (21 * wallSize / 2)   }),
							  XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2), 1.0f, 16 * wallSize - (21 * wallSize / 2)   }),
							  XMFLOAT3({ 19 * wallSize - (21 * wallSize / 2), 1.0f, 10 * wallSize - (21 * wallSize / 2)  }),
							  XMFLOAT3({ 1 * wallSize - (21 * wallSize / 2),  1.0f, 19 * wallSize - (21 * wallSize / 2)  }),
							  XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2), 1.0f, 19 * wallSize - (21 * wallSize / 2)  }),
							  XMFLOAT3({ 19 * wallSize - (21 *  wallSize / 2),1.0f, 19 * wallSize - (21 *  wallSize / 2) }),
							  XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2),1.0f, 7 * wallSize - (21 * wallSize / 2) }),
							  XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2),1.0f, 13 * wallSize - (21 * wallSize / 2) })	
	};
	;
	XMFLOAT2 mapCrystalPos[11] = { {100 + (16.0f * 19),650 + (16.0f * 1)},
								  {100 + (16.0f * 10),650 + (16.0f * 1)},
								  {100 + (16.0f * 1),650 + (16.0f * 1)},
								  {100 + (16.0f * 19),650 + (16.0f * 10)},
								  {100 + (16.0f * 10),650 + (16.0f * 16)},
								  {100 + (16.0f * 1),650 + (16.0f * 10)},
								  {100 + (16.0f * 19),650 + (16.0f * 19)},
								  {100 + (16.0f * 10),650 + (16.0f * 19)},
								  {100 + (16.0f * 1),650 + (16.0f * 19)},
								  {100 + (16.0f * 10),650 + (16.0f * 7)},
								  {100 + (16.0f * 10),650 + (16.0f * 13)}, };

	bool crystalGetFlag[11] = { false,false,false,false,false,false,false,false,false,false,false };//クリスタル取ったか
	int MapValue = 21;
	int MapValueX = 15;
	int MapValueZ = 15;
	
	//マップ情報
	int mapWall[21][21] = {};
	//プレイヤーの位置座標化
	int mapPlayer[21][21] = {};

	//ランダムのためのマップ1
	int mapWallLeftUp[7][7] = {};
	int mapWallLeftCenter[7][7] = {};
	int mapWallLeftDown[7][7] = {};
	int mapWallCenterUp[7][7] = {};
	int mapWallCenterCenter[7][7] = {};
	int mapWallCenterDown[7][7] = {};
	int mapWallRightUp[7][7] = {};
	int mapWallRightCenter[7][7] = {};
	int mapWallRightDown[7][7] = {};

	//ランダムのためのマップ2
	int mapWallLeftUp1[7][7] = {};
	int mapWallLeftCenter1[7][7] = {};
	int mapWallLeftDown1[7][7] = {};
	int mapWallCenterUp1[7][7] = {};
	int mapWallCenterCenter1[7][7] = {};
	int mapWallCenterDown1[7][7] = {};
	int mapWallRightUp1[7][7] = {};
	int mapWallRightCenter1[7][7] = {};
	int mapWallRightDown1[7][7] = {};

	bool allGetFlag = false;//クリスタル全部とれたか

	int stopTime = 0;//ストップタイム
	bool stopFlag = false;//ストップフラグ

	int displayTime = 0;//スポットタイム
	bool displayFlag = false;//スポットフラグ

	std::unique_ptr<Sprite> spriteMapWall[21][21];
	std::unique_ptr<Sprite> spriteMapBack;
	std::unique_ptr<Sprite> spriteMapFrame;
					
	std::unique_ptr<Sprite> spriteCrystal[11];
	std::unique_ptr<Sprite> spriteNumberNum1[10];
	std::unique_ptr<Sprite> spriteNumberNum10[10];

	std::unique_ptr<Sprite> spriteEnemyStop;
	XMFLOAT2 stopFontSize = { 1200.0f * 10, 200.0f * 10 };
	int stopSprieteTime = 0;//時間
	float stopAlpha = 1.0f;//アルファ値

	std::unique_ptr<Sprite> spriteEnemySpot;
	XMFLOAT2 spotFontSize = { 1200.0f * 10, 200.0f * 10 };
	int spotSprieteTime = 0;//時間
	float spotAlpha = 1.0f;//アルファ値
	
	std::unique_ptr<Sprite> spriteSpotEffect;
	int number = 11;//数字

	std::unique_ptr<Model> modelPictureFrame;
	std::unique_ptr<Object3d> objPictureFrame1[21][21];
	std::unique_ptr<Object3d> objPictureFrame2[21][21];
	std::unique_ptr<Object3d> objPictureFrame3[21][21];
	std::unique_ptr<Object3d> objPictureFrame4[21][21];

	std::unique_ptr<Model> modelDesk;
	std::unique_ptr<Object3d> objDesk1[21][21];
	std::unique_ptr<Object3d> objDesk2[21][21];
	std::unique_ptr<Object3d> objDesk3[21][21];
	std::unique_ptr<Object3d> objDesk4[21][21];

	bool lightAction = 0;//ライト点滅フラグ
	int lightCount = 0;//ライト点滅のカウント
};