#pragma once
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"SpherePlant.h"
//�X�p�C�N�{�[����A�������ĊǗ�����N���X
class SpherePlantManager
{
private:
	int size;
	std::vector<SpherePlant*> object;

public:
	SpherePlantManager(int a);
	~SpherePlantManager();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager,float firstSize);
	void Update();
	void Draw(DirectXCommon* dxCommon);

	void SetPosition(Vector3 position);
	void SetTarget(Vector3 tPos);
	inline void SetObjectNumber(int i) { size = i; }
	//�A���̌����w��MAX�l : 6.28
	void SetAngle(float a);
	void LarpColor(Vector3 s,Vector3 e);
};

