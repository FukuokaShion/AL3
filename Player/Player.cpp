#include "Player.h"

Player::~Player() {
	delete model;
}

void Player::Initialize() {
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	texture = TextureManager::Load("mushroom.jpg");
	model = new Cube(texture);
}

void Player::Update() {
	Transform();
	Rotate();
	Attack();
	//弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//デバッグ表示
	debugText_->SetPos(50, 20);
	debugText_->Printf("player(%f, %f)",model->worldTransform_.translation_.x,model->worldTransform_.translation_.y);
}

void Player::Transform() {
	//移動ベクトル
	Vector3 move = {0, 0, 0};
	//移動速度
	float moveSpeed = 0.4;

	// Y方向移動
	if (input_->PushKey(DIK_W)) {
		move.y = moveSpeed;
	} else if (input_->PushKey(DIK_S)) {
		move.y = -moveSpeed;
	}
	// X方向移動
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
	model->worldTransform_.translation_.x = max(model->worldTransform_.translation_.x, -kMoveLimitX);
	model->worldTransform_.translation_.x = min(model->worldTransform_.translation_.x, kMoveLimitX);
	model->worldTransform_.translation_.y = max(model->worldTransform_.translation_.y, -kMoveLimitY);
	model->worldTransform_.translation_.y = min(model->worldTransform_.translation_.y, kMoveLimitY);

	//転送
	model->Affine();
}

void Player::Rotate() {
	//回転ベクトル
	Vector3 rota = {0, 0, 0};
	//回転速度
	float PI = 3.1415;
	float rotaSpeed = PI/180;

	//Y軸回転
	if (input_->PushKey(DIK_Q)) {
		rota.y = rotaSpeed;
	} else if (input_->PushKey(DIK_E)) {
		rota.y = -rotaSpeed;
	}

	//回転ベクトルの加算
	model->worldTransform_.rotation_ += rota;

	//転送
	model->Affine();
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		//弾を生成し初期化
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		//自キャラの座標をコピー
		newBullet->Initialize(model->worldTransform_);

		//弾を登録
		bullets_.push_back(std::move(newBullet));
	}
}

void Player::Draw(ViewProjection viewProjection) {
	//自機描画
	model->Draw(viewProjection);
	//弾描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}