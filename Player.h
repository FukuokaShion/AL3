#pragma once
#include"Cube.h"
#include"DebugText.h"

class Player {
  public:
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw(ViewProjection viewProjection);

  private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	Cube* model;
	uint32_t texture;
};