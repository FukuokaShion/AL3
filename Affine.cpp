#include "Affine.h"
#include <cmath>

Matrix4 AffineScale(WorldTransform worldTransform) {
	Matrix4 matScale = {
		worldTransform.scale_.x,0,0,0,
		0,worldTransform.scale_.y,0,0,
		0,0,worldTransform.scale_.z,0,
		0,0,0,1
	};

	return matScale;
}


Matrix4 AffineRotaX(WorldTransform worldTransform) {
	Matrix4 matRotaX = {
		1,0,0,0,
		0,cos(worldTransform.rotation_.x),sin(worldTransform.rotation_.x),0,
		0,-sin(worldTransform.rotation_.x),cos(worldTransform.rotation_.x),0,
		0,0,0,1,
	};

	return matRotaX;
}


Matrix4 AffineRotaY(WorldTransform worldTransform) {
	Matrix4 matRotaY = {
		cos(worldTransform.rotation_.y), 0, -sin(worldTransform.rotation_.y), 0,
		0,1,0,0,
		sin(worldTransform.rotation_.y),0,cos(worldTransform.rotation_.y),0,
		0,0,0,1,
	};

	return matRotaY;
}


Matrix4 AffineRotaZ(WorldTransform worldTransform) {
	Matrix4 matRotaZ = {
		cos(worldTransform.rotation_.z), sin(worldTransform.rotation_.z), 0, 0,
		-sin(worldTransform.rotation_.z),cos(worldTransform.rotation_.z),0,0,
		0,0,1,0,
		0,0,0,1,
	};

	return matRotaZ;
}

Matrix4 AffineRota(Matrix4 rota1, Matrix4 rota2, Matrix4 rota3) {
	Matrix4 matRota;
	matRota = rota1;
	matRota *= rota2;
	matRota *= rota3;

	return matRota;
}

Matrix4 AffineTrans(WorldTransform worldTransform) {
	Matrix4 matTrans = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		worldTransform.translation_.x,worldTransform.translation_.y,worldTransform.translation_.z,1
	};

	return matTrans;
}

Matrix4 AffineWorld(Matrix4 scale, Matrix4 rota, Matrix4 trans) {
	Matrix4 matWorld = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	matWorld *= scale;
	matWorld *= rota;
	matWorld *= trans;

	return matWorld;
}