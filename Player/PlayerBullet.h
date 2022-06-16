#pragma once
#include "Cube.h"
#include "DebugText.h"

class PlayerBullet {
  public:
	//‰Šú‰»
	void Initialize(WorldTransform worldTransform);
	//XV
	void Update();
	//•½sˆÚ“®
	void Transform();
	//‰ñ“]
	void Rotate();
	//•`‰æ
	void Draw(ViewProjection viewProjection);

  private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	Cube* model;
	uint32_t texture;
};