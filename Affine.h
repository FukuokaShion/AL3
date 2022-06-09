#pragma once
#include "WorldTransform.h"

Matrix4 AffineScale(WorldTransform worldTransform);
Matrix4 AffineRotaX(WorldTransform worldTransform);
Matrix4 AffineRotaY(WorldTransform worldTransform);
Matrix4 AffineRotaZ(WorldTransform worldTransform);
Matrix4 AffineRota(Matrix4 rota1, Matrix4 rota2,Matrix4 rota3);
Matrix4 AffineTrans(WorldTransform worldTransform);
Matrix4 AffineWorld(Matrix4 scale,Matrix4 rota, Matrix4 trans);