#include "Player.h"

void Player::Initialize() {
	texture = TextureManager::Load("mushroom.jpg");
	model = new Cube(texture);
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
}

void Player::Update() {
	//�ړ��x�N�g��
	Vector3 move = {0, 0, 0};
	//�ړ����x
	float moveSpeed = 0.4;

	//Y�����ړ�
	if (input_->PushKey(DIK_W)) {
		move.y = moveSpeed;
	} else if (input_->PushKey(DIK_S)) {
		move.y = -moveSpeed;
	}
	//X�����ړ�
	if (input_->PushKey(DIK_A)) {
		move.x = -moveSpeed;
	} else if (input_->PushKey(DIK_D)) {
		move.x = moveSpeed;
	}

	//�ړ��x�N�g���̉��Z
	model->worldTransform_.translation_ += move;

	//�ړ�����
	const float kMoveLimitX = 36;
	const float kMoveLimitY = 20;
	
	//�͈͂𒴂��Ȃ�����
	model->worldTransform_.translation_.x = max(model->worldTransform_.translation_.x,-kMoveLimitX);
	model->worldTransform_.translation_.x = min(model->worldTransform_.translation_.x,kMoveLimitX);
	model->worldTransform_.translation_.y = max(model->worldTransform_.translation_.y,-kMoveLimitY);
	model->worldTransform_.translation_.y = min(model->worldTransform_.translation_.y,kMoveLimitY);

	//�]��
	model->Affine();



	//�f�o�b�O�\��
	debugText_->SetPos(50, 20);
	debugText_->Printf("player(%f, %f)",model->worldTransform_.translation_.x,model->worldTransform_.translation_.y);
}

void Player::Draw(ViewProjection viewProjection) {
	model->Draw(viewProjection);
}