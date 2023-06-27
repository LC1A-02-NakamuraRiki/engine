#pragma once
#include <DirectXMath.h>
#include "Sprite.h"
#include <array>
#include <map>
#include <memory>

class MapUI
{
private: // エイリアス
// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	//スプライト初期化
	void InitSprite();

	//ミニマップ移動
	void MapUIUpdate(XMFLOAT2 mapPos, int number);

	//スプライト描画
	void DrawSprite(XMFLOAT3 pos, int mapWall[21][21], bool crystalGetFlag[15], int number, bool stopFlag, bool spotAlphaFlag, bool stopAlphaFlag, bool gateOpen);

	//時間停止
	void TimeStop(bool crystalGetFlag, bool stopFlag, int stopTime);

	//敵スポット
	void EnemyDisplay(bool crystalGetFlag, bool displayFlag, int displayTime);

	//フォントを表示する計算
	bool FontAlphaCalculation(float time, bool flag);

	//フォントを表示する計算
	bool FontSizeCalculation(float time, XMFLOAT2 size, bool flag);

private:
	const int MAPVALUE = 21;															//マップの最大サイズ
	const int MAXNUMBER = 10;															//ナンバー最大
	const int CRYSTALVALUE = 15;														//クリスタルの数
	const float MAPWALLSIZE = 16.0f;													//ミニマップの壁の大きさ
	const int MAXNUMUBER = 9;															//ナンバー最大
	const int MAXNUMUBERTENNUM = 10;													//ナンバー最大
	const int MAXNUMUBERNUM = 11;														//ナンバー最大
	const int MAXSTOPTAIME = 300;														//マックスストップタイム
	const int MAXSPOTTIME = 600;														//マックススポットタイム
	const int MAXALPHATIME = 80;														//アルファ時間の最大
	const float MAXFONTMINUSX = 1200;													//フォントが小さくなる際の値X
	const float MAXFONTMINUSY = 200;													//フォントが小さくなる際の値Y
	const float ALPHAMINUSVALUE = 0.05f;												//アルファのマイナス値

	std::unique_ptr<Sprite> spriteDoorOpen;												//ドアUI
	std::array < std::array < std::unique_ptr<Sprite>, 21>, 21> spriteMapWall;			//ミニマップ壁
	std::unique_ptr<Sprite> spriteMapBack;												//ミニマップの背景
	std::unique_ptr<Sprite> spriteMapFrame;												//ミニマップのフレーム				
	std::array <std::unique_ptr<Sprite>, 15> spriteCrystal;								//ミニマップのクリスタル
	std::array <std::unique_ptr<Sprite>, 10> spriteNumberNum1;							//ナンバー1のくらい
	std::array <std::unique_ptr<Sprite>, 10> spriteNumberNum10;							//ナンバー10のくらい
	std::unique_ptr<Sprite> spriteEnemyStop;											//敵停止
	std::unique_ptr<Sprite> spriteEnemySpot;											//敵スポット
	std::unique_ptr<Sprite> spriteSpotEffect;											//スポットエフェクト

	XMFLOAT2 stopFontSize = { 1200.0f * 10, 200.0f * 10 };								//フォントサイズ
	int stopSprieteTime = 0;															//時間
	float stopAlpha = 1.0f;																//アルファ値
	XMFLOAT2 spotFontSize = { 1200.0f * 10, 200.0f * 10 };								//フォントサイズ
	int spotSprieteTime = 0;															//時間
	float spotAlpha = 1.0f;																//アルファ値
	bool displayFlag = false;															//スポットフラグ

	//クリスタルの位置2D
	std::array<XMFLOAT2, 15> mapCrystalPos = { XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 1)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 1)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 1)}, XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 10)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 16)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 10)},XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 19)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 19)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 19)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 7)} ,XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 13)},
	XMFLOAT2{100 + (MAPWALLSIZE * 13),650 + (MAPWALLSIZE * 13)},XMFLOAT2{100 + (MAPWALLSIZE * 7),650 + (MAPWALLSIZE * 13)}, XMFLOAT2{100 + (MAPWALLSIZE * 13),650 + (MAPWALLSIZE * 7)},
	XMFLOAT2{100 + (MAPWALLSIZE * 7),650 + (MAPWALLSIZE * 7)}, };
};

