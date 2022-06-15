#include"Cube.h"
#include"DebugCamera.h"
#include"Affine.h"

Cube::Cube() {
	//ファイルを検索してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mushroom.jpg");
	
	// 3Dモデルの生成
	model_ = Model::Create();
	
	//ワールドトランスフォームの初期化
	this->worldTransform_.Initialize();
}

Cube::~Cube() {
	delete model_;
}

void Cube::Update(WorldTransform worldTransform_) {
	//行列設定
	Matrix4 affineWorld = Affine(worldTransform_);

	//掛け
	this->worldTransform_.matWorld_ = affineWorld;

	//行列の転送
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