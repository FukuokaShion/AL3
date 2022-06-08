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

void Cube::Move() {
	
}

void Cube::Draw(DebugCamera* debugCamera_) {
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
}