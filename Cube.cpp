#include"Cube.h"
#include"DebugCamera.h"
#include"Affine.h"

Cube::Cube() {
	//ファイルを検索してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mushroom.jpg");
	
	// 3Dモデルの生成
	model_ = Model::Create();
	
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
}

Cube::~Cube() {
	delete model_;
}

void Cube::Affine(WorldTransform worldTransform_) {
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

void Cube::Draw(DebugCamera* debugCamera_) {
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
}