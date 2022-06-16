#pragma once
#include"Cube.h"
#include"DebugText.h"
#include"PlayerBullet.h"

class Player {
  public:
	//‰Šú‰»
	void Initialize();
	//XV
	void Update();
	//•½sˆÚ“®
	void Transform();
	//‰ñ“]
	void Rotate();
	//’e”­Ë
	void Attack();
	//•`‰æ
	void Draw(ViewProjection viewProjection);

  private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;
	Cube* model = nullptr;
	PlayerBullet* bullet_ = nullptr;
	uint32_t texture;
};