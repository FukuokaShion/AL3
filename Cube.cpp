#include"Cube.h"
#include"DebugCamera.h"

Cube::Cube() {
	//ファイルを検索してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mushroom.jpg");
	// 3Dモデルの生成
	model_ = Model::Create();
	

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
}

Cube::~Cube() { delete model_; }

void Cube::Move() {
	
}

void Cube::Draw(DebugCamera* debugCamera_) {
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
}