#include"Cube.h"
#include"DebugCamera.h"
#include"Affine.h"

Cube::Cube(uint32_t textureHanlde) {
	//�t�@�C�����������ăe�N�X�`����ǂݍ���
	textureHandle_ = textureHanlde;
	
	// 3D���f���̐���
	model_ = Model::Create();
	
	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
}

Cube::~Cube() {
	delete model_;
}

void Cube::Affine() {
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

void Cube::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}