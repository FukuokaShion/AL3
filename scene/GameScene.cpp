#include "GameScene.h"
#include "AxisIndicator.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include <cassert>
#include <random>
#include<Affine.h>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete debugCamera_;
	for (int i = 0; i < 9; i++) {
		cubes[i]->~Cube();
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();
	
//-----カメラ設定-----
	{
		////カメラ始点座標を設定
		//viewProjection_.eye = {0, 0, -50};
		////カメラの注視点座標設定
		//viewProjection_.target = {0, 0, 0};
		////カメラの上方向ベクトル設定
		//viewProjection_.up = {0.0f, 1.0f, 0.0f};
		////カメラ垂直方向視野角を設定
		//viewProjection_.fovAngleY = PI/4.0f;
		////アス比を設定
		////viewProjection_.aspectRatio = 1.0f;
		////ニアクリップ距離を設定
		//viewProjection_.nearZ = 52.0f;
		////ファークリップ距離を設定
		//viewProjection_.farZ = 53.0f;
		//ビュープロジェクションの初期化
		viewProjection_.Initialize();
	}

//----デバッグカメラ----
	debugCamera_ = new DebugCamera(1280, 720);

//----軸方向----
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

//---------オブジェクト----------
	{
		//オブジェクトの初期化
		for (int i = 0; i < 9; i++) {
			cubes[i] = new Cube();
		}

		//脊髄
		cubes[PartId::kSpine]->worldTransform_.parent_ = &cubes[PartId::kRoot]->worldTransform_;
		cubes[PartId::kSpine]->worldTransform_.translation_ = {0, 4.5f, 0};

		//上半身
		//胸
		cubes[PartId::kChest]->worldTransform_.parent_ = &cubes[PartId::kSpine]->worldTransform_;
		cubes[PartId::kChest]->worldTransform_.translation_ = {0, 0, 0};
		//頭
		cubes[PartId::kHead]->worldTransform_.parent_ = &cubes[PartId::kChest]->worldTransform_;
		cubes[PartId::kHead]->worldTransform_.translation_ = {0, 3.0f, 0};
		//左腕
		cubes[PartId::kArmL]->worldTransform_.parent_ = &cubes[PartId::kChest]->worldTransform_;
		cubes[PartId::kArmL]->worldTransform_.translation_ = {-3.0f, 0, 0};
		//右腕
		cubes[PartId::kArmR]->worldTransform_.parent_ = &cubes[PartId::kChest]->worldTransform_;
		cubes[PartId::kArmR]->worldTransform_.translation_ = {3.0f, 0, 0};

		//下半身
		//尻
		cubes[PartId::kHip]->worldTransform_.parent_ = &cubes[PartId::kSpine]->worldTransform_;
		cubes[PartId::kHip]->worldTransform_.translation_ = {0, -3.0f, 0};
		//左足
		cubes[PartId::kLegL]->worldTransform_.parent_ = &cubes[PartId::kHip]->worldTransform_;
		cubes[PartId::kLegL]->worldTransform_.translation_ = {-3.0f, -3.0f, 0};
		//右足
		cubes[PartId::kLegR]->worldTransform_.parent_ = &cubes[PartId::kHip]->worldTransform_;
		cubes[PartId::kLegR]->worldTransform_.translation_ = {3.0f, -3.0f, 0};

		//オブジェクトを初期位置へ移動
		for (int i = PartId::kRoot; i < PartId::kNumPartId; i++) {
			cubes[i]->Update();
		}
	}
}


void GameScene::Update() {
	//移動ベクトル
	Vector3 move = {0, 0, 0};
	//移動速度
	float moveSpeed = 0.2f;

	//横移動
	if (input_->PushKey(DIK_RIGHT)) {
		move.x = moveSpeed;
	} else if (input_->PushKey(DIK_LEFT)) {
		move.x = -moveSpeed;
	};
	cubes[PartId::kRoot]->worldTransform_.translation_ += move;


	//上半身回転
	//移動ベクトル
	Vector3 chestRota = {0, 0, 0};
	//回転速度
	float chestRotaSpeed = PI / 90;
	if (input_->PushKey(DIK_U)) {
		chestRota.y = -chestRotaSpeed;
	} else if (input_->PushKey(DIK_I)) {
		chestRota.y = chestRotaSpeed;
	};
	cubes[PartId::kChest]->worldTransform_.rotation_ += chestRota;


	//下半身回転
	//移動ベクトル
	Vector3 hipRota = {0, 0, 0};
	//回転速度
	float hipRotaSpeed = PI / 90;
	if (input_->PushKey(DIK_J)) {
		hipRota.y = -hipRotaSpeed;
	} else if (input_->PushKey(DIK_K)) {
		hipRota.y = hipRotaSpeed;
	};
	cubes[PartId::kHip]->worldTransform_.rotation_ += hipRota;


	//大元から順に更新していく
	for (int i = 0; i < 9; i++) {
		//行列計算
		cubes[i]->worldTransform_.matWorld_ = Affine(cubes[i]->worldTransform_);
		//親の行列を掛ける
		if (i > 0) {
			cubes[i]->worldTransform_.matWorld_ *= cubes[i]->worldTransform_.parent_->matWorld_;
		}
		//ワールド行列を転送
		cubes[i]->Update(cubes[i]->worldTransform_.matWorld_);
	}



	/*//デバックカメラの移動
	debugCamera_->Update();*/

	////視点移動
	//{
	//	Vector3 move = {0, 0, 0};
	//	//視点の移動速さ
	//	const float kEyeSpeed = 0.2f;
	//	//押した方向で移動ベクトルを変更
	//	if (input_->PushKey(DIK_W)) {
	//		move = {0, 0, kEyeSpeed};
	//	} else if (input_->PushKey(DIK_S)) {
	//		move = {0, 0, -kEyeSpeed};
	//	}
	//	//視点移動
	//	viewProjection_.eye += move;
	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

	//	//デバッグ用表示
	//	debugText_->SetPos(50, 50);
	//	debugText_->Printf(
	//	  "eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
	//}

	////注視点移動
	//{
	//	//移動ベクトル
	//	Vector3 move = {0, 0, 0};

	//	//注視点の移動速さ
	//	const float kTargetSpeed = 0.2f;

	//	//押した方向で移動ベクトルを変更
	//	if (input_->PushKey(DIK_LEFT)) {
	//		move = {-kTargetSpeed, 0, 0};
	//	} else if (input_->PushKey(DIK_RIGHT)) {
	//		move = {kTargetSpeed, 0, 0};
	//	}

	//	//注視点移動
	//	viewProjection_.target += move;

	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();

	//	//デバッグ用表示
	//	debugText_->SetPos(50, 70);
	//	debugText_->Printf(
	//	  "target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y, viewProjection_.target.z);
	//}

	////上方向回転処理
	//{
	//	//上方向の回転速さ
	//	const float kUpRotaSpeed = 0.05f;

	//	//押した方向で移動ベクトルを変更
	//	if (input_->PushKey(DIK_SPACE)) {
	//		viewAngle += kUpRotaSpeed;
	//		viewAngle = fmodf(viewAngle, PI * 2.0f);
	//	}

	//	//上方向ベクトルを計算
	//	viewProjection_.up = {cosf(viewAngle), sinf(viewAngle), 0.0f};

	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();
	//	
	//	//デバッグ用表示
	//	debugText_->SetPos(50, 90);
	//	debugText_->Printf("up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);
	//
	//}
	
	////Fov変更処理
	//{
	//	//視野変更の速さ
	//	float fovSpeed = PI/180.0f;
	//	//上キーで視野が広がる
	//	if (input_->PushKey(DIK_UP)) {
	//		if (viewProjection_.fovAngleY < PI) {
	//			viewProjection_.fovAngleY += fovSpeed;
	//		}
	//	} else if (input_->PushKey(DIK_DOWN)) {
	//		if (viewProjection_.fovAngleY > 0.01f) {
	//			viewProjection_.fovAngleY -= fovSpeed;
	//		}
	//	}
	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();
	//	//デバッグ用表示
	//	debugText_->SetPos(50, 110);
	//	debugText_->Printf("fovAngleY(degree):%f", viewProjection_.fovAngleY);
	//}

	////クリップ距離変更処理
	//{
	//	//ニアクリップ変更速度
	//	float nearZSpeed = 0.1f;
	//	//上下キーでニアクリップ距離変更
	//	if (input_->PushKey(DIK_UP)) {
	//		viewProjection_.nearZ += nearZSpeed;
	//	} else if (input_->PushKey(DIK_DOWN)) {
	//		viewProjection_.nearZ -= nearZSpeed;
	//	}
	//	//行列の再計算
	//	viewProjection_.UpdateMatrix();
	//	//デバッグ用表示
	//	debugText_->SetPos(50, 130);
	//	debugText_->Printf("nearZ:%f", viewProjection_.nearZ);
	//}

}


void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	for (int i = PartId::kChest; i < PartId::kNumPartId; i++) {
		cubes[i]->Draw(viewProjection_);
	}


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
