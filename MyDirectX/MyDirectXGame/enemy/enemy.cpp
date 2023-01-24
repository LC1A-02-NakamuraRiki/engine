#include "enemy.h"
#include "Collision.h"
#include "Input.h"

using namespace DirectX;

Enemy::~Enemy()
{
	safe_delete(spriteEnemyDot);
	safe_delete(spriteEnemyAngle);
	safe_delete(modelEnemy);
	safe_delete(objEnemy);
}

void Enemy::Initialize()
{
	//�G������
	modelEnemy = Model::CreateFromObject("gostFace", false);//���f��������
	objEnemy = Object3d::Create(modelEnemy);//object������
	objEnemy->SetPosition(pos);//�ʒu������
	objEnemy->SetScale({ 0.35f,0.3f,0.35f });//�傫��������

	//�摜�ǂݍ���
	if (!Sprite::LoadTexture(4, L"Resources/enemyDot.png")) {
		assert(0);
		return;
	}

	//�X�v���C�g�ǂݍ���
	spriteEnemyDot = Sprite::Create(4, miniMapPos);
	spriteEnemyAngle = Sprite::Create(6, miniMapPos);
}

//�S���Ƃ̏�����
void Enemy::InitializeValue()
{
	//�S���Ƃ̏�����
	pos = { -4.0f,3.0f,-28.0f };//�ʒu
	objEnemy->SetPosition(pos);//�ʒu�Z�b�g
	angle = 270;//����
	objEnemy->SetRotation({ 0, angle, 0 });//�����Z�b�g
	nowMove = UP;//�i�ތ���
	adjustValueX = 0;//�����lX
	adjustValueZ = 0;//�����lZ
	speed = 0.2f;//�X�s�[�h
	vReserveFlag = false;//�D��x
	miniMapPos = { 100 + (16.0f * 10),650 + (16.0f * 7) };//�~�j�}�b�v�ʒu
	maxAdjustmentTime = 40;//�����^�C��

	wallHitFlag = false;//��ǂ݂̍��W���ǂɓ������Ă��邩
	adjustmentFlag = false;//�ʒu�����t���O
	killTime = 0;//���胂�[�V�����̎���
	startStopTime = 0;//�X�^�[�g�܂ł̍d������
}

void Enemy::InitializeValue2()
{
	//�S���Ƃ̏�����
	pos = { 4.0f,3.0f,68.0f };//�ʒu
	objEnemy->SetPosition(pos);//�ʒu�Z�b�g
	nowMove = LEFT;//�i�ތ���
	adjustValueX = 0;//�����lX
	adjustValueZ = 0;//�����lZ
	speed = 0.16f;//�X�s�[�h
	vReserveFlag = false;//�D��x
	miniMapPos = { 100 + (16.0f * 9),650 + (16.0f * 19) };//�~�j�}�b�v�ʒu
	maxAdjustmentTime = 49;//�����^�C��
	wallHitFlag = false;//��ǂ݂̍��W���ǂɓ������Ă��邩
	adjustmentFlag = false;//�ʒu�����t���O
	killTime = 0;//���胂�[�V�����̎���
	startStopTime = 0;//�X�^�[�g�܂ł̍d������
}

void Enemy::InitializeValue3()
{
	//�S���Ƃ̏�����
	pos = { -76.0f,3.0f,-12.0f };//�ʒu
	objEnemy->SetPosition(pos);//�ʒu�Z�b�g
	nowMove = UP;//�i�ތ���
	adjustValueX = 0;//�����lX
	adjustValueZ = 0;//�����lZ
	speed = 0.16f;//�X�s�[�h
	vReserveFlag = false;//�D��x
	miniMapPos = { 100 + (16.0f * 19),650 + (16.0f * 9) };//�~�j�}�b�v�ʒu
	maxAdjustmentTime = 49;//�����^�C��
	wallHitFlag = false;//��ǂ݂̍��W���ǂɓ������Ă��邩
	adjustmentFlag = false;//�ʒu�����t���O
	killTime = 0;//���胂�[�V�����̎���
	startStopTime = 0;//�X�^�[�g�܂ł̍d������
}

void Enemy::Update(Player* player, MapChip* mapChip, XMFLOAT2 mapPos, XMFLOAT2 plusValue ,bool catchFlag1, bool catchFlag2)
{	
	//�A�b�v�f�[�g
	objEnemy->Update(pos,pos, pos,pos, 0, 1);
	//�T��
	AI(player, mapChip,plusValue);
	if (mapChip->GetGateOpenFlag() && !catchFlag1 && !catchFlag2)//�X�^�[�g���Ă��邩�A�߂܂��Ă��Ȃ���
	{
		startStopTime++;//�X�^�[�g�܂ł̍d���^�C��
		if(!CatchCollision(player) && startStopTime > 90)//�X�^�[�g������
		{
			//����
			Move(mapChip, mapPos);
		}
	}
}

void Enemy::Draw()
{
	objEnemy->Draw();//�G�l�~�[�`��
}

void Enemy::DrawSprite(MapChip* mapChip)
{
	//�X�^�[�g�������ǂ���
	if (mapChip->GetDisplayFlag() && spriteEnemyDot->GetPosition().x < 420 && spriteEnemyDot->GetPosition().x > 100
		&& spriteEnemyDot->GetPosition().y > 650 && spriteEnemyDot->GetPosition().y < 986)
	{
		spriteEnemyAngle->Draw(1.0f);//���Ă�������`��
		spriteEnemyDot->Draw(1.0f);//�G�l�~�[�̃h�b�g�`��
	}
}

void Enemy::AI(Player* player,MapChip* mapChip, XMFLOAT2 plusValue)
{
	XMFLOAT3 playerPos = player->GetPos();

	//��������
	float vectorX = playerPos.x + plusValue.x - pos.x;
	float vectorZ = playerPos.z + plusValue.y - pos.z;
	
	//�D��x����
	if ((vectorX * vectorX) < (vectorZ * vectorZ))
	{
		vReserveFlag = true;
	}
	else if ((vectorX * vectorX) >= (vectorZ * vectorZ))
	{
		vReserveFlag = false;
	}

	if (adjustmentFlag)//�ʒu�����t���O
	{
		adjustmentTime++;
		if (adjustmentTime >= maxAdjustmentTime)
		{
			adjustmentTime = 0;
			adjustmentFlag = false;
		}
	}
	else if (!adjustmentFlag)//�ʒu�����t���O
	{
		if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 2)//�㍶�p
		{
			if (nowMove == UP)
			{
				nowMove = RIGHT;
				adjustmentFlag = true;
			}
			if (nowMove == LEFT)
			{
				nowMove = DOWN;
				adjustmentFlag = true;
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 3)//�㒆�S
		{
			if (nowMove != LEFT && vReserveFlag == false && 0 < vectorX)
			{
				nowMove = RIGHT;
				adjustmentFlag = true;
			}
			else if (nowMove != RIGHT && vReserveFlag == false && vectorX < 0)
			{
				nowMove = LEFT;
				adjustmentFlag = true;
			}
			else if (nowMove != UP && vReserveFlag == true && vectorZ >= 0)
			{
				nowMove = DOWN;
				adjustmentFlag = true;
			}
			else if (nowMove == UP)
			{
				if (vectorX <= 0)
				{
					nowMove = LEFT;
					adjustmentFlag = true;
				}
				if (vectorX > 0)
				{
					nowMove = RIGHT;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == LEFT)
			{
				if (vectorZ > 0)
				{
					nowMove = DOWN;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == RIGHT)
			{
				if (vectorZ > 0)
				{
					nowMove = DOWN;
					adjustmentFlag = true;
				}
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 4)//��E�p
		{
			if (nowMove == RIGHT)
			{
				nowMove = DOWN;
				adjustmentFlag = true;
			}
			if (nowMove == UP)
			{
				nowMove = LEFT;
				adjustmentFlag = true;
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 5)//������
		{
			if (nowMove != DOWN && vReserveFlag == true && vectorZ < 0)
			{
				nowMove = UP;
				adjustmentFlag = true;
			}
			else if (nowMove != UP && vReserveFlag == true && 0 < vectorZ)
			{
				nowMove = DOWN;
				adjustmentFlag = true;
			}
			else if (nowMove != LEFT && vReserveFlag == false && vectorX >= 0)
			{
				nowMove = RIGHT;
				adjustmentFlag = true;
			}
			else if(nowMove == LEFT)
			{
				if (vectorZ <= 0)
				{
					nowMove = UP;
					adjustmentFlag = true;
				}
				else if (vectorZ > 0)
				{
					nowMove = DOWN;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == UP)
			{
				if (vectorX > 0)
				{
					nowMove = RIGHT;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == DOWN)
			{
				if (vectorX > 0)
				{
					nowMove = RIGHT;
					adjustmentFlag = true;
				}
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 6)//����
		{
			if (nowMove == UP && vectorZ > 0)
			{
				if (vectorX <= 0)
				{
					nowMove = LEFT;
					adjustmentFlag = true;
				}
				if (vectorX > 0)
				{
					nowMove = RIGHT;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == DOWN && vectorZ < 0)
			{
				if (vectorX <= 0)
				{
					nowMove = LEFT;
					adjustmentFlag = true;
				}
				if (vectorX > 0)
				{
					nowMove = RIGHT;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == RIGHT && vectorX < 0)
			{
				if (vectorZ <= 0)
				{
					nowMove = UP;
					adjustmentFlag = true;
				}
				if (vectorZ > 0)
				{
					nowMove = DOWN;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == LEFT && vectorX> 0)
			{
				if (vectorZ <= 0)
				{
					nowMove = UP;
					adjustmentFlag = true;
				}
				if (vectorZ > 0)
				{
					nowMove = DOWN;
					adjustmentFlag = true;
				}
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 7)//�����E
		{
		if (nowMove != DOWN && vReserveFlag == true && vectorZ < 0)
		{
			nowMove = UP;
			adjustmentFlag = true;
		}
		else if (nowMove != UP && vReserveFlag == true && 0 < vectorZ)
		{
			nowMove = DOWN;
			adjustmentFlag = true;
		}
		else if (nowMove != RIGHT && vReserveFlag == false && vectorX <= 0)
		{
			nowMove = LEFT;
			adjustmentFlag = true;
		}
		else if (nowMove == RIGHT)
			{
				if (vectorZ <= 0)
				{
					nowMove = UP;
					adjustmentFlag = true;
				}
				if (vectorZ > 0)
				{
					nowMove = DOWN;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == UP)
			{
				if (vectorX < 0)
				{
					nowMove = LEFT;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == DOWN)
			{
				if (vectorX < 0)
				{
					nowMove = LEFT;
					adjustmentFlag = true;
				}
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 8)//�����p
		{
			if (nowMove == LEFT)
			{
				nowMove = UP;
				adjustmentFlag = true;
			}
			if (nowMove == DOWN)
			{
				nowMove = RIGHT;
				adjustmentFlag = true;
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 9)//������
		{

		if (nowMove != RIGHT && vReserveFlag == false && vectorX < 0)
		{
			nowMove = LEFT;
			adjustmentFlag = true;
		}
		else if (nowMove != LEFT && vReserveFlag == false && 0 < vectorX)
		{
			nowMove = RIGHT;
			adjustmentFlag = true;
		}
		else if (nowMove != DOWN && vReserveFlag == true && vectorZ <= 0)
		{
			nowMove = UP;
			adjustmentFlag = true;
		}
		else if (nowMove == DOWN)
			{
				if (vectorX <= 0)
				{
					nowMove = LEFT;
					adjustmentFlag = true;
				}
				if (vectorX > 0)
				{
					nowMove = RIGHT;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == LEFT)
			{
				if (vectorZ < 0)
				{
					nowMove = UP;
					adjustmentFlag = true;
				}
			}
			else if (nowMove == RIGHT)
			{
				if (vectorZ < 0)
				{
					nowMove = UP;
					adjustmentFlag = true;
				}
			}
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == 10)//���E�p
		{
			if (nowMove == DOWN)
			{
				nowMove = LEFT;
				adjustmentFlag = true;
			}
			if (nowMove == RIGHT)
			{
				nowMove = UP;
				adjustmentFlag = true;
			}
		}
	}
}

void Enemy::Move(MapChip* mapChip, XMFLOAT2 mapPos)
{
	
	if (mapChip->GetStopFlag() == false)//STOP�������Ă邩
	{
		if (nowMove == DOWN)//���Ɉړ�
		{
			spriteEnemyAngle->SetRotation(45);//�p�x���Z�b�g
			objEnemy->SetRotation({0, 270, 0});//�p�x���Z�b�g
			angle = 270;//�p�x�̒l���Z�b�g
			pos.z += speed;//�ړ��X�s�[�h
			miniMapPos.y += speed * 2;//�~�j�}�b�v�̈ړ�
			adjustValueZ = -3.9f;//�����l�Z�b�g
		}
		else if (nowMove == UP)//��Ɉړ�
		{
			spriteEnemyAngle->SetRotation(-135);//�p�x���Z�b�g
			objEnemy->SetRotation({ 0, 90, 0 });//�p�x���Z�b�g
			angle = 90;//�p�x�̒l���Z�b�g
			pos.z -= speed;//�ړ��X�s�[�h
			miniMapPos.y -= speed * 2;//�~�j�}�b�v�̈ړ�
			adjustValueZ = 3.9f;//�����l�Z�b�g
		}
		else if (nowMove == RIGHT)//�E�Ɉړ�
		{
			spriteEnemyAngle->SetRotation(135);//�p�x���Z�b�g
			objEnemy->SetRotation({ 0, 0, 0 });//�p�x���Z�b�g
			angle = 0;//�p�x�̒l���Z�b�g
			pos.x += speed;//�ړ��X�s�[�h
			miniMapPos.x -= speed * 2;//�~�j�}�b�v�̈ړ�
			adjustValueX = -3.9f;//�����l�Z�b�g
		}
		else if (nowMove == LEFT)//���Ɉړ�
		{
			spriteEnemyAngle->SetRotation(-45);//�p�x���Z�b�g
			objEnemy->SetRotation({ 0, 180, 0 });//�p�x���Z�b�g
			angle = 180;//�p�x�̒l���Z�b�g
			pos.x -= speed;//�ړ��X�s�[�h
			miniMapPos.x += speed * 2;//�~�j�}�b�v�̈ړ�
			adjustValueX = 3.9f;//�����l�Z�b�g
		}
	}

	//obj���ɉe��
	spriteEnemyDot->SetPosition({ miniMapPos.x + mapPos.x , miniMapPos.y + mapPos.y });//�ʒu�Z�b�g
	spriteEnemyAngle->SetPosition({ miniMapPos.x + mapPos.x + 8, miniMapPos.y + mapPos.y + 8 });//�ʒu�Z�b�g
	objEnemy->SetPosition(pos);//�ʒu�Z�b�g
}

bool Enemy::CatchCollision(Player* player)
{
	XMFLOAT3 playerPos = player->GetPos();//���W�擾
	return Collision::ChenkSphere2Sphere(playerPos, pos, 2.5f, 3.0f);//�v���C���[�Ɠ���������
}

bool Enemy::DeathAnimation(Player* player)
{
	if (CatchCollision(player))//�߂܂�����
	{
		//�p�x����
		float aX = player->GetPos().x - pos.x;//x�̃x�N�g��
		float aZ = player->GetPos().z - pos.z;//z�̃x�N�g��
		float aXZ = XMConvertToDegrees(float(atan2(aX, aZ)));//�p�x�Z�o
		
		
		if (player->GetViewAngle() < aXZ + 30 && player->GetViewAngle() > aXZ - 30)//�G�̕�����������
		{
			player->SetViewAngleY2(aXZ);
			player->SetViewAngleX2(10);
			killTime++;
		}
		else if (player->GetViewAngle() < aXZ)//�G�̕������ĂȂ��Ƃ�
		{
			player->SetViewAngleY(15);
		}
		else if (player->GetAngle() > aXZ)//�G�̕������ĂȂ��Ƃ�
		{
			player->SetViewAngleY(-15);
		}

		if (killTime > 60)//���[�V�����I�������
		{
			killTime = 0;
			return true;
		}
	}
	return false;
}
