#include "enemy.h"
#include "Collision.h"
#include "Input.h"
#include "FbxLoader.h"
#include "FbxObject3d.h"

using namespace DirectX;

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	//�G������
	modelWalking = std::unique_ptr<FbxModel>(FbxLoader::GetInstance()->LoadModelFromFile("Walking"));//���f��������
	objectWalking = std::make_unique<FbxObject3d>();//object������
	objectWalking->Initialize();//������
	objectWalking->SetModel(modelWalking.get());//���f���Ɠ���
	objectWalking->PlayAnimation();//�A�j���[�V����


	//�G������
	modelAttack = std::unique_ptr<FbxModel>(FbxLoader::GetInstance()->LoadModelFromFile("Zombie Attack"));//���f��������
	objectAttack = std::make_unique<FbxObject3d>();//object������
	objectAttack->Initialize();//������
	objectAttack->SetModel(modelAttack.get());//���f���Ɠ���
	objectAttack->PlayAnimation();//�A�j���[�V����

	//�摜�ǂݍ���
	if (!Sprite::LoadTexture(4, L"Resources/enemyDot.png")) {
		assert(0);
		return;
	}
	//�摜�ǂݍ���
	if (!Sprite::LoadTexture(99, L"Resources/DeadEf.png")) {
		assert(0);
		return;
	}
	//�X�v���C�g�ǂݍ���
	spriteEnemyDot = std::unique_ptr<Sprite>(Sprite::Create(4, miniMapPos));
	spriteEnemyAngle = std::unique_ptr<Sprite>(Sprite::Create(6, miniMapPos));
	spriteDeadEffect = std::unique_ptr<Sprite>(Sprite::Create(99, {0,0}));
}

//�S���Ƃ̏�����
void Enemy::InitializeValue()
{
	objectWalking->AnimationReset();
	objectAttack->AnimationReset();

	//�S���Ƃ̏�����
	pos = { -4.0f,3.0f,-28.0f };//�ʒu
	angle = 360;//����
	nowMove = UP;//�i�ތ���
	adjustValueX = 0;//�����lX
	adjustValueZ = 0;//�����lZ
	speed = 0.2f;//�X�s�[�h
	vReserveFlag = false;//�D��x
	miniMapPos = { 100 + (mapWallSize * 10),650 + (mapWallSize * 7) };//�~�j�}�b�v�ʒu
	maxAdjustmentTime = 40;//�����^�C��

	wallHitFlag = false;//��ǂ݂̍��W���ǂɓ������Ă��邩
	adjustmentFlag = false;//�ʒu�����t���O
	killTime = 0;//���胂�[�V�����̎���
	startStopTime = 0;//�X�^�[�g�܂ł̍d������
	deadPos = { 0.0f,2.5f,0.0f };
	deadView = 0.0f;
	deadAlpha = 0.0f;
}

void Enemy::InitializeValue2()
{
	//�S���Ƃ̏�����
	pos = { 4.0f,3.0f,68.0f };//�ʒu
	nowMove = LEFT;//�i�ތ���
	adjustValueX = 0;//�����lX
	adjustValueZ = 0;//�����lZ
	speed = 0.16f;//�X�s�[�h
	vReserveFlag = false;//�D��x
	miniMapPos = { 100 + (mapWallSize * 9),650 + (mapWallSize * 19) };//�~�j�}�b�v�ʒu
	maxAdjustmentTime = 49;//�����^�C��
	wallHitFlag = false;//��ǂ݂̍��W���ǂɓ������Ă��邩
	adjustmentFlag = false;//�ʒu�����t���O
	killTime = 0;//���胂�[�V�����̎���
	startStopTime = 0;//�X�^�[�g�܂ł̍d������
	deadPos = { 0.0f,2.5f,0.0f };
	deadView = 0.0f;
	deadAlpha = 0.0f;
}

void Enemy::InitializeValue3()
{
	//�S���Ƃ̏�����
	pos = { -76.0f,3.0f,-12.0f };//�ʒu
	nowMove = UP;//�i�ތ���
	adjustValueX = 0;//�����lX
	adjustValueZ = 0;//�����lZ
	speed = 0.16f;//�X�s�[�h
	vReserveFlag = false;//�D��x
	miniMapPos = { 100 + (mapWallSize * 19),650 + (mapWallSize * 9) };//�~�j�}�b�v�ʒu
	maxAdjustmentTime = 49;//�����^�C��
	wallHitFlag = false;//��ǂ݂̍��W���ǂɓ������Ă��邩
	adjustmentFlag = false;//�ʒu�����t���O
	killTime = 0;//���胂�[�V�����̎���
	startStopTime = 0;//�X�^�[�g�܂ł̍d������
	deadPos = { 0.0f,2.5f,0.0f };
	deadView = 0.0f;
	deadAlpha = 0.0f;
}

void Enemy::Update(Player* player, MapChip* mapChip, XMFLOAT2 mapPos, XMFLOAT2 plusValue ,bool catchFlag1, bool catchFlag2)
{	
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
	if (mapChip->GetStopFlag() || startStopTime < 90)
	{
		objectWalking->StopAnimation();
	}
	else
	{
		objectWalking->playAnimation();
	}
	
	objectWalking->SetPosition(XMFLOAT3(pos.x, pos.y - 2.8f, pos.z));
	objectWalking->SetRotation(XMFLOAT3(0, angle, 0));
	
	if (CatchCollision(player)) {
		objectAttack->SetPosition(XMFLOAT3(pos.x, pos.y - 2.8f, pos.z));
		objectAttack->SetRotation(XMFLOAT3(0, (XMConvertToDegrees(atan2(pos.x - player->GetPos().x, pos.z - player->GetPos().z)) + 270) - 90, 0));
	}
	else
	{
		objectAttack->AnimationReset();
	}
	bool lightAction = mapChip->LightAction();
	objectWalking->Update(lightAction);//�A�b�v�f�[�g
	objectAttack->Update(lightAction);//�A�b�v�f�[�g
	
}

void Enemy::Draw(Player* player, ID3D12GraphicsCommandList* cmdList)
{
	if (!CatchCollision(player))//�߂܂��ĂȂ��Ƃ�
	{
		objectWalking->Draw(cmdList);//�G�l�~�[�����`��
	}
	else//�߂܂�����
	{
		objectAttack->Draw(cmdList);//�G�l�~�[�A�^�b�N�`��
	}
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
	if (killTime > 45)
	{
		deadAlpha += 0.01f;
		spriteDeadEffect->Draw(deadAlpha);
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
			angle = 360;//�p�x�̒l���Z�b�g
			pos.z += speed;//�ړ��X�s�[�h
			miniMapPos.y += speed * 2;//�~�j�}�b�v�̈ړ�
			adjustValueZ = -3.9f;//�����l�Z�b�g
		}
		else if (nowMove == UP)//��Ɉړ�
		{
			spriteEnemyAngle->SetRotation(-135);//�p�x���Z�b�g
			angle = 180;//�p�x�̒l���Z�b�g
			pos.z -= speed;//�ړ��X�s�[�h
			miniMapPos.y -= speed * 2;//�~�j�}�b�v�̈ړ�
			adjustValueZ = 3.9f;//�����l�Z�b�g
		}
		else if (nowMove == RIGHT)//�E�Ɉړ�
		{
			spriteEnemyAngle->SetRotation(135);//�p�x���Z�b�g
			angle = 90;//�p�x�̒l���Z�b�g
			pos.x += speed;//�ړ��X�s�[�h
			miniMapPos.x -= speed * 2;//�~�j�}�b�v�̈ړ�
			adjustValueX = -3.9f;//�����l�Z�b�g
		}
		else if (nowMove == LEFT)//���Ɉړ�
		{
			spriteEnemyAngle->SetRotation(-45);//�p�x���Z�b�g
			angle = 270;//�p�x�̒l���Z�b�g
			pos.x -= speed;//�ړ��X�s�[�h
			miniMapPos.x += speed * 2;//�~�j�}�b�v�̈ړ�
			adjustValueX = 3.9f;//�����l�Z�b�g
		}
	}

	//obj���ɉe��
	const float enemyAngleAdjustValue = 8.0f;
	spriteEnemyDot->SetPosition({ miniMapPos.x + mapPos.x , miniMapPos.y + mapPos.y });//�ʒu�Z�b�g
	spriteEnemyAngle->SetPosition({ miniMapPos.x + mapPos.x + enemyAngleAdjustValue, miniMapPos.y + mapPos.y + enemyAngleAdjustValue });//�ʒu�Z�b�g
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
		XMFLOAT3 playerPos = { 0,0,0 };
		playerPos = player->GetPos();
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

		if (killTime > 45)//���[�V�����I�������
		{
			if (killTime > 50)//���[�V�����I�������
			{
				player->SetViewAngleX2(70.0f);
			}
			//�����Â�����̂ƌ��̉��o
			else if (killTime > 45)
			{
				deadAlphaCountFlag = true;
				deadView += 9;
				player->SetViewAngleX2(10.0f + deadView);
			}

			//�|���
			if (deadPos.y >= 0.0f)
			{
				deadPos.y -= 0.25f;
			}
			playerPos.y = deadPos.y;
			player->SetPos(playerPos);
		}
		if (killTime > 150)//���[�V�����I�������
		{
			killTime = 0;
			return true;
		}
	}
	return false;
}
