#include"Cube.h"
#include"DebugCamera.h"
#include"Affine.h"

Cube::Cube(uint32_t textureHanlde) {
	//ファイルを検索してテクスチャを読み込む
	textureHandle_ = textureHanlde;
	
	// 3Dモデルの生成
	model_ = Model::Create();
	
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
}

Cube::~Cube() {
	delete model_;
}

void Cube::Affine() {
	//行列設定
	Matrix4 matScale = AffineScale(worldTransform_);
	Matrix4 matRotaX = AffineRotaX(worldTransform_);
	Matrix4 matRotaY = AffineRotaY(worldTransform_);
	Matrix4 matRotaZ = AffineRotaZ(worldTransform_);
	Matrix4 matRota = AffineRota(matRotaZ, matRotaX, matRotaY);
	Matrix4 matTrans = AffineTrans(worldTransform_);

	//掛け
	this->worldTransform_.matWorld_ = AffineWorld(matScale,matRota,matTrans);

	//行列の転送
	this->worldTransform_.TransferMatrix();
}

void Cube::Draw(ViewProjection viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}