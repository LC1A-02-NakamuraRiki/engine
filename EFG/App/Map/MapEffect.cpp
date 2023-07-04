#include "MapEffect.h"
#include "Input.h"

bool MapEffect::LightAction(bool lightActionFlag, float lightCount)
{
	const int MAXACTIONCOUNT = 5;
	const float lightDelayTime = 20;

	//���C�g�̓_�ł����Ȃ�
	if (!lightActionFlag) {
		return true;
	}

	//��莞�Ԍo�ߌド�C�g�̃J�E���g��0�ɂ���
	lightCount++;
	if (lightCount > lightDelayTime * 15) {
		lightCount = 0;
	}

	//���C�g�̓_��
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
	const int MAPVALUE = 21;															//�}�b�v�̍ő�T�C�Y
	const int DOORVALUE = 4;															//�h�A�̐�
	//�v���C���[�̃}�b�v�̍��W
	XMFLOAT3 playerPos = pos;
	int mapY = int((playerPos.z / 8) + ((MAPVALUE + 1) / 2));
	int mapX = int((playerPos.x / 8) + ((MAPVALUE + 1) / 2));

	//�h�A�֘A
	if (gateOpenFlag == true && doorAngle> 0) {
		return moveDoorAngle[i];
	}

	//�Q�[�g�I�[�v��
	if (Input::GetInstance()->KeybordTrigger(DIK_E) && mapX == 10 && mapY == 9) {
		gateOpenFlag = true;
	}
	return 0.0f;
}