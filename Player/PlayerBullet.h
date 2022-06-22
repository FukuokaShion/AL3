#pragma once
#include<memory>
#include "Cube.h"
#include "DebugText.h"

class PlayerBullet {
  public:
	~PlayerBullet();
	//������
	void Initialize(WorldTransform worldTransform);
	//�X�V
	void Update();
	//���s�ړ�
	void Transform();
	//��]
	void Rotate();
	//�`��
	void Draw(ViewProjection viewProjection);

  private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	Cube* model;
	uint32_t texture;
};