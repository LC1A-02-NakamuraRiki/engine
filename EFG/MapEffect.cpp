#include "MapEffect.h"
#include "Input.h"

bool MapEffect::LightAction(bool lightActionFlag, float lightCount)
{
	const int MAXACTIONCOUNT = 5;
	const float lightDelayTime = 20;

	//ライトの点滅をしない
	if (!lightActionFlag) {
		return true;
	}

	//一定時間経過後ライトのカウントを0にする
	lightCount++;
	if (lightCount > lightDelayTime * 15) {
		lightCount = 0;
	}

	//ライトの点滅
	for (int i = 1; i < MAXACTIONCOUNT; i++) {
		if (lightCount > lightDelayTime * i) {
			if (i % 2 == 0) {
				return true;
			}
			else if (i % 2 == 1) {
				return false;
			}
		}
	}
	return true;
}

float MapEffect::DoorOpen(XMFLOAT3 pos ,bool gateOpenFlag,float doorAngle)
{
	const int MAPVALUE = 21;															//マップの最大サイズ
	const int DOORVALUE = 4;															//ドアの数
	//プレイヤーのマップの座標
	XMFLOAT3 playerPos = pos;
	int mapY = int((playerPos.z / 8) + ((MAPVALUE + 1) / 2));
	int mapX = int((playerPos.x / 8) + ((MAPVALUE + 1) / 2));

	//ドア関連
	if (gateOpenFlag == true && doorAngle> 0) {
		return moveDoorAngle[i];
	}

	//ゲートオープン
	if (Input::GetInstance()->KeybordTrigger(DIK_E) && mapX == 10 && mapY == 9) {
		gateOpenFlag = true;
	}
	return 0.0f;
}