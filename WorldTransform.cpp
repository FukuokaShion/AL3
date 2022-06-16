#include "WorldTransform.h"
#include"Affine.h"

void WorldTransform::Update() {
	//行列計算
	matWorld_ = Affine();
	//親の行列を掛ける
	if (parent_ != NULL) {
		matWorld_ *= parent_->matWorld_;
	}
	//ワールド行列を転送
	TransferMatrix();
}