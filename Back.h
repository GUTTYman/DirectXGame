#pragma once
#include "GameObject.h"
#include <DirectXMath.h>
#include "Object3d.h"
class Back :
	public GameObject
{
private:
	std::unique_ptr < Object3d> object;
public:
	Back();
	~Back();
	void Initialize(DirectXCommon* dxCommon, TextureManager* textureManager) override;
	void Update()override;
	void Draw(DirectXCommon* dxCommon)override;
};