#include "MapUI.h"

void MapUI::InitSprite()
{
	//�ǂ̏�����
	for (int x = 0; x < MAPVALUE; x++) {
		for (int y = 0; y < MAPVALUE; y++) {
			spriteMapWall[y][x] = nullptr;
		}
	}

	//����������
	for (int i = 0; i < MAXNUMBER; i++) {
		spriteNumberNum1[i] = std::unique_ptr<Sprite>(Sprite::Create(71 + i, { 260 - 10, 656 - MAPWALLSIZE - 96 }));
		spriteNumberNum10[i] = std::unique_ptr<Sprite>(Sprite::Create(71 + i, { 260 - 58, 656 - MAPWALLSIZE - 96 }));
	}

	//�X�g�b�vUI������
	spriteEnemyStop = std::unique_ptr<Sprite>(Sprite::Create(31, { 990, 850 }));
	spriteEnemyStop->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	spriteEnemyStop->SetSize(XMFLOAT2(stopFontSize));

	//�X�|�b�gUI������
	spriteEnemySpot = std::unique_ptr<Sprite>(Sprite::Create(32, { 990, 850 }));
	spriteEnemySpot->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));
	spriteEnemySpot->SetSize(XMFLOAT2(spotFontSize));

	//�~�j�}�b�v�̕Ǐ�����
	for (int x = 0; x < MAPVALUE; x++) {
		for (int y = 0; y < MAPVALUE; y++) {
			spriteMapWall[y][x] = std::unique_ptr<Sprite>(Sprite::Create(2, { -16 + 100 + (MAPWALLSIZE * (MAPVALUE - x)),650 + (MAPWALLSIZE * y) }));
		}
	}

	//�N���X�^��������
	for (int i = 0; i < CRYSTALVALUE; i++) { spriteCrystal[i] = std::unique_ptr<Sprite>(Sprite::Create(7, mapCrystalPos[i])); }
	spriteCrystal[3] = std::unique_ptr<Sprite>(Sprite::Create(17, mapCrystalPos[3]));
	spriteCrystal[5] = std::unique_ptr<Sprite>(Sprite::Create(130, mapCrystalPos[5]));
	spriteSpotEffect = std::unique_ptr<Sprite>(Sprite::Create(33, { 84,650 - 16 - 96 }));

	//�h�A���J����UI
	spriteDoorOpen = std::unique_ptr<Sprite>(Sprite::Create(45, { 990, 850 }));
	spriteDoorOpen->SetAnchorPoint(XMFLOAT2(0.5f, 0.5f));

	//�~�j�}�b�v�̘g
	spriteMapBack = std::unique_ptr<Sprite>(Sprite::Create(5, { -16 + 100,650 - 16 - 96 }));
	spriteMapFrame = std::unique_ptr<Sprite>(Sprite::Create(26, { -16 + 100,650 - 16 - 96 }));
}

void MapUI::MapUIUpdate(XMFLOAT2 mapPos, int number)
{
	//�~�j�}�b�v�̕ǈړ�
	for (int x = 0; x < MAPVALUE; x++) {
		for (int y = 0; y < MAPVALUE; y++) {
			spriteMapWall[y][x]->SetPosition({ mapPos.x - MAPWALLSIZE + 100 + (MAPWALLSIZE * (MAPVALUE - x)), mapPos.y + 650 + (MAPWALLSIZE * y) });
		}
	}

	//�~�j�}�b�v�̃N���X�^���ړ�
	for (int i = 0; i < CRYSTALVALUE; i++) {
		spriteCrystal[i]->SetPosition({ mapPos.x + mapCrystalPos[i].x, mapPos.y + mapCrystalPos[i].y });
	}

	//�����̃t�H���g
	if (number >= MAXNUMBER) {
		for (int i = 0; i < MAXNUMBER; i++) {
			spriteNumberNum1[i]->SetPosition(XMFLOAT2(260 - 10, 656 - 16 - 96));
		}
	}
	else {
		for (int i = 0; i < MAXNUMBER; i++) {
			spriteNumberNum1[i]->SetPosition(XMFLOAT2(225, 656 - 16 - 96));
		}
	}
}

void MapUI::DrawSprite(XMFLOAT3 pos, int mapWall[21][21], bool crystalGetFlag[15],int number,bool stopFlag, bool spotAlphaFlag,bool stopAlphaFlag,bool gateOpen)
{
	//�}�b�v���̍��W�n�̎擾
	XMFLOAT3 playerPos = pos;
	int mapY = int((playerPos.z / 8) + ((MAPVALUE + 1) / 2));
	int mapX = int((playerPos.x / 8) + ((MAPVALUE + 1) / 2));

	//�~�j�}�b�v�̗�
	spriteMapBack->Draw(1.0f);//�X�|�b�g���ĂȂ���
	if (displayFlag) {
		spriteSpotEffect->Draw(1.0f);//�X�|�b�g��
	}

	//��
	for (int x = 0; x < MAPVALUE; x++) {
		for (int y = 0; y < MAPVALUE; y++) {
			if (mapWall[y][x] == 1 && spriteMapWall[y][x]->GetPosition().x < 420 && spriteMapWall[y][x]->GetPosition().x > 100
				&& spriteMapWall[y][x]->GetPosition().y > 650 && spriteMapWall[y][x]->GetPosition().y < 986) {
				spriteMapWall[y][x]->Draw(1.0f);
			}
		}
	}

	//�N���X�^��
	for (int i = 0; i < CRYSTALVALUE; i++) {
		if (crystalGetFlag[i] == false && spriteCrystal[i]->GetPosition().x < 420 && spriteCrystal[i]->GetPosition().x > 100
			&& spriteCrystal[i]->GetPosition().y > 650 && spriteCrystal[i]->GetPosition().y < 986) {
			spriteCrystal[i]->Draw(1.0f);
		}
	}

	//�~�j�}�b�v�̃t���[��
	if (!displayFlag) {
		spriteMapFrame->Draw(1.0f);
	}

	//����
	for (int i = 0; i < MAXNUMUBER; i++) {
		if (number == i + 1) {
			spriteNumberNum1[number - 1]->Draw(1.0f);
		}
		if (number == MAXNUMUBERTENNUM) {
			spriteNumberNum10[i]->Draw(1.0f);
		}
	}

	//�X�|�b�g�t�H���g
	if (spotAlphaFlag) {
		spotSprieteTime++;
		spriteEnemySpot->Draw(spotAlpha);
	}

	//�X�g�b�v�t�H���g
	if (stopAlphaFlag) {
		stopSprieteTime++;
		spriteEnemyStop->Draw(stopAlpha);
	}

	//�Q�[�g�J���t���O
	if (gateOpen) {
		spriteDoorOpen->Draw(1.0f);
	}
}

void MapUI::TimeStop(bool crystalGetFlag,bool stopFlag,int stopTime)
{
	//�G��~
	if (crystalGetFlag && stopTime == 0) {
		stopFlag = true;
	}
	if (stopFlag) {
		stopTime++;
	}
	if (stopTime > MAXSTOPTAIME) {
		stopFlag = false;
	}

	//�X�g�b�v�t�H���g�֘A
	if (FontAlphaCalculation(stopSprieteTime, stopFlag)) {
		stopAlpha -= ALPHAMINUSVALUE;
	}
	if (FontSizeCalculation(stopSprieteTime, stopFontSize, stopFlag)) {
		stopFontSize.x -= MAXFONTMINUSX;
		stopFontSize.y -= MAXFONTMINUSY;
		spriteEnemyStop->SetSize(stopFontSize);
	}
}

void MapUI::EnemyDisplay(bool crystalGetFlag, bool displayFlag, int displayTime)
{
	//�G�X�|�b�g
	if (crystalGetFlag && displayTime == 0) {
		displayFlag = true;
	}
	if (displayFlag) {
		displayTime++;
	}
	if (displayTime > MAXSPOTTIME) {
		displayFlag = false;
	}

	//�X�|�b�g�t�H���g�֘A
	if (FontAlphaCalculation(spotSprieteTime, displayFlag)) {
		spotAlpha -= ALPHAMINUSVALUE;
	}
	if (FontSizeCalculation(spotSprieteTime, spotFontSize, displayFlag)) {
		spotFontSize.x -= MAXFONTMINUSX;
		spotFontSize.y -= MAXFONTMINUSY;
		spriteEnemySpot->SetSize(spotFontSize);
	}
}

bool MapUI::FontAlphaCalculation(float time, bool flag)
{
	//�A���t�@�l�ύX�t���O
	if (time > 60 && time < 80 && flag) {
		return true;
	}
	return false;
}

bool MapUI::FontSizeCalculation(float time, XMFLOAT2 size, bool flag)
{
	//�T�C�Y�ύX�t���O
	if (time < 60 && size.x > 1200 && flag) {
		return true;
	}
	return false;
}
