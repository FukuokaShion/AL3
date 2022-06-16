#pragma once
#include"Cube.h"
#include"DebugText.h"

class Player {
  public:
	//‰Šú‰»
	void Initialize();
	//XV
	void Update();
	//•`‰æ
	void Draw(ViewProjection viewProjection);

  private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	Cube* model;
	uint32_t texture;
};