#include "Player.h"

void Player::Initialize() {
	texture = TextureManager::Load("mushroom.jpg");
	model = new Cube(texture);
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
}

void Player::Update() {
	//移動ベクトル
	Vector3 move = {0, 0, 0};
	//移動速度
	float moveSpeed = 0.4;

	//Y方向移動
	if (input_->PushKey(DIK_W)) {
		move.y = moveSpeed;
	} else if (input_->PushKey(DIK_S)) {
		move.y = -moveSpeed;
	}
	//X方向移動
	if (input_->PushKey(DIK_A)) {
		move.x = -moveSpeed;
	} else if (input_->PushKey(DIK_D)) {
		move.x = moveSpeed;
	}

	//移動ベクトルの加算
	model->worldTransform_.translation_ += move;

	//移動制限
	const float kMoveLimitX = 36;
	const float kMoveLimitY = 20;
	
	//範囲を超えない処理
	model->worldTransform_.translation_.x = max(model->worldTransform_.translation_.x,-kMoveLimitX);
	model->worldTransform_.translation_.x = min(model->worldTransform_.translation_.x,kMoveLimitX);
	model->worldTransform_.translation_.y = max(model->worldTransform_.translation_.y,-kMoveLimitY);
	model->worldTransform_.translation_.y = min(model->worldTransform_.translation_.y,kMoveLimitY);

	//転送
	model->Affine();



	//デバッグ表示
	debugText_->SetPos(50, 20);
	debugText_->Printf("player(%f, %f)",model->worldTransform_.translation_.x,model->worldTransform_.translation_.y);
}

void Player::Draw(ViewProjection viewProjection) {
	model->Draw(viewProjection);
}