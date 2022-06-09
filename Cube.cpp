#include"Cube.h"
#include"DebugCamera.h"
#include"Affine.h"

Cube::Cube() {
	//�t�@�C�����������ăe�N�X�`����ǂݍ���
	textureHandle_ = TextureManager::Load("mushroom.jpg");
	
	// 3D���f���̐���
	model_ = Model::Create();
	
	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
}

Cube::~Cube() {
	delete model_;
}

void Cube::Affine(WorldTransform worldTransform_) {
	//�s��ݒ�
	Matrix4 matScale = AffineScale(worldTransform_);
	Matrix4 matRotaX = AffineRotaX(worldTransform_);
	Matrix4 matRotaY = AffineRotaY(worldTransform_);
	Matrix4 matRotaZ = AffineRotaZ(worldTransform_);
	Matrix4 matRota = AffineRota(matRotaZ, matRotaX, matRotaY);
	Matrix4 matTrans = AffineTrans(worldTransform_);

	//�|��
	this->worldTransform_.matWorld_ = AffineWorld(matScale,matRota,matTrans);

	//�s��̓]��
	this->worldTransform_.TransferMatrix();
}

void Cube::Draw(DebugCamera* debugCamera_) {
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
}