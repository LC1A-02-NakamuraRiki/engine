#include "enemy.h"
#include "Collision.h"
#include "Input.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"
#include "MapEffect.h"

using namespace DirectX;

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	//�G������
	modelWalking = std::unique_ptr<FbxModel>(FbxLoader::GetInstance()->LoadModelFromFile("Walking"));		//���f��������
	objectWalking = std::make_unique<FbxObject3d>();														//object������
	objectWalking->Initialize();																			//������
	objectWalking->SetModel(modelWalking.get());															//���f���Ɠ���
	objectWalking->PlayAnimation();																			//�A�j���[�V����

	//�G������
	modelAttack = std::unique_ptr<FbxModel>(FbxLoader::GetInstance()->LoadModelFromFile("Zombie Attack"));	//���f��������
	objectAttack = std::make_unique<FbxObject3d>();															//object������
	objectAttack->Initialize();																				//������
	objectAttack->SetModel(modelAttack.get());																//���f���Ɠ���
	objectAttack->PlayAnimation();																			//�A�j���[�V����

	//�X�v���C�g�ǂݍ���
	spriteEnemyDot = std::unique_ptr<Sprite>(Sprite::Create(4, miniMapPos));								//�G�̓_
	spriteEnemyAngle = std::unique_ptr<Sprite>(Sprite::Create(6, miniMapPos));								//�v���C���[�̌����Ă����
	spriteDeadEffect = std::unique_ptr<Sprite>(Sprite::Create(99, { 0,0 }));								//�|�ꂽ���̃G�t�F�N�g
}



void Enemy::Update(Player* player, MapChip* mapChip, XMFLOAT2 mapPos, XMFLOAT2 plusValue, bool catchFlag1, bool catchFlag2)
{
	//�T��
	AI(player, mapChip, plusValue);

	//�ړ�
	if (StartFlag(player, mapChip, catchFlag1, catchFlag2)) {
		Move(player, mapChip, mapPos);
	}

	//�I�u�W�F�N�g�̃A�b�v�f�[�g
	ObjectUpdate(player, mapChip);
}

void Enemy::ObjectUpdate(Player* player, MapChip* mapChip)
{
	//FBX�֘A
	FbxUpdate(player, mapChip);

	//���C�g�̏����Q��
	bool lightAction = MapEffect::LightAction(lightAction, lightCount);
	objectWalking->Update(lightAction);//�A�b�v�f�[�g
	objectAttack->Update(lightAction);//�A�b�v�f�[�g
}

void Enemy::FbxUpdate(Player* player, MapChip* mapChip)
{
	//�A�j���[�V����
	if (AnimationStop(mapChip)) {
		objectWalking->StopAnimation();
	}
	else {
		objectWalking->playAnimation();
	}

	//FBX�A�j���[�V��������
	objectWalking->SetPosition(XMFLOAT3(pos.x, pos.y - 2.8f, pos.z));
	objectWalking->SetRotation(XMFLOAT3(0, angle, 0));

	//FBX�A�j���[�V�����U��
	if (CatchCollision(player)) {
		objectAttack->SetPosition(XMFLOAT3(pos.x, pos.y - 2.8f, pos.z));
		objectAttack->SetRotation(XMFLOAT3(0, (XMConvertToDegrees(atan2(pos.x - player->GetPos().x, pos.z - player->GetPos().z)) + 270) - 90, 0));
	}
	else {
		objectAttack->AnimationReset();
	}
}

void Enemy::Draw(Player* player, ID3D12GraphicsCommandList* cmdList)
{
	//�߂܂��ĂȂ��Ƃ�
	if (!CatchCollision(player)){
		objectWalking->Draw(cmdList);//�G�l�~�[�����`��
	}
	else{
		objectAttack->Draw(cmdList);//�G�l�~�[�A�^�b�N�`��
	}
}

void Enemy::DrawSprite(MapChip* mapChip)
{
	//�X�^�[�g�������ǂ���
	if (mapChip->GetDisplayFlag() && spriteEnemyDot->GetPosition().x < 420 && spriteEnemyDot->GetPosition().x > 100
		&& spriteEnemyDot->GetPosition().y > 650 && spriteEnemyDot->GetPosition().y < 986){
		spriteEnemyAngle->Draw(1.0f);//���Ă�������`��
		spriteEnemyDot->Draw(1.0f);//�G�l�~�[�̃h�b�g�`��
	}

	//�|���ꂽ���̃A���t�@
	const int MAXKILLTIME = 45;
	const float alphaValue = 0.01f;
	if (killTime > MAXKILLTIME){
		deadAlpha += alphaValue;
		spriteDeadEffect->Draw(deadAlpha);
	}
}

void Enemy::AI(Player* player, MapChip* mapChip, XMFLOAT2 plusValue)
{
	//�v���C���[�̈ʒu
	XMFLOAT3 playerPos = player->GetPos();

	//��������
	float vectorX = playerPos.x + plusValue.x - pos.x;
	float vectorZ = playerPos.z + plusValue.y - pos.z;
	
	//�D��x����
	if ((vectorX * vectorX) < (vectorZ * vectorZ)){
		vReserveFlag = true;
	}
	else if ((vectorX * vectorX) >= (vectorZ * vectorZ)){
		vReserveFlag = false;
	}

	//�ʒu�����t���O
	if (adjustmentFlag){
		adjustmentTime++;
		if (adjustmentTime >= maxAdjustmentTime){
			adjustmentTime = 0;
			adjustmentFlag = false;
		}
	}
	else if (!adjustmentFlag){//����
		if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::LEFTTOP)){//�㍶�p
			CornerJudge(MoveVector::UP, MoveVector::RIGHT, MoveVector::LEFT, MoveVector::DOWN);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::CENTERTOP)){//�㒆�S
			ThreeWayJudgeVertical(vectorX, vectorZ, AriaValue::CENTERTOP);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::RIGHTTOP)){//��E�p
			CornerJudge(MoveVector::RIGHT, MoveVector::DOWN, MoveVector::UP, MoveVector::LEFT);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::LEFTMIDDLE)){//������
			ThreeWayJudgeHorizontal(vectorX, vectorZ, AriaValue::LEFTMIDDLE);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::CENTERMIDDLE)){//����
			FourWayJudge(vectorX, vectorZ);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::RIGHTMIDDLE)){//�����E
			ThreeWayJudgeHorizontal(vectorX, vectorZ, AriaValue::RIGHTMIDDLE);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::LEFTBOTTOM)){//�����p
			CornerJudge(MoveVector::LEFT, MoveVector::UP, MoveVector::DOWN, MoveVector::RIGHT);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::CENTERBOTTOM)){//������
			ThreeWayJudgeVertical(vectorX, vectorZ, AriaValue::CENTERBOTTOM);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::RIGHTBOTTOM)){//���E�p
			CornerJudge(MoveVector::DOWN, MoveVector::LEFT, MoveVector::RIGHT, MoveVector::UP);
		}
	}
}

void Enemy::Move(Player* player, MapChip* mapChip, XMFLOAT2 mapPos)
{
	if (mapChip->GetStopFlag() == false){//STOP�������Ă邩
		if (nowMove == static_cast<int>(MoveVector::DOWN)){//���Ɉړ�
			MoveValue(45, 360, 0, 1, 0, -1);
		}
		else if (nowMove == static_cast<int>(MoveVector::UP)){//��Ɉړ�
			MoveValue(-135, 180, 0, -1, 0, 1);
		}
		else if (nowMove == static_cast<int>(MoveVector::RIGHT)){//�E�Ɉړ�
			MoveValue(135, 90, 1, 0, -1, 0);
		}
		else if (nowMove == static_cast<int>(MoveVector::LEFT)){//���Ɉړ�
			MoveValue(-45, 270, -1, 0, 1, 0);
		}
	}

	//obj���ɉe��
	const float enemyAngleAdjustValue = 8.0f;
	spriteEnemyDot->SetPosition({ miniMapPos.x + mapPos.x , miniMapPos.y + mapPos.y });//�ʒu�Z�b�g
	spriteEnemyAngle->SetPosition({ miniMapPos.x + mapPos.x + enemyAngleAdjustValue, miniMapPos.y + mapPos.y + enemyAngleAdjustValue });//�ʒu�Z�b�g
}

void Enemy::MoveValue(float spriteAngle, float objectAngle, float xSpeed, float zSpeed, float adjustX, float adjustZ)
{
	spriteEnemyAngle->SetRotation(spriteAngle);		//�p�x���Z�b�g
	angle = objectAngle;							//�p�x�̒l���Z�b�g
	pos.x += speed * xSpeed;						//�ړ��X�s�[�h
	pos.z += speed * zSpeed;						//�ړ��X�s�[�h
	miniMapPos.x -= (speed * 2) * xSpeed;			//�~�j�}�b�v�̈ړ�
	miniMapPos.y += (speed * 2) * zSpeed;			//�~�j�}�b�v�̈ړ�
	adjustValueX = 3.9f * adjustX;					//�����l�Z�b�g
	adjustValueZ = 3.9f * adjustZ;					//�����l�Z�b�g
}

bool Enemy::CatchCollision(Player* player)
{
	//�����蔻�蒲��
	XMFLOAT3 playerPos = player->GetPos();//���W�擾
	return Collision::ChenkSphere2Sphere(playerPos, pos, 2.5f, 3.0f);//�v���C���[�Ɠ���������
}

bool Enemy::DeathAnimation(Player* player)
{
	//�߂܂�����
	if (CatchCollision(player)){
		//�p�x����
		float aX = player->GetPos().x - pos.x;//x�̃x�N�g��
		float aZ = player->GetPos().z - pos.z;//z�̃x�N�g��
		float aXZ = XMConvertToDegrees(float(atan2(aX, aZ)));//�p�x�Z�o
		XMFLOAT3 playerPos = { 0,0,0 };
		playerPos = player->GetPos();

		//�G�̕�����������
		if (player->GetViewAngle() < aXZ + ANGLECAL && player->GetViewAngle() > aXZ - ANGLECAL){
			player->SetViewAngleY2(aXZ);
			player->SetViewAngleX2(DIEANGLEY);

			killTime++;
		}
		else if (player->GetViewAngle() < aXZ) {//�G�̕������ĂȂ��Ƃ�
			player->SetViewAngleY(ANGLEVALUE);
		}
		else if (player->GetAngle() > aXZ) {//�G�̕������ĂȂ��Ƃ�	
			player->SetViewAngleY(-ANGLEVALUE);
		}

		//���[�V�����I�������
		if (killTime > NOCKTIME){
			if (killTime > BLOODTIME){
				player->SetViewAngleX2(70.0f);
			}
			//�����Â�����̂ƌ��̉��o
			else if (killTime > NOCKTIME){
				deadAlphaCountFlag = true;
				deadView += 9;
				player->SetViewAngleX2(10.0f + deadView);
			}

			//�|���
			if (deadPos.y >= 0.0f){
				deadPos.y -= SINKVALUE;
			}
			playerPos.y = deadPos.y;
			player->SetPos(playerPos);
		}

		//���[�V�����I�������
		if (killTime > MAXDIETIME){
			killTime = 0;
			return true;
		}
	}
	return false;
}

bool Enemy::StartFlag(Player* player, MapChip* mapChip, bool catchFlag1, bool catchFlag2)
{
	//�X�^�[�g���Ă��邩�A�߂܂��Ă��Ȃ���
	if (mapChip->GetGateOpenFlag() && !catchFlag1 && !catchFlag2){
		startStopTime++;//�X�^�[�g�܂ł̍d���^�C��
		if (!CatchCollision(player) && startStopTime > 90){//�X�^�[�g������
			return true;
		}
	}
	return false;
}

bool Enemy::AnimationStop(MapChip* mapChip)
{
	//���[�V�����X�g�b�v
	if (mapChip->GetStopFlag() || startStopTime < 90){
		return true;
	}
	return false;
}

void Enemy::AiPriority(Player* player, XMFLOAT2 plusValue)
{
	//�v���C���[�̈ʒu
	XMFLOAT3 playerPos = player->GetPos();

	//��������
	vectorX = playerPos.x + plusValue.x - pos.x;
	vectorZ = playerPos.z + plusValue.y - pos.z;

	//�D��x����
	if ((vectorX * vectorX) < (vectorZ * vectorZ)){
		vReserveFlag = true;
	}
	else if ((vectorX * vectorX) >= (vectorZ * vectorZ)){
		vReserveFlag = false;
	}
}

int Enemy::NodeValue(MapChip* mapChip)
{
	//�H�n�ɂ������ǂ�������
	return mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ);
}

void Enemy::CornerJudge(MoveVector vecP1, MoveVector resultP1, MoveVector vecP2, MoveVector resultP2)
{
	//�p�̔���
	if (nowMove == static_cast<int>(vecP1)) {
		nowMove = static_cast<int>(resultP1);
		adjustmentFlag = true;
	}
	else if (nowMove == static_cast<int>(vecP2)) {
		nowMove = static_cast<int>(resultP2);
		adjustmentFlag = true;
	}
}

void Enemy::ThreeWayJudgeVertical(float vecValueX, float vecValueZ, AriaValue ariaNo)
{
	//T���H
	if (nowMove != static_cast<int>(MoveVector::LEFT) && vReserveFlag == false && 0 < vecValueX){
		nowMove = static_cast<int>(MoveVector::RIGHT);
		adjustmentFlag = true;
	}
	else if (nowMove != static_cast<int>(MoveVector::RIGHT) && vReserveFlag == false && vecValueX < 0){
		nowMove = static_cast<int>(MoveVector::LEFT);
		adjustmentFlag = true;
	}
	else if (nowMove != static_cast<int>(MoveVector::UP) && vReserveFlag == true && vecValueZ >= 0 && ariaNo == AriaValue::CENTERTOP){
		nowMove = static_cast<int>(MoveVector::DOWN);
		adjustmentFlag = true;
	}
	else if (nowMove != static_cast<int>(MoveVector::DOWN) && vReserveFlag == true && vecValueZ <= 0 && ariaNo == AriaValue::CENTERBOTTOM){
		nowMove = static_cast<int>(MoveVector::UP);
		adjustmentFlag = true;
	}
	else if (nowMove == static_cast<int>(MoveVector::UP) || nowMove == static_cast<int>(MoveVector::DOWN)){
		if (vecValueX <= 0){
			nowMove = static_cast<int>(MoveVector::LEFT);
			adjustmentFlag = true;
		}
		if (vecValueX > 0){
			nowMove = static_cast<int>(MoveVector::RIGHT);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::LEFT)){
		if (vecValueZ > 0 && ariaNo == AriaValue::CENTERTOP){
			nowMove = static_cast<int>(MoveVector::DOWN);
			adjustmentFlag = true;
		}
		else if (vecValueZ < 0 && ariaNo == AriaValue::CENTERBOTTOM){
			nowMove = static_cast<int>(MoveVector::UP);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::RIGHT)){
		if (vecValueZ > 0 && ariaNo == AriaValue::CENTERTOP){
			nowMove = static_cast<int>(MoveVector::DOWN);
			adjustmentFlag = true;
		}
		else if (vecValueZ < 0 && ariaNo == AriaValue::CENTERBOTTOM){
			nowMove = static_cast<int>(MoveVector::UP);
			adjustmentFlag = true;
		}
	} 
}

void Enemy::ThreeWayJudgeHorizontal(float vecValueX, float vecValueZ, AriaValue ariaNo)
{
	//T���H
	if (nowMove != static_cast<int>(MoveVector::DOWN) && vReserveFlag == true && vecValueZ < 0){
		nowMove = static_cast<int>(MoveVector::UP);
		adjustmentFlag = true;
	}
	else if (nowMove != static_cast<int>(MoveVector::UP) && vReserveFlag == true && 0 < vecValueZ){
		nowMove = static_cast<int>(MoveVector::DOWN);
		adjustmentFlag = true;
	}
	else if (nowMove != static_cast<int>(MoveVector::LEFT) && vReserveFlag == false && vecValueX >= 0 && ariaNo == AriaValue::LEFTMIDDLE){
		nowMove = static_cast<int>(MoveVector::RIGHT);
		adjustmentFlag = true;
	}
	else if (nowMove != static_cast<int>(MoveVector::RIGHT) && vReserveFlag == false && vecValueX <= 0 && ariaNo == AriaValue::RIGHTMIDDLE){
		nowMove = static_cast<int>(MoveVector::LEFT);
		adjustmentFlag = true;
	}
	else if (nowMove == static_cast<int>(MoveVector::LEFT) || nowMove == static_cast<int>(MoveVector::RIGHT)){
		if (vecValueZ <= 0)
		{
			nowMove = static_cast<int>(MoveVector::UP);
			adjustmentFlag = true;
		}
		else if (vecValueZ > 0)
		{
			nowMove = static_cast<int>(MoveVector::DOWN);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::UP)){
		if (vecValueX > 0 && ariaNo == AriaValue::LEFTMIDDLE){
			nowMove = static_cast<int>(MoveVector::RIGHT);
			adjustmentFlag = true;
		}
		else if (vecValueX < 0 && ariaNo == AriaValue::RIGHTMIDDLE){
			nowMove = static_cast<int>(MoveVector::LEFT);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::DOWN)){
		if (vecValueX > 0 && ariaNo == AriaValue::LEFTMIDDLE){
			nowMove = static_cast<int>(MoveVector::RIGHT);
			adjustmentFlag = true;
		}
		else if (vecValueX < 0 && ariaNo == AriaValue::RIGHTMIDDLE){
			nowMove = static_cast<int>(MoveVector::LEFT);
			adjustmentFlag = true;
		}
	}
}

void Enemy::FourWayJudge(float vecValueX, float vecValueZ)
{
	//�\���H
	if (nowMove == static_cast<int>(MoveVector::UP) && vecValueZ > 0){
		if (vecValueX <= 0){
			nowMove = static_cast<int>(MoveVector::LEFT);
			adjustmentFlag = true;
		}
		else if (vecValueX > 0){
			nowMove = static_cast<int>(MoveVector::RIGHT);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::DOWN) && vecValueZ < 0){
		if (vecValueX <= 0){
			nowMove = static_cast<int>(MoveVector::LEFT);
			adjustmentFlag = true;
		}
		else if (vecValueX > 0){
			nowMove = static_cast<int>(MoveVector::RIGHT);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::RIGHT) && vecValueX < 0){
		if (vecValueZ <= 0){
			nowMove = static_cast<int>(MoveVector::UP);
			adjustmentFlag = true;
		}
		else if (vecValueZ > 0){
			nowMove = static_cast<int>(MoveVector::DOWN);
			adjustmentFlag = true;
		}
	}
	else if (nowMove == static_cast<int>(MoveVector::LEFT) && vecValueX > 0){
		if (vecValueZ <= 0){
			nowMove = static_cast<int>(MoveVector::UP);
			adjustmentFlag = true;
		}
		else if (vecValueZ > 0){
			nowMove = static_cast<int>(MoveVector::DOWN);
			adjustmentFlag = true;
		}
	}
}

//�S���Ƃ̏�����
void Enemy::InitializeValue()
{
	objectWalking->AnimationReset();
	objectAttack->AnimationReset();

	//�S���Ƃ̏�����
	pos = { -4.0f,3.0f,-28.0f };										//�ʒu
	angle = 360;														//����
	nowMove = static_cast<int>(MoveVector::UP);							//�i�ތ���
	adjustValueX = 0;													//�����lX
	adjustValueZ = 0;													//�����lZ
	speed = 0.2f;														//�X�s�[�h
	vReserveFlag = false;												//�D��x
	miniMapPos = { 100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 7) };	//�~�j�}�b�v�ʒu
	maxAdjustmentTime = 40;												//�����^�C��
	wallHitFlag = false;												//��ǂ݂̍��W���ǂɓ������Ă��邩
	adjustmentFlag = false;												//�ʒu�����t���O
	killTime = 0;														//���胂�[�V�����̎���
	startStopTime = 0;													//�X�^�[�g�܂ł̍d������
	deadPos = { 0.0f,2.5f,0.0f };										//�|���ꂽ���̍��W
	deadView = 0.0f;													//�|���ꂽ���̎��_
	deadAlpha = 0.0f;													//�|���ꂽ���̃A���t�@
}

void Enemy::InitializeValue2()
{
	objectWalking->AnimationReset();
	objectAttack->AnimationReset();
	//�S���Ƃ̏�����
	pos = { 4.0f,3.0f,68.0f };											//�ʒu
	nowMove = static_cast<int>(MoveVector::LEFT);						//�i�ތ���
	adjustValueX = 0;													//�����lX
	adjustValueZ = 0;													//�����lZ
	speed = 0.16f;														//�X�s�[�h
	vReserveFlag = false;												//�D��x
	miniMapPos = { 100 + (MAPWALLSIZE * 9),650 + (MAPWALLSIZE * 19) };	//�~�j�}�b�v�ʒu
	maxAdjustmentTime = 49;												//�����^�C��
	wallHitFlag = false;												//��ǂ݂̍��W���ǂɓ������Ă��邩
	adjustmentFlag = false;												//�ʒu�����t���O
	killTime = 0;														//���胂�[�V�����̎���
	startStopTime = 0;													//�X�^�[�g�܂ł̍d������
	deadPos = { 0.0f,2.5f,0.0f };										//�|���ꂽ���̍��W
	deadView = 0.0f;													//�|���ꂽ���̎��_
	deadAlpha = 0.0f;													//�|���ꂽ���̃A���t�@
}

void Enemy::InitializeValue3()
{
	objectWalking->AnimationReset();
	objectAttack->AnimationReset();
	//�S���Ƃ̏�����
	pos = { -76.0f,3.0f,-12.0f };										//�ʒu
	nowMove = static_cast<int>(MoveVector::UP);							//�i�ތ���
	adjustValueX = 0;													//�����lX
	adjustValueZ = 0;													//�����lZ
	speed = 0.16f;														//�X�s�[�h
	vReserveFlag = false;												//�D��x
	miniMapPos = { 100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 9) };	//�~�j�}�b�v�ʒu
	maxAdjustmentTime = 49;												//�����^�C��
	wallHitFlag = false;												//��ǂ݂̍��W���ǂɓ������Ă��邩
	adjustmentFlag = false;												//�ʒu�����t���O
	killTime = 0;														//���胂�[�V�����̎���
	startStopTime = 0;													//�X�^�[�g�܂ł̍d������
	deadPos = { 0.0f,2.5f,0.0f };										//�|���ꂽ���̍��W
	deadView = 0.0f;													//�|���ꂽ���̎��_
	deadAlpha = 0.0f;													//�|���ꂽ���̃A���t�@
}