#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "DebugCamera.h"

#include "Cube.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	float PI = 3.1415;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;


	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	//オブジェクト
	Cube* cubes[9];

  public:
	enum PartId {
		kRoot,//大元
		kSpine,//脊髄
		kChest,//胸
		kHead,//頭
		kArmL,//左腕
		kArmR,//右腕
		kHip,//尻
		kLegL,//左足
		kLegR,//右足

		kNumPartId
	};

	//デバッグカメラ
	ViewProjection viewProjection_;
	DebugCamera* debugCamera_ = nullptr;

	//カメラ上方向の角度
	float viewAngle = 0.0f;

};
