#pragma once
#include"Cube.h"
#include"DebugText.h"

class Player {
  public:
	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw(ViewProjection viewProjection);

  private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	Cube* model;
	uint32_t texture;
};