#pragma once
#include <DirectXMath.h>
#include "Object3d.h"
#include"LoadCSV.h"
#include <memory>
#include <array>
#include <map>
#include "EditLoader.h"
#include "MapUI.h"

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

	enum MapAriaNum {			//移動方向
		UpOrLeft,
		Center,
		DownOrRight
	};

	const float WALLSIZE = 8.0f;														//壁の大きさ
	const float MAPWALLSIZE = 16.0f;													//ミニマップの壁の大きさ
	const int MAPVALUE = 21;															//マップの最大サイズ
	const int MAPAREAVALUE = 7;															//1エリアのサイズ
	const int MAXAREA = 3;																//エリアの数
	const int CRYSTALVALUE = 15;														//クリスタルの数
	const int DOORVALUE = 4;															//ドアの数
	const int MAXNUMBER = 10;															//ナンバー最大
	const int MAXSTOPTAIME = 300;														//マックスストップタイム
	const int MAXSPOTTIME = 600;														//マックススポットタイム
	const int MAXNUMUBER = 9;															//ナンバー最大
	const int MAXNUMUBERTENNUM = 10;													//ナンバー最大
	const int MAXNUMUBERNUM = 11;														//ナンバー最大
	const int MAXACTIONCOUNT = 5;														//アクションの最大
	const int MAXALPHATIME = 80;														//アルファ時間の最大
	const float MAXFONTMINUSX = 1200;													//フォントが小さくなる際の値X
	const float MAXFONTMINUSY = 200;													//フォントが小さくなる際の値Y
	const float ALPHAMINUSVALUE = 0.05f;												//アルファのマイナス値
	const float SPOTCRYSTALNUM = 3;														//特殊クリスタルの番号スポット
	const float STOPCRYSTALNUM = 5;														//特殊クリスタルの番号ストップ
public:
	~MapChip();
	
	//最初の初期化
	void Initialize();

	//マップ初期化
	void InitMapObject();

	//モデルの読み込み
	void LoadModel();

	//マップの読み込み
	void LoadMap();

	//クリスタル初期化
	void InitCrystal();

	//ドア初期化
	void InitDoor();

	//タイトル時の初期化
	void InitializeValue();

	//マップ作製
	void MapCreate();

	//マップのランダム排出
	void MapRandam(int mapArea[AREAVALUE][AREAVALUE],int mapArea2[AREAVALUE][AREAVALUE], int X, int Z);
	
	//全体アップデート
	void Update(XMFLOAT3 pos, XMFLOAT2 mapPos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3);

	//ステージアップデート
	void StageUpdate(XMFLOAT3 pos, XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3);
	
	//マップアップデート
	void MapUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3);
	
	//OBJアップデート
	void MapObjUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3, int x, int z, int lightFlag);

	//クリスタルアップデート
	void CrystalUpdate(XMFLOAT3 pos);
	
	//机と絵画アップデート
	void DeskAndFrameUpdate(XMFLOAT3 enemyPos1, XMFLOAT3 enemyPos2, XMFLOAT3 enemyPos3, int lightFlag);
	
	//プレイヤーの位置をマップチップに変換
	void PlayerPosConvertMap(XMFLOAT3 pos);

	//座標からマップチップ配列の算出
	int ArrayValue(float x, float y);
	
	//描画
	void Draw();

	//描画
	void MiniMapDraw();

	//アルファの時間
	bool AlphaFlag(float time, bool flag);

	//ゲートオープン
	bool GateOpen(int mapX,int mapY);

	//マップチップの情報取得
	int GetArrayValue(int x, int z) { return mapWall[z][x]; }			

	//マップチップで表したプレイヤーの位置取得
	int GetPlayerArrayValue(int x, int z) { return mapPlayer[x][z]; }	

	//クリスタルをすべて取ったかフラグ取得
	bool GetAllGetFlag() { return allGetFlag; }							

	//ストップフラグ取得
	bool GetStopFlag() { return stopFlag; }								

	//スポットフラグ取得
	bool GetDisplayFlag() { return displayFlag; }					

	//クリスタル取れているかフラグ取得
	bool GetCrystalGetFlag(int no) { return crystalGetFlag[no]; }		

	//ゲートが開いたかフラグ取得
	bool GetGateOpenFlag() { return gateOpenFlag; }																					

	//フラグセット
	bool SetLightAction(bool actionFlag) { return this->lightAction = actionFlag; }		
private:

	std::unique_ptr <MapUI> mapUI;
	std::unique_ptr<Model> modelMapWall;												//壁モデル
	std::unique_ptr<Model> modelCeiling;												//ライトモデル
	std::unique_ptr<Model> modelFlat;													//天井モデル
	std::unique_ptr<Model> modelCrystal;												//クリスタルモデル
	std::unique_ptr<Model> modelItemCrystal;											//アイテムクリスタルモデル
	std::unique_ptr<Model> modelItemCrystal2;											//アイテムクリスタルモデル
	std::unique_ptr<Model> modelFloor;													//床モデル
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objMapWall;			//壁オブジェクト
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objCeiling;			//ライトオブジェクト
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objFloor;				//床のオブジェクト
	std::array <std::unique_ptr<Object3d>, 15> objCrystal;								//クリスタルオブジェクト
	std::array < std::unique_ptr<Model>, 4> modelDoor;									//ドアモデル
	std::array<float, 4> doorAngle = { 90, 270,90,270 };								//ドア角度
	std::array < std::unique_ptr<Object3d>, 4> objMapDoor;								//ドアオブジェクト
	bool gateOpenFlag = false;															//ゲート空いたか
	std::array<std::array<int, 21>, 21> mapWall = {};									//マップ情報	
	std::array<std::array<int, 21>, 21> mapPlayer = {};									//プレイヤーの位置座標化	
	bool allGetFlag = false;															//クリスタル全部とれたか
	int stopTime = 0;																	//ストップタイム
	bool stopFlag = false;																//ストップフラグ
	int displayTime = 0;																//スポットタイム
	int number = 11;																	//数字
	std::unique_ptr<Model> modelPictureFrame;											//絵画のモデル
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame1;		//絵画オブジェクト
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame2;		//絵画オブジェクト
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame3;		//絵画オブジェクト
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objPictureFrame4;		//絵画オブジェクト
	std::unique_ptr<Model> modelDesk;													//机モデル
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk1;				//机オブジェクト
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk2;				//机オブジェクト
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk3;				//机オブジェクト
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objDesk4;				//机オブジェクト
	bool lightAction = false;																//ライト点滅フラグ
	int lightCount = 0;																	//ライト点滅のカウント
	EditData* editData = nullptr;														//マップのデータ
	std::map<std::string, Model*> models;												//モデルデータ
	std::vector<Object3d*> objects;														//オブジェクトデータ
	EditData* randamEditData = nullptr;													//ランダムのマップのデータ
	std::map<std::string, Model*> randamModels;											//ランダムのモデルデータ
	std::vector<Object3d*> randamObjects;												//ランダムのオブジェクトデータ
	bool lightSilen = true;																//ライト点滅フラグ
	int lightDelayTime = 20;

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

	//クリスタルの位置3D
	std::array<XMFLOAT3, 15> crystalPos = { XMFLOAT3({ 1 * WALLSIZE - (21 * WALLSIZE / 2),  1.0f, 1 * WALLSIZE - (21 * WALLSIZE / 2)   }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)   }),
	XMFLOAT3({ 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),  1.0f, 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)   }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 16 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)   }),
	XMFLOAT3({ 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 1 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),  1.0f, 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2), 1.0f, 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2)  }),
	XMFLOAT3({ 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 19 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 7 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 10 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 13 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 7 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 13 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 13 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 13 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 7 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 7 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }),
	XMFLOAT3({ 13 * WALLSIZE - (MAPVALUE * WALLSIZE / 2),1.0f, 7 * WALLSIZE - (MAPVALUE * WALLSIZE / 2) }), };

	
	

	//ドアオブジェクトポジション
	std::array <XMFLOAT3,4> mapDoorPos = { XMFLOAT3({ -0.2f,0.2f,-16.0f }),
	XMFLOAT3({ -7.8f,0.2f,-16.0f }),
	XMFLOAT3({ -0.2f,0.2f,8.0f   }),
	XMFLOAT3({ -7.8f,0.2f,8.0f   }) };			

	//ドアの角度変更値
	std::array <float, 4> moveDoorAngle = {-10,10,10,-10};

	//クリスタル取ったか
	std::array<bool, 15> crystalGetFlag = { false,false,false,false,false,false,false,false,false,false,false,false,false,false,false };
};