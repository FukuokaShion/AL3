#pragma once
#include<memory>
#include "Cube.h"
#include "DebugText.h"

class PlayerBullet {
  public:
	~PlayerBullet();
	//初期化
	void Initialize(WorldTransform worldTransform);
	//更新
	void Update();
	//平行移動
	void Transform();
	//回転
	void Rotate();
	//描画
	void Draw(ViewProjection viewProjection);

  private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	Cube* model;
	uint32_t texture;
};