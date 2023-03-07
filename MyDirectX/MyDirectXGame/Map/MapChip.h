#pragma once
#include <DirectXMath.h>
#include "Object3d.h"
#include "Sprite.h"
#include"LoadCSV.h"
#include "SafeDelete.h"
#include <memory>
#include <array>
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

	int GetArrayValue(int x, int z) { return mapWall[z][x]; }//マップチップの情報取得
	int GetPlayerArrayValue(int x, int z) { return mapPlayer[x][z]; }//マップチップで表したプレイヤーの位置取得
	bool GetAllGetFlag() { return allGetFlag; }//クリスタルをすべて取ったかフラグ取得
	bool GetStopFlag() { return stopFlag; }//ストップフラグ取得
	bool GetDisplayFlag() { return displayFlag; }//スポットフラグ取得
	bool GetCrystalGetFlag(int no) { return crystalGetFlag[no]; }//クリスタル取れているかフラグ取得
	bool GetGateOpenFlag() { return gateOpenFlag; }//ゲートが開いたかフラグ取得

	bool LightAction();//ライト点滅
	bool SetLightAction(bool actionFlag) {return this->lightAction = actionFlag;}//フラグセット
private:
	
	std::unique_ptr<Model> modelMapWall;//壁モデル
	std::array < std::array < std::unique_ptr<Object3d>,21>,21> objMapWall;//壁オブジェクト
	std::unique_ptr<Model> modelCeiling;//ライトモデル
	std::unique_ptr<Model> modelFlat;//天井モデル
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objCeiling;//ライトオブジェクト
	std::unique_ptr<Model> modelFloor;//床モデル
	std::array < std::array < std::unique_ptr<Object3d>, 21>, 21> objFloor;//床オブジェクト
	std::unique_ptr<Model> modelCrystal;//クリスタルモデル
	std::unique_ptr<Model> modelItemCrystal;//アイテムクリスタルモデル
	std::array <std::unique_ptr<Object3d>, 11> objCrystal;//クリスタルオブジェクト

	std::unique_ptr<Sprite> spriteDoorOpen;//ドアUI
	std::array < std::unique_ptr<Model>,4> modelDoor;//ドアモデル
	std::array<float, 4> doorAngle = {90, 270,90,270};//ドア角度
	std::array < std::unique_ptr<Object3d>,4> objMapDoor;//ドアオブジェクト
	bool gateOpenFlag = false;//ゲート空いたか
	float wallSize = 8;//壁の大きさ

	//クリスタルの位置3D
	std::array<XMFLOAT3, 11> crystalPos = {XMFLOAT3({ 1 * wallSize - (21 * wallSize / 2),  1.0f, 1 * wallSize - (21 * wallSize / 2)   }),
	XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2), 1.0f, 1 * wallSize - (21 * wallSize / 2)   }),
	XMFLOAT3({ 19 * wallSize - (21 * wallSize / 2), 1.0f, 1 * wallSize - (21 * wallSize / 2)  }),
	XMFLOAT3({ 1 * wallSize - (21 * wallSize / 2),  1.0f, 10 * wallSize - (21 * wallSize / 2)   }),
	XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2), 1.0f, 16 * wallSize - (21 * wallSize / 2)   }),
	XMFLOAT3({ 19 * wallSize - (21 * wallSize / 2), 1.0f, 10 * wallSize - (21 * wallSize / 2)  }),
	XMFLOAT3({ 1 * wallSize - (21 * wallSize / 2),  1.0f, 19 * wallSize - (21 * wallSize / 2)  }),
	XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2), 1.0f, 19 * wallSize - (21 * wallSize / 2)  }),
	XMFLOAT3({ 19 * wallSize - (21 *  wallSize / 2),1.0f, 19 * wallSize - (21 *  wallSize / 2) }),
	XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2),1.0f, 7 * wallSize - (21 * wallSize / 2) }),
	XMFLOAT3({ 10 * wallSize - (21 * wallSize / 2),1.0f, 13 * wallSize - (21 * wallSize / 2) })	};
	
	//クリスタルの位置2D
	std::array<XMFLOAT2, 11> mapCrystalPos = { XMFLOAT2{100 + (16.0f * 19),650 + (16.0f * 1)},XMFLOAT2{100 + (16.0f * 10),650 + (16.0f * 1)},
	XMFLOAT2{100 + (16.0f * 1),650 + (16.0f * 1)},XMFLOAT2{100 + (16.0f * 19),650 + (16.0f * 10)},XMFLOAT2{100 + (16.0f * 10),650 + (16.0f * 16)},
	XMFLOAT2{100 + (16.0f * 1),650 + (16.0f * 10)},XMFLOAT2{100 + (16.0f * 19),650 + (16.0f * 19)},XMFLOAT2{100 + (16.0f * 10),650 + (16.0f * 19)},
	XMFLOAT2{100 + (16.0f * 1),650 + (16.0f * 19)},XMFLOAT2{100 + (16.0f * 10),650 + (16.0f * 7)},XMFLOAT2{100 + (16.0f * 10),650 + (16.0f * 13)}, };

	std::array<bool, 11> crystalGetFlag = { false,false,false,false,false,false,false,false,false,false,false };//クリスタル取ったか
	int MapValue = 21;//マップサイズ
	
	//マップ情報
	std::array<std::array<int, 21>, 21> mapWall = {};
	//プレイヤーの位置座標化
	std::array<std::array<int, 21>, 21> mapPlayer = {};

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
};