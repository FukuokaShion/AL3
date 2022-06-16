#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "DebugCamera.h"

class Cube {
  public:
	Cube(uint32_t textureHandle);

	~Cube();

	void Affine();

	void Draw(ViewProjection viewProjection);

	private:
	uint32_t textureHandle_ = 0;
	Model* model_ = nullptr;
  public:
	WorldTransform worldTransform_;
};