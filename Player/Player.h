#pragma once
#include"Cube.h"
#include"DebugText.h"
#include"PlayerBullet.h"

class Player {
  public:
	//������
	void Initialize();
	//�X�V
	void Update();
	//���s�ړ�
	void Transform();
	//��]
	void Rotate();
	//�e����
	void Attack();
	//�`��
	void Draw(ViewProjection viewProjection);

  private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	Cube* model = nullptr;
	PlayerBullet* bullet_ = nullptr;
	uint32_t texture;
};