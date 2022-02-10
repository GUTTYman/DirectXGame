#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"

class RiseUI :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;

public:
	RiseUI();
	~RiseUI();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update();
	void Draw(DirectXCommon* dxCommon)override;
};

