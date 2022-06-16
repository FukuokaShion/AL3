#include "PlayerBullet.h"

void PlayerBullet::Initialize(WorldTransform worldTransform) {
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	texture = TextureManager::Load("black.png");
	model = new Cube(texture);
	model->worldTransform_ = worldTransform;
	model->Affine();
}

void PlayerBullet::Update() {
	Transform();
	Rotate();

	//デバッグ表示
	debugText_->SetPos(50, 50);
	debugText_->Printf("playerBullet(%f, %f)", model->worldTransform_.translation_.x, model->worldTransform_.translation_.y);
}

void PlayerBullet::Transform() {
}

void PlayerBullet::Rotate() {
}

void PlayerBullet::Draw(ViewProjection viewProjection) {
	model->Draw(viewProjection);
}