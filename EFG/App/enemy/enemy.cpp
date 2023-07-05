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
	//敵初期化
	modelWalking = std::unique_ptr<FbxModel>(FbxLoader::GetInstance()->LoadModelFromFile("Walking"));		//モデル初期化
	objectWalking = std::make_unique<FbxObject3d>();														//object初期化
	objectWalking->Initialize();																			//初期化
	objectWalking->SetModel(modelWalking.get());															//モデルと同期
	objectWalking->PlayAnimation();																			//アニメーション

	//敵初期化
	modelAttack = std::unique_ptr<FbxModel>(FbxLoader::GetInstance()->LoadModelFromFile("Zombie Attack"));	//モデル初期化
	objectAttack = std::make_unique<FbxObject3d>();															//object初期化
	objectAttack->Initialize();																				//初期化
	objectAttack->SetModel(modelAttack.get());																//モデルと同期
	objectAttack->PlayAnimation();																			//アニメーション

	//スプライト読み込み
	spriteEnemyDot = std::unique_ptr<Sprite>(Sprite::Create(4, miniMapPos));								//敵の点
	spriteEnemyAngle = std::unique_ptr<Sprite>(Sprite::Create(6, miniMapPos));								//プレイヤーの向いてる方向
	spriteDeadEffect = std::unique_ptr<Sprite>(Sprite::Create(99, { 0,0 }));								//倒れた時のエフェクト
}



void Enemy::Update(Player* player, MapChip* mapChip, XMFLOAT2 mapPos, XMFLOAT2 plusValue, bool catchFlag1, bool catchFlag2)
{
	//探索
	AI(player, mapChip, plusValue);

	//移動
	if (StartFlag(player, mapChip, catchFlag1, catchFlag2)) {
		Move(player, mapChip, mapPos);
	}

	//オブジェクトのアップデート
	ObjectUpdate(player, mapChip);
}

void Enemy::ObjectUpdate(Player* player, MapChip* mapChip)
{
	//FBX関連
	FbxUpdate(player, mapChip);

	//ライトの情報を参照
	bool lightAction = MapEffect::LightAction(lightAction, lightCount);
	objectWalking->Update(lightAction);//アップデート
	objectAttack->Update(lightAction);//アップデート
}

void Enemy::FbxUpdate(Player* player, MapChip* mapChip)
{
	//アニメーション
	if (AnimationStop(mapChip)) {
		objectWalking->StopAnimation();
	}
	else {
		objectWalking->playAnimation();
	}

	//FBXアニメーション歩き
	objectWalking->SetPosition(XMFLOAT3(pos.x, pos.y - 2.8f, pos.z));
	objectWalking->SetRotation(XMFLOAT3(0, angle, 0));

	//FBXアニメーション攻撃
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
	//捕まってないとき
	if (!CatchCollision(player)){
		objectWalking->Draw(cmdList);//エネミー歩き描画
	}
	else{
		objectAttack->Draw(cmdList);//エネミーアタック描画
	}
}

void Enemy::DrawSprite(MapChip* mapChip)
{
	//スタートしたかどうか
	if (mapChip->GetDisplayFlag() && spriteEnemyDot->GetPosition().x < 420 && spriteEnemyDot->GetPosition().x > 100
		&& spriteEnemyDot->GetPosition().y > 650 && spriteEnemyDot->GetPosition().y < 986){
		spriteEnemyAngle->Draw(1.0f);//見ている方向描画
		spriteEnemyDot->Draw(1.0f);//エネミーのドット描画
	}

	//倒された時のアルファ
	const int MAXKILLTIME = 45;
	const float alphaValue = 0.01f;
	if (killTime > MAXKILLTIME){
		deadAlpha += alphaValue;
		spriteDeadEffect->Draw(deadAlpha);
	}
}

void Enemy::AI(Player* player, MapChip* mapChip, XMFLOAT2 plusValue)
{
	//プレイヤーの位置
	XMFLOAT3 playerPos = player->GetPos();

	//距離調べ
	float vectorX = playerPos.x + plusValue.x - pos.x;
	float vectorZ = playerPos.z + plusValue.y - pos.z;
	
	//優先度調べ
	if ((vectorX * vectorX) < (vectorZ * vectorZ)){
		vReserveFlag = true;
	}
	else if ((vectorX * vectorX) >= (vectorZ * vectorZ)){
		vReserveFlag = false;
	}

	//位置調整フラグ
	if (adjustmentFlag){
		adjustmentTime++;
		if (adjustmentTime >= maxAdjustmentTime){
			adjustmentTime = 0;
			adjustmentFlag = false;
		}
	}
	else if (!adjustmentFlag){//判別
		if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::LEFTTOP)){//上左角
			CornerJudge(MoveVector::UP, MoveVector::RIGHT, MoveVector::LEFT, MoveVector::DOWN);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::CENTERTOP)){//上中心
			ThreeWayJudgeVertical(vectorX, vectorZ, AriaValue::CENTERTOP);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::RIGHTTOP)){//上右角
			CornerJudge(MoveVector::RIGHT, MoveVector::DOWN, MoveVector::UP, MoveVector::LEFT);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::LEFTMIDDLE)){//中央左
			ThreeWayJudgeHorizontal(vectorX, vectorZ, AriaValue::LEFTMIDDLE);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::CENTERMIDDLE)){//中央
			FourWayJudge(vectorX, vectorZ);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::RIGHTMIDDLE)){//中央右
			ThreeWayJudgeHorizontal(vectorX, vectorZ, AriaValue::RIGHTMIDDLE);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::LEFTBOTTOM)){//下左角
			CornerJudge(MoveVector::LEFT, MoveVector::UP, MoveVector::DOWN, MoveVector::RIGHT);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::CENTERBOTTOM)){//下中央
			ThreeWayJudgeVertical(vectorX, vectorZ, AriaValue::CENTERBOTTOM);
		}
		else if (mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ) == static_cast<int>(AriaValue::RIGHTBOTTOM)){//下右角
			CornerJudge(MoveVector::DOWN, MoveVector::LEFT, MoveVector::RIGHT, MoveVector::UP);
		}
	}
}

void Enemy::Move(Player* player, MapChip* mapChip, XMFLOAT2 mapPos)
{
	if (mapChip->GetStopFlag() == false){//STOP発動してるか
		if (nowMove == static_cast<int>(MoveVector::DOWN)){//下に移動
			MoveValue(45, 360, 0, 1, 0, -1);
		}
		else if (nowMove == static_cast<int>(MoveVector::UP)){//上に移動
			MoveValue(-135, 180, 0, -1, 0, 1);
		}
		else if (nowMove == static_cast<int>(MoveVector::RIGHT)){//右に移動
			MoveValue(135, 90, 1, 0, -1, 0);
		}
		else if (nowMove == static_cast<int>(MoveVector::LEFT)){//左に移動
			MoveValue(-45, 270, -1, 0, 1, 0);
		}
	}

	//obj等に影響
	const float enemyAngleAdjustValue = 8.0f;
	spriteEnemyDot->SetPosition({ miniMapPos.x + mapPos.x , miniMapPos.y + mapPos.y });//位置セット
	spriteEnemyAngle->SetPosition({ miniMapPos.x + mapPos.x + enemyAngleAdjustValue, miniMapPos.y + mapPos.y + enemyAngleAdjustValue });//位置セット
}

void Enemy::MoveValue(float spriteAngle, float objectAngle, float xSpeed, float zSpeed, float adjustX, float adjustZ)
{
	spriteEnemyAngle->SetRotation(spriteAngle);		//角度をセット
	angle = objectAngle;							//角度の値をセット
	pos.x += speed * xSpeed;						//移動スピード
	pos.z += speed * zSpeed;						//移動スピード
	miniMapPos.x -= (speed * 2) * xSpeed;			//ミニマップの移動
	miniMapPos.y += (speed * 2) * zSpeed;			//ミニマップの移動
	adjustValueX = 3.9f * adjustX;					//調整値セット
	adjustValueZ = 3.9f * adjustZ;					//調整値セット
}

bool Enemy::CatchCollision(Player* player)
{
	//当たり判定調べ
	XMFLOAT3 playerPos = player->GetPos();//座標取得
	return Collision::ChenkSphere2Sphere(playerPos, pos, 2.5f, 3.0f);//プレイヤーと当たったか
}

bool Enemy::DeathAnimation(Player* player)
{
	//捕まったか
	if (CatchCollision(player)){
		//角度調べ
		float aX = player->GetPos().x - pos.x;//xのベクトル
		float aZ = player->GetPos().z - pos.z;//zのベクトル
		float aXZ = XMConvertToDegrees(float(atan2(aX, aZ)));//角度算出
		XMFLOAT3 playerPos = { 0,0,0 };
		playerPos = player->GetPos();

		//敵の方向ききった
		if (player->GetViewAngle() < aXZ + ANGLECAL && player->GetViewAngle() > aXZ - ANGLECAL){
			player->SetViewAngleY2(aXZ);
			player->SetViewAngleX2(DIEANGLEY);

			killTime++;
		}
		else if (player->GetViewAngle() < aXZ) {//敵の方向いてないとき
			player->SetViewAngleY(ANGLEVALUE);
		}
		else if (player->GetAngle() > aXZ) {//敵の方向いてないとき	
			player->SetViewAngleY(-ANGLEVALUE);
		}

		//モーション終わったか
		if (killTime > NOCKTIME){
			if (killTime > BLOODTIME){
				player->SetViewAngleX2(70.0f);
			}
			//少しづつ上向くのと血の演出
			else if (killTime > NOCKTIME){
				deadAlphaCountFlag = true;
				deadView += 9;
				player->SetViewAngleX2(10.0f + deadView);
			}

			//倒れる
			if (deadPos.y >= 0.0f){
				deadPos.y -= SINKVALUE;
			}
			playerPos.y = deadPos.y;
			player->SetPos(playerPos);
		}

		//モーション終わったか
		if (killTime > MAXDIETIME){
			killTime = 0;
			return true;
		}
	}
	return false;
}

bool Enemy::StartFlag(Player* player, MapChip* mapChip, bool catchFlag1, bool catchFlag2)
{
	//スタートしているか、捕まっていないか
	if (mapChip->GetGateOpenFlag() && !catchFlag1 && !catchFlag2){
		startStopTime++;//スタートまでの硬直タイム
		if (!CatchCollision(player) && startStopTime > 90){//スタートしたか
			return true;
		}
	}
	return false;
}

bool Enemy::AnimationStop(MapChip* mapChip)
{
	//モーションストップ
	if (mapChip->GetStopFlag() || startStopTime < 90){
		return true;
	}
	return false;
}

void Enemy::AiPriority(Player* player, XMFLOAT2 plusValue)
{
	//プレイヤーの位置
	XMFLOAT3 playerPos = player->GetPos();

	//距離調べ
	vectorX = playerPos.x + plusValue.x - pos.x;
	vectorZ = playerPos.z + plusValue.y - pos.z;

	//優先度調べ
	if ((vectorX * vectorX) < (vectorZ * vectorZ)){
		vReserveFlag = true;
	}
	else if ((vectorX * vectorX) >= (vectorZ * vectorZ)){
		vReserveFlag = false;
	}
}

int Enemy::NodeValue(MapChip* mapChip)
{
	//路地についたかどうか調べ
	return mapChip->ArrayValue(pos.x + adjustValueX, pos.z + adjustValueZ);
}

void Enemy::CornerJudge(MoveVector vecP1, MoveVector resultP1, MoveVector vecP2, MoveVector resultP2)
{
	//角の判定
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
	//T字路
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
	//T字路
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
	//十字路
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

//鬼ごとの初期化
void Enemy::InitializeValue()
{
	objectWalking->AnimationReset();
	objectAttack->AnimationReset();

	//鬼ごとの初期化
	pos = { -4.0f,3.0f,-28.0f };										//位置
	angle = 360;														//向き
	nowMove = static_cast<int>(MoveVector::UP);							//進む向き
	adjustValueX = 0;													//調整値X
	adjustValueZ = 0;													//調整値Z
	speed = 0.2f;														//スピード
	vReserveFlag = false;												//優先度
	miniMapPos = { 100 + (MAPWALLSIZE * 10),650 + (MAPWALLSIZE * 7) };	//ミニマップ位置
	maxAdjustmentTime = 40;												//調整タイム
	wallHitFlag = false;												//先読みの座標が壁に当たっているか
	adjustmentFlag = false;												//位置調整フラグ
	killTime = 0;														//殴りモーションの時間
	startStopTime = 0;													//スタートまでの硬直時間
	deadPos = { 0.0f,2.5f,0.0f };										//倒された時の座標
	deadView = 0.0f;													//倒された時の視点
	deadAlpha = 0.0f;													//倒された時のアルファ
}

void Enemy::InitializeValue2()
{
	objectWalking->AnimationReset();
	objectAttack->AnimationReset();
	//鬼ごとの初期化
	pos = { 4.0f,3.0f,68.0f };											//位置
	nowMove = static_cast<int>(MoveVector::LEFT);						//進む向き
	adjustValueX = 0;													//調整値X
	adjustValueZ = 0;													//調整値Z
	speed = 0.16f;														//スピード
	vReserveFlag = false;												//優先度
	miniMapPos = { 100 + (MAPWALLSIZE * 9),650 + (MAPWALLSIZE * 19) };	//ミニマップ位置
	maxAdjustmentTime = 49;												//調整タイム
	wallHitFlag = false;												//先読みの座標が壁に当たっているか
	adjustmentFlag = false;												//位置調整フラグ
	killTime = 0;														//殴りモーションの時間
	startStopTime = 0;													//スタートまでの硬直時間
	deadPos = { 0.0f,2.5f,0.0f };										//倒された時の座標
	deadView = 0.0f;													//倒された時の視点
	deadAlpha = 0.0f;													//倒された時のアルファ
}

void Enemy::InitializeValue3()
{
	objectWalking->AnimationReset();
	objectAttack->AnimationReset();
	//鬼ごとの初期化
	pos = { -76.0f,3.0f,-12.0f };										//位置
	nowMove = static_cast<int>(MoveVector::UP);							//進む向き
	adjustValueX = 0;													//調整値X
	adjustValueZ = 0;													//調整値Z
	speed = 0.16f;														//スピード
	vReserveFlag = false;												//優先度
	miniMapPos = { 100 + (MAPWALLSIZE * 19),650 + (MAPWALLSIZE * 9) };	//ミニマップ位置
	maxAdjustmentTime = 49;												//調整タイム
	wallHitFlag = false;												//先読みの座標が壁に当たっているか
	adjustmentFlag = false;												//位置調整フラグ
	killTime = 0;														//殴りモーションの時間
	startStopTime = 0;													//スタートまでの硬直時間
	deadPos = { 0.0f,2.5f,0.0f };										//倒された時の座標
	deadView = 0.0f;													//倒された時の視点
	deadAlpha = 0.0f;													//倒された時のアルファ
}