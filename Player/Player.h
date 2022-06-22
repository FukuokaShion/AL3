#pragma once
#include<memory>
#include<list>
#include"Cube.h"
#include"DebugText.h"
#include"PlayerBullet.h"

class Player {
  public:
	~Player();
	//初期化
	void Initialize();
	//更新
	void Update();
	//平行移動
	void Transform();
	//回転
	void Rotate();
	//弾発射
	void Attack();
	//描画
	void Draw(ViewProjection viewProjection);

  private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	Cube* model = nullptr;
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
	uint32_t texture;
};