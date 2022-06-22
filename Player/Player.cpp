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
	//�e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//�f�o�b�O�\��
	debugText_->SetPos(50, 20);
	debugText_->Printf("player(%f, %f)",model->worldTransform_.translation_.x,model->worldTransform_.translation_.y);
}

void Player::Transform() {
	//�ړ��x�N�g��
	Vector3 move = {0, 0, 0};
	//�ړ����x
	float moveSpeed = 0.4;

	// Y�����ړ�
	if (input_->PushKey(DIK_W)) {
		move.y = moveSpeed;
	} else if (input_->PushKey(DIK_S)) {
		move.y = -moveSpeed;
	}
	// X�����ړ�
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
	model->worldTransform_.translation_.x = max(model->worldTransform_.translation_.x, -kMoveLimitX);
	model->worldTransform_.translation_.x = min(model->worldTransform_.translation_.x, kMoveLimitX);
	model->worldTransform_.translation_.y = max(model->worldTransform_.translation_.y, -kMoveLimitY);
	model->worldTransform_.translation_.y = min(model->worldTransform_.translation_.y, kMoveLimitY);

	//�]��
	model->Affine();
}

void Player::Rotate() {
	//��]�x�N�g��
	Vector3 rota = {0, 0, 0};
	//��]���x
	float PI = 3.1415;
	float rotaSpeed = PI/180;

	//Y����]
	if (input_->PushKey(DIK_Q)) {
		rota.y = rotaSpeed;
	} else if (input_->PushKey(DIK_E)) {
		rota.y = -rotaSpeed;
	}

	//��]�x�N�g���̉��Z
	model->worldTransform_.rotation_ += rota;

	//�]��
	model->Affine();
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		//�e�𐶐���������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		//���L�����̍��W���R�s�[
		newBullet->Initialize(model->worldTransform_);

		//�e��o�^
		bullets_.push_back(std::move(newBullet));
	}
}

void Player::Draw(ViewProjection viewProjection) {
	//���@�`��
	model->Draw(viewProjection);
	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}