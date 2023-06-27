#pragma once
#include <DirectXMath.h>
#include "Sprite.h"
#include <array>
#include <map>
#include <memory>

class MapUI
{
private: // �G�C���A�X
// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	//�X�v���C�g������
	void InitSprite();

	//�~�j�}�b�v�ړ�
	void MapUIUpdate(XMFLOAT2 mapPos, int number);

	//�X�v���C�g�`��
	void DrawSprite(XMFLOAT3 pos, int mapWall[21][21], bool crystalGetFlag[15], int number, bool stopFlag, bool spotAlphaFlag, bool stopAlphaFlag, bool gateOpen);

	//���Ԓ�~
	void TimeStop(bool crystalGetFlag, bool stopFlag, int stopTime);

	//�G�X�|�b�g
	void EnemyDisplay(bool crystalGetFlag, bool displayFlag, int displayTime);

	//�t�H���g��\������v�Z
	bool FontAlphaCalculation(float time, bool flag);

	//�t�H���g��\������v�Z
	bool FontSizeCalculation(float time, XMFLOAT2 size, bool flag);

private:
	const int MAPVALUE = 21;															//�}�b�v�̍ő�T�C�Y
	const int MAXNUMBER = 10;															//�i���o�[�ő�
	const int CRYSTALVALUE = 15;														//�N���X�^���̐�
	const float MAPWALLSIZE = 16.0f;													//�~�j�}�b�v�̕ǂ̑傫��
	const int MAXNUMUBER = 9;															//�i���o�[�ő�
	const int MAXNUMUBERTENNUM = 10;													//�i���o�[�ő�
	const int MAXNUMUBERNUM = 11;														//�i���o�[�ő�
	const int MAXSTOPTAIME = 300;														//�}�b�N�X�X�g�b�v�^�C��
	const int MAXSPOTTIME = 600;														//�}�b�N�X�X�|�b�g�^�C��
	const int MAXALPHATIME = 80;														//�A���t�@���Ԃ̍ő�
	const float MAXFONTMINUSX = 1200;													//�t�H���g���������Ȃ�ۂ̒lX
	const float MAXFONTMINUSY = 200;													//�t�H���g���������Ȃ�ۂ̒lY
	const float ALPHAMINUSVALUE = 0.05f;												//�A���t�@�̃}�C�i�X�l

	std::unique_ptr<Sprite> spriteDoorOpen;												//�h�AUI
	std::array < std::array < std::unique_ptr<Sprite>, 21>, 21> spriteMapWall;			//�~�j�}�b�v��
	std::unique_ptr<Sprite> spriteMapBack;												//�~�j�}�b�v�̔w�i
	std::unique_ptr<Sprite> spriteMapFrame;												//�~�j�}�b�v�̃t���[��				
	std::array <std::unique_ptr<Sprite>, 15> spriteCrystal;								//�~�j�}�b�v�̃N���X�^��
	std::array <std::unique_ptr<Sprite>, 10> spriteNumberNum1;							//�i���o�[1�̂��炢
	std::array <std::unique_ptr<Sprite>, 10> spriteNumberNum10;							//�i���o�[10�̂��炢
	std::unique_ptr<Sprite> spriteEnemyStop;											//�G��~
	std::unique_ptr<Sprite> spriteEnemySpot;											//�G�X�|�b�g
	std::unique_ptr<Sprite> spriteSpotEffect;											//�X�|�b�g�G�t�F�N�g

	XMFLOAT2 stopFontSize = { 1200.0f * 10, 200.0f * 10 };								//�t�H���g�T�C�Y
	int stopSprieteTime = 0;															//����
	float stopAlpha = 1.0f;																//�A���t�@�l
	XMFLOAT2 spotFontSize = { 1200.0f * 10, 200.0f * 10 };								//�t�H���g�T�C�Y
	int spotSprieteTime = 0;															//����
	float spotAlpha = 1.0f;																//�A���t�@�l
	bool displayFlag = false;															//�X�|�b�g�t���O

	//�N���X�^���̈ʒu2D
	std::array<XMFLOAT2, 15> mapCrystalPos = { XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 1)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 1)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 1)}, XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 10)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 16)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 10)},XMFLOAT2{100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 19)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 19)},
	XMFLOAT2{100 + (MAPWALLSIZE * 1),650 + (MAPWALLSIZE * 19)},XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 7)} ,XMFLOAT2{100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 13)},
	XMFLOAT2{100 + (MAPWALLSIZE * 13),650 + (MAPWALLSIZE * 13)},XMFLOAT2{100 + (MAPWALLSIZE * 7),650 + (MAPWALLSIZE * 13)}, XMFLOAT2{100 + (MAPWALLSIZE * 13),650 + (MAPWALLSIZE * 7)},
	XMFLOAT2{100 + (MAPWALLSIZE * 7),650 + (MAPWALLSIZE * 7)}, };
};

