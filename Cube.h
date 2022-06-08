#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "DebugCamera.h"

class Cube {
  public:
	Cube();

	~Cube();

	void Affine(Vector3 scale, Vector3 rota, Vector3 trans);

	void Draw(DebugCamera* debugCamera_);

	
	uint32_t textureHandle_ = 0;
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
};