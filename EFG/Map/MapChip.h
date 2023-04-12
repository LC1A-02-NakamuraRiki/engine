#pragma once
#include <DirectXMath.h>
#include "Object3d.h"
#include "Sprite.h"
#include"LoadCSV.h"
#include <memory>
#include <array>
#include <map>
#include "EditLoader.h"

#define AREAVALUE (7) //横の最大枚数

class MapChip
{
private: // エイリアス
// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

	const float WALLSIZE = 8.0f;														//壁の大きさ
	const float MAPWALLSIZE = 16.0f;													//ミニマップの壁の大きさ
	const int MAPVALUE = 21;															//マップの最大サイズ
	const int MAPAREAVALUE = 7;
	const int CRYSTALVALUE = 11;
	const int DOORVALUE = 4;
	const int MAXNUMBER = 10;
public:
	~MapChip();
	void Initialize();//最初の初期化
	void InitializeValue();//タイトル時の初期化
	void MapCreate();//マップ作製
	void MapRandam(int mapArea[AREAVALUE][AREAVALUE],int mapArea2[AREAVALUE][AREAVALUE], int X, int Z);
	void MapMove(XMFLOAT2 mapPos);//ミニマップ移動
	void Update(XMFLOAT3 pos, XMFLOAT2 mapPos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3);//アップデート
	void StageUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3);
	void DoorOpen(XMFLOAT3 pos);
	void PlayerPosConvertMap(XMFLOAT3 pos);
	void CrystalUpdate(XMFLOAT3 pos);
	int ArrayValue(float x, float y);//座標からマップチップ配列の算出
	void Draw();//描画
	void DrawSprite(XMFLOAT3 pos);//スプライト描画
	void TimeStop();//時間停止
	void EnemyDisplay();//敵スポット

	int GetArrayValue(int x, int z) { return mapWall[z][x]; }			//マップチップの情報取得
	int GetPlayerArrayValue(int x, int z) { return mapPlayer[x][z]; }	//マップチップで表したプレイヤーの位置取得
	bool GetAllGetFlag() { return allGetFlag; }							//クリスタルをすべて取ったかフラグ取得
	bool GetStopFlag() { return stopFlag; }								//ストップフラグ取得
	bool GetDisplayFlag() { return displayFlag; }						//スポットフラグ取得
	bool GetCrystalGetFlag(int no) { return crystalGetFlag[no]; }		//クリスタル取れているかフラグ取得
	bool GetGateOpenFlag() { return gateOpenFlag; }						//ゲートが開いたかフラグ取得

	bool LightAction();																	//ライト点滅
	bool SetLightAction(bool actionFlag) { return this->lightAction = actionFlag; }		//フラグセット
private:
	std::unique_ptr<Model> modelMapWall;												//壁モデル
	std::unique_ptr<Model> modelCeiling;												//ライトモデル
	std::unique_ptr<Model> modelFlat;													//天井モデル
	std::unique_ptr<Model> modelFloor;													//床モデル
	std::unique_ptr<Model> modelCrystal;												//クリスタルモデル
	std::unique_ptr<Model> modelItemCrystal;											//アイテムクリスタルモデル
	std::unique_ptr<Model> modelItemCrystal2;											//アイテムクリスタルモデル
	std::array <std::unique_ptr<Object3d>, 11> objCrystal;//クリスタルオブジェクト

	std::unique_ptr<Sprite> spriteDoorOpen;//ドアUI
	std::array < std::unique_ptr<Model>, 4> modelDoor;//ドアモデル
	std::array<float, 4> doorAngle = { 90, 270,90,270 };//ドア角度
	std::array < std::unique_ptr<Object3d>, 4> objMapDoor;//ドアオブジェクト
	bool gateOpenFlag = false;//ゲート空いたか

	//クリスタルの位置3D
	std::array<XMFLOAT3, 11> crystalPos = { XMFLOAT3({ 1 * WALLSIZE - (21 * WALLSIZE / 2),  1.0f, 1 * WALLSIZE - (21 * WALLSIZE / 2)   }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)   }),
	XMFLOAT3({ 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),  1.0f, 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)   }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 16 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)   }),
	XMFLOAT3({ 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),  1.0f, 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 7 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 13 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }) };
	
	//クリスタルの位置2D
	std::array<XMFLOAT2, 11> mapCrystalPos = { XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 1)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 1)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 1)}, XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 10)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 16)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 10)},XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 19)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 19)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 19)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 7)} ,XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 13)}, };

	std::array<bool, 11> crystalGetFlag = { false,false,false,false,false,false,false,false,false,false,false };//クリスタル取ったか
	
	
	//マップ情報
	std::array<std::array<int, 21>, 21> mapWall = {};
	//プレイヤーの位置座標化
	std::array<std::array<int, 21>, 21> mapPlayer = {};

	bool allGetFlag = false;//クリスタル全部とれたか

	int stopTime = 0;//ストップタイム
	bool stopFlag = false;//ストップフラグ

	int displayTime = 0;//スポットタイム
	bool displayFlag = false;//スポットフラグ

	std::array < std::array < std::unique_ptr<Sprite>,21>,21> spriteMapWall;//ミニマップ壁
	std::unique_ptr<Sprite> spriteMapBack;//ミニマップの背景
	std::unique_ptr<Sprite> spriteMapFrame;//ミニマップのフレーム
					
	std::array <std::unique_ptr<Sprite>,11> spriteCrystal;//ミニマップのクリスタル
	std::array <std::unique_ptr<Sprite>,10> spriteNumberNum1;//ナンバー1のくらい
	std::array <std::unique_ptr<Sprite>,10> spriteNumberNum10;//ナンバー10のくらい

	std::unique_ptr<Sprite> spriteEnemyStop;//敵停止
	XMFLOAT2 stopFontSize = { 1200.0f * 10, 200.0f * 10 };//フォントサイズ
	int stopSprieteTime = 0;//時間
	float stopAlpha = 1.0f;//アルファ値

	std::unique_ptr<Sprite> spriteEnemySpot;//敵スポット
	XMFLOAT2 spotFontSize = { 1200.0f * 10, 200.0f * 10 };//フォントサイズ
	int spotSprieteTime = 0;//時間
	float spotAlpha = 1.0f;//アルファ値
	
	std::unique_ptr<Sprite> spriteSpotEffect;//スポットエフェクト
	int number = 11;//数字

	std::unique_ptr<Model> modelPictureFrame;//絵画のモデル
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame1;//絵画オブジェクト
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame2;//絵画オブジェクト
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame3;//絵画オブジェクト
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame4;//絵画オブジェクト

	std::unique_ptr<Model> modelDesk;//机モデル
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk1;//机オブジェクト
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk2;//机オブジェクト
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk3;//机オブジェクト
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk4;//机オブジェクト

	bool lightAction = 0;//ライト点滅フラグ
	int lightCount = 0;//ライト点滅のカウント

	EditData* editData = nullptr;

	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;

	EditData* randamEditData = nullptr;
	std::map<std::string, Model*> randamModels;
	std::vector<Object3d*> randamObjects;

	//ランダムのためのマップ1
	int mapWallLeftUp[7][7] = {
		1,1,1,1,1,1,1,
		1,2,0,0,0,3,0,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		1,0,1,1,1,5,0,
		1,5,0,0,3,10,1,
		1,0,1,1,0,1,1
	};
	int mapWallLeftCenter[7][7] = {
		1,8,4,1,0,1,1,
		1,1,5,0,7,1,1,
		1,2,10,1,5,0,0,
		1,0,1,1,0,1,1,
		1,8,4,1,5,0,0,
		1,1,5,0,7,1,1,
		1,2,10,1,0,1,1
	};
	int mapWallLeftDown[7][7] = {
		1,0,1,1,0,1,1,
		1,5,0,0,9,4,1,
		1,0,1,1,1,5,0,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		1,8,0,0,0,9,0,
		1,1,1,1,1,1,1
	};
	int mapWallCenterUp[7][7] = {
		1,1,1,1,1,1,1,
		4,1,2,0,4,1,2,
		8,3,10,1,8,3,10,
		1,0,1,1,1,0,1,
		0,9,3,0,3,9,0,
		1,1,0,1,0,1,1,
		1,1,0,1,0,1,1 };
	int mapWallCenterCenter[7][7] = {
		2,0,9,3,9,0,4,
		0,1,1,11,1,1,0,
		7,1,1,0,1,1,5,
		0,1,1,0,1,1,0,
		7,1,1,0,1,1,5,
		0,1,1,11,1,1,0,
		8,0,3,9,3,0,10
	};
	int mapWallCenterDown[7][7] = {
		1,1,0,1,0,1,1,
		1,1,0,1,0,1,1,
		0,3,9,0,9,3,0,
		1,0,1,1,1,0,1,
		2,9,4,1,2,9,4,
		10,1,8,0,10,1,8,
		1,1,1,1,1,1,1
	};
	int mapWallRightUp[7][7] = {
		1,1,1,1,1,1,1,
		0,3,0,0,0,4,1,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		0,7,1,1,1,0,1,
		1,8,3,0,0,7,1,
		1,1,0,1,1,0,1
	};
	int mapWallRightCenter[7][7] = {
		1,1,0,1,2,10,1,
		1,1,5,0,7,1,1,
		0,0,7,1,8,4,1,
		1,1,0,1,1,0,1,
		0,0,7,1,2,10,1,
		1,1,5,0,7,1,1,
		1,1,0,1,8,4,1
	};
	int mapWallRightDown[7][7] = {
		1,1,0,1,1,0,1,
		1,2,9,0,0,7,1,
		0,7,1,1,1,0,1,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		0,9,0,0,0,10,1,
		1,1,1,1,1,1,1
	};

	//ランダムのためのマップ2
	int mapWallLeftUp1[7][7] = {
		1,1,1,1,1,1,1,
		1,2,0,0,0,3,0,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		1,0,1,1,1,5,0,
		1,5,0,0,3,10,1,
		1,0,1,1,0,1,1
	};
	int mapWallLeftCenter1[7][7] = {
		1,8,4,1,0,1,1,
		1,1,5,0,7,1,1,
		1,2,10,1,5,0,0,
		1,0,1,1,0,1,1,
		1,8,4,1,5,0,0,
		1,1,5,0,7,1,1,
		1,2,10,1,0,1,1
	};
	int mapWallLeftDown1[7][7] = {
		1,0,1,1,0,1,1,
		1,5,0,0,9,4,1,
		1,0,1,1,1,5,0,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		1,8,0,0,0,9,0,
		1,1,1,1,1,1,1
	};
	int mapWallCenterUp1[7][7] = {
		1,1,1,1,1,1,1,
		4,1,2,0,4,1,2,
		8,3,10,1,8,3,10,
		1,0,1,1,1,0,1,
		0,9,3,0,3,9,0,
		1,1,0,1,0,1,1,
		1,1,0,1,0,1,1 };
	int mapWallCenterCenter1[7][7] = {
		2,0,9,3,9,0,4,
		0,1,1,11,1,1,0,
		7,1,1,0,1,1,5,
		0,1,1,0,1,1,0,
		7,1,1,0,1,1,5,
		0,1,1,11,1,1,0,
		8,0,3,9,3,0,10
	};
	int mapWallCenterDown1[7][7] = {
		1,1,0,1,0,1,1,
		1,1,0,1,0,1,1,
		0,3,9,0,9,3,0,
		1,0,1,1,1,0,1,
		2,9,4,1,2,9,4,
		10,1,8,0,10,1,8,
		1,1,1,1,1,1,1
	};
	int mapWallRightUp1[7][7] = {
		1,1,1,1,1,1,1,
		0,3,0,0,0,4,1,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		0,7,1,1,1,0,1,
		1,8,3,0,0,7,1,
		1,1,0,1,1,0,1
	};
	int mapWallRightCenter1[7][7] = {
		1,1,0,1,2,10,1,
		1,1,5,0,7,1,1,
		0,0,7,1,8,4,1,
		1,1,0,1,1,0,1,
		0,0,7,1,2,10,1,
		1,1,5,0,7,1,1,
		1,1,0,1,8,4,1
	};
	int mapWallRightDown1[7][7] = {
		1,1,0,1,1,0,1,
		1,2,9,0,0,7,1,
		0,7,1,1,1,0,1,
		1,0,1,1,1,0,1,
		1,0,1,1,1,0,1,
		0,9,0,0,0,10,1,
		1,1,1,1,1,1,1
	};
};