#include "Player.h"
#include "Input.h"
#include <algorithm>
#include <iostream>

using namespace DirectX;

Player::~Player()
{
}

void Player::Initialize()
{
	//�X�v���C�g�̍쐬
	spritePlayerDot = std::unique_ptr<Sprite>(Sprite::Create(3, miniMapPos));	//�v���C���[�̓_
	spritePlayerAngle = std::unique_ptr<Sprite>(Sprite::Create(6, miniMapPos));	//�v���C���[�̌����Ă����
	spriteMoveUI = std::unique_ptr<Sprite>(Sprite::Create(100, { 0,0 }));		//�`���[�g���A��Move��UI
	spriteViewUI = std::unique_ptr<Sprite>(Sprite::Create(101, { 0,0 }));		//�`���[�g���A��View��UI
	spriteOpenUI = std::unique_ptr<Sprite>(Sprite::Create(102, { 0,0 }));		//�`���[�g���A��Open��UI
}

void Player::InitializeValue()
{
	miniMapPos = { 100 + (MAPWALLSIZE * 11),650 + (MAPWALLSIZE * 11) };	//�~�j�}�b�v�����l
	pos = { -4.0f,0.0f,4.0f };											//�v���C���[�̈ʒu
	mapPosValue = { 0,0 };												//�}�b�v�̍��W
	viewSpeed = 4.0f;													//���_�̑���
	target = { 0,0.0f,0 };												//�����_
	targetY = 0;														//�h��̒���
	angle = { 0,0,0 };													//��������
	walkShaking = 2.5;													//�����̗h���l
	isWalkShaking = false;												//�����̗h��̃t���O
	walkShakingTime = 0;												//�����̗h��̃^�C��
	angleX = 0;															//�J����X��
	angleY = 0;															//�J����Y��

}

void Player::Update(MapChip* mapChip, bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3)
{
	//�`���[�g���A���̉��o
	TutorialAlpha(mapChip);
	
	//�v���C���[�̌����̎Z�o
	AngleSearch();

	//�ړ�
	Move(mapChip,tutrialFlag,catchFlag,catchFlag2,catchFlag3);

	//�����̗h��
	WalkShaking();

	//���_
	View(tutrialFlag, catchFlag, catchFlag2, catchFlag3);

	//�X�v���C�g�֘A�̃|�W�V�����ƃA���O���Z�b�g
	UiUpdate();
}

void Player::DrawSprite()
{
	//�}�b�v�̕`��
	MapDraw();

	//UI�̕`��
	UiDraw();
}

void Player::Move(MapChip* mapChip, bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3)
{	
	//�ړ�
	if (MoveStopFlag(tutrialFlag, catchFlag, catchFlag2, catchFlag3)){
		//�O
		if (Input::GetInstance()->KeybordPush(DIK_W)){
			MoveUpdate(mapChip, FRONT);
		}
		//��
		if (Input::GetInstance()->KeybordPush(DIK_A)){
			MoveUpdate(mapChip, LEFT);
		}
		//��
		if (Input::GetInstance()->KeybordPush(DIK_S)){
			MoveUpdate(mapChip, BACK);
		}
		//�E
		if (Input::GetInstance()->KeybordPush(DIK_D)){
			MoveUpdate(mapChip, RIGHT);
		}
	}
}

bool Player::MoveStopFlag(bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3)
{
	//���o�ɓ����Ă��Ȃ���
	if (tutrialFlag == false && catchFlag == false && catchFlag2 == false && catchFlag3 == false){
		return true;
	}
	return false;
}

void Player::MoveValue(float vec)
{
	//�`���[�g���A���I��������
	if (!moveTutorialFlag) { moveTutorialFlag = true; }

	//�ʒu�ړ�
	pos.x += cos(((angle.y + vec) * PI) / -INVERSEVECTOR) * MOVESPEED;      // x���W���X�V
	pos.z += sin(((angle.y + vec) * PI) / -INVERSEVECTOR) * MOVESPEED;      // z���W���X�V

	//�}�b�v�̈ʒu�ړ�
	mapPosValue.x += cos(((angle.y + vec) * PI) / -INVERSEVECTOR) * (MOVESPEED * 2);				   // x���W���X�V
	mapPosValue.y += sin((((angle.y + vec) + INVERSEVECTOR) * PI) / -INVERSEVECTOR) * (MOVESPEED * 2); // y���W���X�V

	//���_�ړ�
	target.x += cos(((angle.y + vec) * PI) / -INVERSEVECTOR) * MOVESPEED;      // x���W���X�V
	target.z += sin(((angle.y + vec) * PI) / -INVERSEVECTOR) * MOVESPEED;      // z���W���X�V
}

void Player::MoveCollision(MapChip* mapChip, float vec)
{
	//�O���̓����蔻��
	if(TouchWall(mapChip, CollisionDirection::FRONT ))
	{
		PushBack(VerticalOrHorizontal::VERTICAL, vec);
	}
	//�����̓����蔻��
	if (TouchWall(mapChip, CollisionDirection::LEFT))
	{
		PushBack(VerticalOrHorizontal::HORIZONTAL, vec);
	}
	//��둤�̓����蔻��
	if (TouchWall(mapChip, CollisionDirection::BACK))
	{
		PushBack(VerticalOrHorizontal::VERTICAL, vec);
	}
	//�E���̓����蔻��
	if (TouchWall(mapChip, CollisionDirection::RIGHT))
	{
		PushBack(VerticalOrHorizontal::HORIZONTAL,vec);
	}
	isWalkShaking = true;
}

void Player::MoveUpdate(MapChip* mapChip, float vec)
{
	//�ړ��v�Z
	MoveValue(vec);

	//�����蔻��
	MoveCollision(mapChip, vec);
}

bool Player::TouchWall(MapChip* mapChip, CollisionDirection direction)
{
	//�ǂɐG��Ă��邩
	float XR = 0.0f;
	float ZR = 0.0f;
	
	//���ar�̒l����
	if (direction == CollisionDirection::FRONT) { ZR = R; }
	else if (direction == CollisionDirection::BACK) { ZR = -R; }
	else if (direction == CollisionDirection::RIGHT) { XR = R; }
	else if (direction == CollisionDirection::LEFT) { XR = -R; }

	//�������Ă��邩�ǂ����̔���
	if (mapChip->ArrayValue(pos.x + XR, pos.z + ZR) == 1 || mapChip->ArrayValue(pos.x + XR, pos.z + ZR) == 11){
		return true;
	}
	return false;
}

void Player::PushBack(VerticalOrHorizontal VerOrHor ,float vec)
{
	//�����߂��c
	if (VerOrHor == VerticalOrHorizontal::VERTICAL){
		pos.z += sin(((angle.y + vec + INVERSEVECTOR) * PI) / -INVERSEVECTOR) * MOVESPEED;      // z���W���X�V
		mapPosValue.y += sin(((angle.y + vec) * PI) / -INVERSEVECTOR) * (MOVESPEED * 2);
	}
	//�����߂���
	else if (VerOrHor == VerticalOrHorizontal::HORIZONTAL)
	{
		pos.x += cos(((angle.y + vec + INVERSEVECTOR) * PI) / -INVERSEVECTOR) * MOVESPEED;      // x���W���X�V
		mapPosValue.x += cos(((angle.y + vec + INVERSEVECTOR) * PI) / -INVERSEVECTOR) * (MOVESPEED * 2);
	}
}

void Player::WalkShaking()
{
	//�V�F�C�N���Ȃ�
	if (!shakeFlag){
		pos.y = 2.5;
	}
	//�V�F�C�N����
	else if (shakeFlag) {
		ShaikingMove();
	}
}

void Player::ShaikingMove()
{
	//�V�F�C�N�l
	const float shakeValue = 0.05f;
	if (isWalkShaking == true)
	{
		walkShakingTime++;
		if (walkShakingTime <= 8){
			walkShaking += shakeValue;
		}
		else if (walkShakingTime >= 8 && walkShakingTime <= 16){
			walkShaking -= shakeValue;
		}
		else if (walkShakingTime > 16){
			walkShaking = 2.5f;
			walkShakingTime = 0;
			isWalkShaking = false;
		}
	}
	pos.y = 0.5f + walkShaking;
	target.y = targetY + walkShaking;
}

void Player::View(bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3)
{
	const float INVERSEVECTOR = 180;
	
	//�ʒu���W�ƒ����_���W�̌v�Z
	ViewCalculation();

	//���_�𓮂����Ȃ���Ԃ̎��Ԃ�
	if (ViewFixedFlag(tutrialFlag, catchFlag, catchFlag2, catchFlag3)) { return; }

	//���_�𓮂��������ǂ���
	if (angleY != 0 && angleX != 0) {
		viewTutorialFlag = true;
	}

	//���_�̈ړ�
	angleY += Input::GetInstance()->GetMouseMove().lX * mouseViewSpeed;
	angleX -= Input::GetInstance()->GetMouseMove().lY * mouseViewSpeed;

}

void Player::ViewCalculation()
{
	//���_�v�Z
	XMVECTOR v0 = { 0,0,-10, 0 };
	//angle���W�A������y���܂��ɉ�]�B���a��-100
	XMMATRIX  rotM = XMMatrixIdentity();
	rotM *= XMMatrixRotationX(XMConvertToRadians(angleX));
	rotM *= XMMatrixRotationY(XMConvertToRadians(angleY));
	XMVECTOR v = XMVector3TransformNormal(v0, rotM);
	XMVECTOR cameraPos = { pos.x,pos.y,pos.z };
	XMVECTOR v3 = cameraPos + v;
	XMFLOAT3 f = { v3.m128_f32[0], v3.m128_f32[1], v3.m128_f32[2] };
	pos = { cameraPos.m128_f32[0], cameraPos.m128_f32[1], cameraPos.m128_f32[2] };
	target = f;

	//���_����
	if (angleY < -INVERSEVECTOR) {
		angleY = INVERSEVECTOR;
	}
	else if (angleY > INVERSEVECTOR) {
		angleY = -INVERSEVECTOR;
	}
	angleX = std::clamp(angleX, -85.0f, 85.0f);
}

bool Player::ViewFixedFlag(bool tutrialFlag, bool catchFlag, bool catchFlag2, bool catchFlag3)
{
	if (tutrialFlag == true || catchFlag == true || catchFlag2 == true || catchFlag3 == true)
	{
		return true;
	}
	return false;
}

void Player::AngleSearch()
{
	//���Ă�������̊p�x
	angle.y = XMConvertToDegrees(atan2(pos.x - target.x, pos.z - target.z)) + 90;
}

void Player::TutorialAlpha(MapChip* mapChip)
{
	//�h�A���J�������ǂ���
	if (mapChip->GetGateOpenFlag()) {
		openTutorialFlag = true;
	}

	//�`���[�g���A���֘A
	const float alphaSpeed = 0.025f;
	if (moveTutorialFlag){
		moveTutorial -= alphaSpeed;
	}
	if (viewTutorialFlag){
		viewTutorial -= alphaSpeed;
	}
	if (openTutorialFlag){
		openTutorial -= alphaSpeed;
	}
}

void Player::UiUpdate()
{
	//UI�̈ʒu�Z�b�g
	const float mapLeftValue = 100.0f;
	const float mapTopValue = 650.0f;
	const float angleConvertValue = 135;
	const float enemyAngleAdjustValue = 8.0f;

	//�v���C���[�̃X�v���C�g�̊֘A
	spritePlayerDot->SetPosition({ mapLeftValue + (MAPWALLSIZE * 10), mapTopValue + (MAPWALLSIZE * 11) });
	spritePlayerAngle->SetPosition({ mapLeftValue + (MAPWALLSIZE * 10) + enemyAngleAdjustValue, mapTopValue + (MAPWALLSIZE * 11) + enemyAngleAdjustValue });
	spritePlayerAngle->SetRotation(angle.y + angleConvertValue);
}

void Player::MapDraw()
{
	//�v���C���[�̃~�j�}�b�v�̏��
	spritePlayerAngle->Draw(1.0f);
	spritePlayerDot->Draw(1.0f);
}

void Player::UiDraw()
{
	//�`���[�g���A���̕`��
	spriteViewUI->Draw(viewTutorial);
	spriteMoveUI->Draw(moveTutorial);
	spriteOpenUI->Draw(openTutorial);
}

bool Player::AlartCalculation(MapChip* mapChip, int mapX, int mapY, int X, int Z)
{
	const int ALARTMAXSEARCH = 5;
	const int WALL = 1;
	//�߂��ɕǂ����邩
	for (int i = 1; i < ALARTMAXSEARCH; i++) {
		if (mapChip->GetArrayValue(mapX + (i * X), mapY + (i * Z)) == WALL) {
			i = ALARTMAXSEARCH;
		}
		if (mapChip->GetArrayValue(mapX + (i * X), mapY + (i * Z)) != WALL && mapChip->GetPlayerArrayValue(mapX + (i * X), mapY + (i * Z)) == WALL) {
			return true;
		}
	}
	return false;
}

bool Player::AlartFlag(MapChip* mapChip, XMFLOAT3 enemyPos)
{
	//�}�b�v���̍��W�̎擾
	int mapX = int((enemyPos.x / 8) + ((MAPVALUE + 1) / 2));
	int mapY = int((enemyPos.z / 8) + ((MAPVALUE + 1) / 2));

	//�߂��ɕǂ����邩
	if (AlartCalculation(mapChip, mapX, mapY, 1, -1)) {return true;}
	if (AlartCalculation(mapChip, mapX, mapY, 1, +1)) {return true;}
	if (AlartCalculation(mapChip, mapX, mapY, -1, 1)) {return true;}
	if (AlartCalculation(mapChip, mapX, mapY, +1, 1)) {return true;}
	
	return false;
}

int Player::ShortCutFlag(MapChip* mapChip, XMFLOAT3 enemyPos, int X, int Z)
{
	//�}�b�v���̍��W�̎擾
	int mapX = int((enemyPos.x / 8) + ((MAPVALUE + 1) / 2));
	int mapY = int((enemyPos.z / 8) + ((MAPVALUE + 1) / 2));
	const int ALARTMAXSEARCH = 5;
	const int PLAYER = 1;
	const int WALL = 1;
	//�߂��ɕǂ����邩
	for (int i = 1; i < ALARTMAXSEARCH; i++){
		if (mapChip->GetArrayValue(mapX + (i * X), mapY + (i * Z)) == WALL){
			return i;
		}
		if (mapChip->GetArrayValue(mapX + (i * X), mapY + (i * Z)) != WALL && mapChip->GetPlayerArrayValue(mapX + (i * X), mapY + (i * Z)) == WALL){
			return i;
		}	
	}

	return 0;
}

XMFLOAT2 Player::ShortCutValue(MapChip* mapChip, XMFLOAT3 enemyPos, float X, float Z, CHECKVECTOR vector)
{
	//���}�X������邩�̒���
	XMFLOAT2 plusValue = { 0,0 };
	float vectorX = pos.x - enemyPos.x;
	float vectorZ = pos.z - enemyPos.z;
	const int ALARTMAXSEARCH = 5;
	const int WALL = 1;

	for (int i = 1; i < ALARTMAXSEARCH + 1; i++){
		if (mapChip->ArrayValue(pos.x + (WALLSIZE * (i * X)), pos.z + (WALLSIZE * (i * Z))) == WALL || i == ALARTMAXSEARCH){
			if (vector == CHECKVECTOR::ZMINUS){
				plusValue.x = 0;
				plusValue.y = -WALLSIZE * (i - 1);
			}
			else if (vector == CHECKVECTOR::ZPLUS){
				plusValue.x = 0;
				plusValue.y = WALLSIZE * (i - 1);
			}
			else if (vector == CHECKVECTOR::XMINUS){
				plusValue.y = 0;
				plusValue.x = -WALLSIZE * (i - 1);
			}
			else if (vector == CHECKVECTOR::XPLUS){
				plusValue.y = 0;
				plusValue.x = WALLSIZE * (i - 1);
			}
		}
	}
	return plusValue;
}

XMFLOAT2 Player::GetShortCut(MapChip* mapChip, XMFLOAT3 enemyPos)
{
	//�}�b�v���̍��W�̎擾
	int mapX = int((enemyPos.x / 8) + ((MAPVALUE + 1) / 2));
	int mapY = int((enemyPos.z / 8) + ((MAPVALUE + 1) / 2));
	const int ALARTMAXSEARCH = 5;
	const int PLAYER = 1;
	const int WALL = 1;

	//�߂��ɕǂ����邩
	if (ShortCutFlag(mapChip, enemyPos, 1, -1)) { return XMFLOAT2{ 0,0 }; }
	if (ShortCutFlag(mapChip, enemyPos, 1, +1)) { return XMFLOAT2{ 0,0 }; }
	if (ShortCutFlag(mapChip, enemyPos, -1, 1)) { return XMFLOAT2{ 0,0 }; }
	if (ShortCutFlag(mapChip, enemyPos, +1, 1)) { return XMFLOAT2{ 0,0 }; }
	

	//���}�X������邩�̒���
	XMFLOAT2 plusValue = { 0,0 };
	float vectorX = pos.x - enemyPos.x;
	float vectorZ = pos.z - enemyPos.z;
	if (-45 < angleY && angleY < 45){
		plusValue = ShortCutValue(mapChip, enemyPos, 1.0f, -1.0f, CHECKVECTOR::ZMINUS);
	}
	else if (135 < angleY || angleY < -135){
		plusValue = ShortCutValue(mapChip, enemyPos, 1.0f, 1.0f, CHECKVECTOR::ZPLUS);
	}
	else if (-135 < angleY && angleY < -45){
		plusValue = ShortCutValue(mapChip, enemyPos, 1.0f, 1.0f, CHECKVECTOR::XPLUS);
	}
	else if (45 < angleY && angleY < 135){
		plusValue = ShortCutValue(mapChip, enemyPos, -1.0f, 1.0f, CHECKVECTOR::XMINUS);
	}
	return plusValue;
}