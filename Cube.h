#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "DebugCamera.h"

class Cube {
  public:
	Cube();

	~Cube();

	void Affine(WorldTransform worldTransform);

	void Draw(DebugCamera* debugCamera_);

	private:
	uint32_t textureHandle_ = 0;
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
};