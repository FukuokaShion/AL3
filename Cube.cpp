#include"Cube.h"
#include"DebugCamera.h"

Cube::Cube() {
	//�t�@�C�����������ăe�N�X�`����ǂݍ���
	textureHandle_ = TextureManager::Load("mushroom.jpg");
	// 3D���f���̐���
	model_ = Model::Create();
	

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
}

Cube::~Cube() { delete model_; }

void Cube::Affine(Vector3 scale,Vector3 rota,Vector3 trans) {
	//�X�P�[�����O
	worldTransform_.scale_ = {scale.x, scale.y, scale.z};
	Matrix4 matScale = {
		worldTransform_.scale_.x,0,0,0,
		0,worldTransform_.scale_.y,0,0,
		0,0,worldTransform_.scale_.z,0,
		0,0,0,1
	};
	
	//��]
	worldTransform_.rotation_ = {rota.x, rota.y, rota.z};

	Matrix4 matRotaX, matRotaY, matRotaZ; 
	
	matRotaZ = {
		cos(worldTransform_.rotation_.z), sin(worldTransform_.rotation_.z), 0, 0,
		-sin(worldTransform_.rotation_.z),cos(worldTransform_.rotation_.z),0,0,
		0,0,1,0,
		0,0,0,1,
	};

	matRotaX = {
		1,0,0,0,
		0,cos(worldTransform_.rotation_.x),sin(worldTransform_.rotation_.x),0,
		0,-sin(worldTransform_.rotation_.x),cos(worldTransform_.rotation_.x),0,
		0,0,0,1,
	};

	matRotaY = {
		cos(worldTransform_.rotation_.y), 0, -sin(worldTransform_.rotation_.y), 0,
		0,1,0,0,
		sin(worldTransform_.rotation_.y),0,cos(worldTransform_.rotation_.y),0,
		0,0,0,1,
	};

	//���s�ړ�
	worldTransform_.translation_ = {trans.x, trans.y, trans.z};

	Matrix4 matTrans = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		worldTransform_.translation_.x,worldTransform_.translation_.y,worldTransform_.translation_.z,1
	};

	worldTransform_.matWorld_ = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	worldTransform_.matWorld_ *= matScale;
	Matrix4 matRota;
	matRota = matRotaZ;
	matRota *= matRotaX;
	matRota *= matRotaY;
	worldTransform_.matWorld_ *= matRota;
	worldTransform_.matWorld_ *= matTrans;

	worldTransform_.TransferMatrix();
}

void Cube::Draw(DebugCamera* debugCamera_) {
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
}