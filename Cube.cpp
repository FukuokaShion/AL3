#include"Cube.h"
#include"DebugCamera.h"
#include"Affine.h"

Cube::Cube() {
	//�t�@�C�����������ăe�N�X�`����ǂݍ���
	textureHandle_ = TextureManager::Load("mushroom.jpg");
	
	// 3D���f���̐���
	model_ = Model::Create();
	
	//���[���h�g�����X�t�H�[���̏�����
	this->worldTransform_.Initialize();
}

Cube::~Cube() {
	delete model_;
}

void Cube::Update(WorldTransform worldTransform_) {
	//�s��ݒ�
	Matrix4 affineWorld = Affine(worldTransform_);

	//�|��
	this->worldTransform_.matWorld_ = affineWorld;

	//�s��̓]��
	this->worldTransform_.TransferMatrix();
}

void Cube::Update(Matrix4 world) { 
	worldTransform_.matWorld_ = world;
	worldTransform_.TransferMatrix();
}

void Cube::Draw(DebugCamera* debugCamera_) {
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
}

void Cube::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}