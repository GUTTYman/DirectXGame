#pragma once
#include "Model.h"
#include <DirectXMath.h>
#include "Object3d.h"
#include"BoundObject.h"
//�L�m�R�Ǘ��N���X
class BoundObjectManager
{
private:
	static const int size = 1;
	std::vector<std::unique_ptr<BoundObject>> object;

public:
	BoundObjectManager();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager);
	void Update();
	void Draw(DirectXCommon* dxCommon);

	void SetPosition(Vector3 position);
};

