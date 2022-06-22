#pragma once
#include<memory>
#include<list>
#include"Cube.h"
#include"DebugText.h"
#include"PlayerBullet.h"

class Player {
  public:
	~Player();
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
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	uint32_t texture;
};